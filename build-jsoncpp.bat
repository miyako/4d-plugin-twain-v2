@echo off
rem Builds jsoncpp (deps\jsoncpp submodule) as an x64 static library with the
rem static CRT and installs it for TWAIN.vcxproj:
rem   Release (/MT)  -> lib\windows64\jsoncpp.lib
rem   Debug   (/MTd) -> lib\windows64\debug\jsoncpp.lib
rem Usage: build-jsoncpp.bat [Release^|Debug]   (default: Release)
setlocal

set "ROOT=%~dp0"
set "SRC=%ROOT%deps\jsoncpp"
set "BUILD=%ROOT%build\jsoncpp-win64"
set "CONFIG=%~1"
if "%CONFIG%"=="" set "CONFIG=Release"

if /I "%CONFIG%"=="Debug" (
  set "OUTDIR=%ROOT%lib\windows64\debug"
) else (
  set "CONFIG=Release"
  set "OUTDIR=%ROOT%lib\windows64"
)

if not exist "%SRC%\CMakeLists.txt" (
  git -C "%ROOT%." submodule update --init deps/jsoncpp || exit /b 1
)

rem Fall back to the CMake bundled with Visual Studio if not on PATH
where cmake >nul 2>&1
if not errorlevel 1 goto :have_cmake
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -property installationPath`) do set "VSDIR=%%i"
set "PATH=%PATH%;%VSDIR%\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
where cmake >nul 2>&1
if errorlevel 1 (
  echo error: cmake not found
  exit /b 1
)
:have_cmake

cmake -S "%SRC%" -B "%BUILD%" -A x64 ^
  -DBUILD_SHARED_LIBS=OFF ^
  -DBUILD_STATIC_LIBS=ON ^
  -DBUILD_OBJECT_LIBS=OFF ^
  -DJSONCPP_STATIC_WINDOWS_RUNTIME=ON ^
  -DJSONCPP_WITH_TESTS=OFF ^
  -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF ^
  -DJSONCPP_WITH_PKGCONFIG_SUPPORT=OFF ^
  -DJSONCPP_WITH_CMAKE_PACKAGE=OFF ^
  -DJSONCPP_WITH_INSTALL=OFF || exit /b 1

cmake --build "%BUILD%" --config %CONFIG% --parallel || exit /b 1

if not exist "%OUTDIR%" mkdir "%OUTDIR%"
copy /Y "%BUILD%\lib\%CONFIG%\jsoncpp.lib" "%OUTDIR%\jsoncpp.lib" || exit /b 1
echo Installed %OUTDIR%\jsoncpp.lib (%CONFIG%)
exit /b 0
