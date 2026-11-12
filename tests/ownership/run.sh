#!/bin/bash
# Builds the synthetic-boundary ownership harness against a source tree with
# ASan/UBSan and runs every test in its own process.
#
#   tests/ownership/run.sh <source-root> <fixed|baseline>
#
# <source-root> provides the plugin sources, the bundled 4D Plugin API and
# the static image libraries (a/). The harness itself always comes from this
# script's directory, so the SAME harness can be run against an immutable
# baseline (git archive of the base SHA) and against the fixed tree.
#
# In "fixed" mode every test must pass. In "baseline" mode the tests named
# in EXPECTED_BASELINE_FAILURES must fail and every other test (the
# controls) must pass; anything else is a harness or model error.
set -euo pipefail

SRC=$(cd "$1" && pwd)
MODE=$2
HERE=$(cd "$(dirname "$0")" && pwd)
OUT=$(mktemp -d)
trap 'rm -rf "$OUT"' EXIT

EXPECTED_BASELINE_FAILURES="
defect_live_get_devices_element_not_cleared
defect_live_ob_set_s_empty_owner_leaks
defect_live_scan_jpeg_pictures_not_cleared
defect_live_scan_png_picture_not_cleared
hardening_live_default_option_parse_error_untouched
hardening_live_ob_stringify_error_untouched
defect_dormant_ob_get_a_result_not_cleared
defect_dormant_ob_get_b_wrong_kind_not_cleared
defect_dormant_ob_get_n_wrong_kind_not_cleared
defect_dormant_ob_get_o_c_reference_not_released
defect_dormant_ob_set_empty_owner_leaks
hardening_dormant_ob_get_error_result_untouched
"

# jsoncpp is a submodule (deps/jsoncpp); a git archive does not contain it.
JSONCPP=${JSONCPP:-$SRC/deps/jsoncpp}
if [ ! -f "$JSONCPP/src/lib_json/json_value.cpp" ]; then
    echo "jsoncpp sources not found at $JSONCPP (git submodule update --init deps/jsoncpp, or set JSONCPP)" >&2
    exit 2
fi

SAN="-g -O1 -fno-omit-frame-pointer -fsanitize=address,undefined -fno-sanitize-recover=undefined"
# Same header search paths as the Xcode project.
INC=(-I "$SRC/4D Plugin API" -I "$SRC/4D Plugin API/Classes" -I "$SRC/support" -I "$SRC"
     -I "$SRC/include" -I "$SRC/include/libpng16" -I "$SRC/include/jpeglib"
     -I "$JSONCPP/include/json" -I "$JSONCPP/include")
WARN="-w"

objs=()
cc() { # <lang> <file> [extra flags...]
    local lang=$1 file=$2; shift 2
    local o="$OUT/$(basename "$file").o"
    xcrun clang $SAN $WARN -x "$lang" "${INC[@]}" "$@" -c "$file" -o "$o"
    objs+=("$o")
}

# The macOS build members (TWAIN.xcodeproj): 4DPluginAPI.c, C_BLOB.cpp,
# C_TEXT.cpp, 4DPlugin-JSON.cpp, capabilities.cpp, twain_dsm.cpp,
# twain_jpg.cpp, twain_png.cpp and 4DPlugin-TWAIN.cpp (#included by the
# harness). ARRAY_TEXT.cpp and C_LONGINT.cpp are in no build.
cc c "$SRC/4D Plugin API/4DPluginAPI.c" -Wno-multichar -Wno-error=int-conversion
for f in C_BLOB C_TEXT; do
    cc objective-c++ "$SRC/4D Plugin API/Classes/$f.cpp" -std=c++17
done
cc objective-c++ "$SRC/support/4DPlugin-JSON.cpp" -std=c++17
cc objective-c++ "$SRC/support/capabilities.cpp" -std=c++17
cc objective-c++ "$SRC/support/twain_jpg.cpp" -std=c++17
cc objective-c++ "$SRC/support/twain_png.cpp" -std=c++17
# On macOS (USE_TWAIN_DSM 0) DSM::Alloc/Lock are "return 0" stubs, so no
# memory transfer can complete there. The harness supplies the DSM memory
# entry points the Windows build gets from TWAINDSM (DSM_MemAllocate...);
# the platform versions are renamed out of the way. Everything else in
# twain_dsm.cpp is the real code.
cc objective-c++ "$SRC/support/twain_dsm.cpp" -std=c++17 \
    -DAlloc=platform_dsm_Alloc -DFree=platform_dsm_Free -DLock=platform_dsm_Lock -DUnlock=platform_dsm_Unlock
for f in json_reader json_value json_writer; do
    cc objective-c++ "$JSONCPP/src/lib_json/$f.cpp" -std=c++17 -I "$JSONCPP/src/lib_json"
done
# engine_harness.cpp #includes 4DPlugin-TWAIN.cpp from $SRC.
cc objective-c++ "$HERE/engine_harness.cpp" -std=c++17

# TWAIN.framework is NOT linked: DSM_Entry is the harness's synthetic
# data source, so no real scanner is ever touched.
xcrun clang++ $SAN "${objs[@]}" "$SRC/a/libjpeg.a" "$SRC/a/libpng16.a" "$SRC/a/libz.a" \
    -framework Foundation -framework CoreGraphics -o "$OUT/harness"

export ASAN_OPTIONS=abort_on_error=0:halt_on_error=1
export UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1

bad=0
for t in $("$OUT/harness" --list); do
    if "$OUT/harness" "$t" >"$OUT/$t.log" 2>&1; then got=pass; else got=fail; fi
    expect=pass
    if [ "$MODE" = baseline ] && grep -qx "$t" <<<"$EXPECTED_BASELINE_FAILURES"; then expect=fail; fi
    if [ "$got" = "$expect" ]; then status=OK; else status=UNEXPECTED; bad=1; fi
    printf '%-12s %-5s (expected %-4s) %s\n' "$status" "$got" "$expect" "$t"
    if [ "$got" = fail ]; then sed 's/^/    | /' "$OUT/$t.log"; fi
    # A sanitizer report or harness error is never an expected outcome.
    if grep -qE 'ERROR: AddressSanitizer|runtime error:|HARNESS ERROR' "$OUT/$t.log"; then
        echo "UNEXPECTED   sanitizer/harness error in $t"; bad=1
    fi
done

if [ $bad -ne 0 ]; then echo "RESULT ($MODE): FAILED"; exit 1; fi
echo "RESULT ($MODE): all outcomes as expected"
