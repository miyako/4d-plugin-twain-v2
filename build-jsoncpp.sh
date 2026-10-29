#!/bin/sh
# Builds jsoncpp (deps/jsoncpp submodule) as a universal (arm64 + x86_64)
# static library and installs it to a/libjsoncpp.a for the Xcode project.
# Headers are used directly from deps/jsoncpp/include so they always match.
set -eu

ROOT=$(cd "$(dirname "$0")" && pwd)
SRC="$ROOT/deps/jsoncpp"
BUILD="$ROOT/build/jsoncpp-mac"
OUT="$ROOT/a/libjsoncpp.a"
DEPLOY="${MACOSX_DEPLOYMENT_TARGET:-10.13}"

if [ ! -f "$SRC/CMakeLists.txt" ]; then
  git -C "$ROOT" submodule update --init deps/jsoncpp
fi

# Xcode run-script phases don't inherit the user's PATH
PATH="$PATH:/opt/homebrew/bin:/usr/local/bin:/Applications/CMake.app/Contents/bin"
if ! command -v cmake >/dev/null 2>&1; then
  echo "error: cmake not found (brew install cmake)" >&2
  exit 1
fi

rm -rf "$BUILD"
cmake -S "$SRC" -B "$BUILD" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
  -DCMAKE_OSX_DEPLOYMENT_TARGET="$DEPLOY" \
  -DBUILD_SHARED_LIBS=OFF \
  -DBUILD_STATIC_LIBS=ON \
  -DBUILD_OBJECT_LIBS=OFF \
  -DJSONCPP_WITH_TESTS=OFF \
  -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF \
  -DJSONCPP_WITH_PKGCONFIG_SUPPORT=OFF \
  -DJSONCPP_WITH_CMAKE_PACKAGE=OFF \
  -DJSONCPP_WITH_INSTALL=OFF
cmake --build "$BUILD" --config Release --parallel

mkdir -p "$(dirname "$OUT")"
cp "$BUILD/lib/libjsoncpp.a" "$OUT"
lipo -info "$OUT"
