# Ownership regressions

An ASan/UBSan harness for the 4D value ownership contracts used by this plugin. It needs no 4D, scanner or TWAIN DSM.

- It compiles the real plugin sources (`4DPlugin-TWAIN.cpp`, `support/*.cpp`), the unchanged SDK `4DPluginAPI.c`, `C_TEXT` and `C_BLOB`.
- A synthetic `Call4D` engine tracks every string, picture, object, collection and handle. It reports leaks, double frees, and failed results that were touched.
- A stubbed `DSM_Entry` provides two synthetic sources. They produce 16x8 grey pages through memory transfer.

```sh
git submodule update --init deps/jsoncpp
tests/ownership/run.sh . fixed                       # every test must pass
git archive 2423ec4 | tar -x -C /tmp/base
JSONCPP=$PWD/deps/jsoncpp tests/ownership/run.sh /tmp/base baseline   # defect tests must fail, controls pass
```

Each test runs in its own process. Any sanitizer report or `HARNESS ERROR` fails the run in either mode.

Not covered: the Windows-only paths (`doScanWin`, shared-memory transfer), the real 4D runtime and a real TWAIN DSM.
