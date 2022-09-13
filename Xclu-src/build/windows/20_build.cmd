echo on
rem Purpose: build Xclu project
rem Input: source folder in ../..
rem Output: Xclu-bin folder

rem notes: * Xclu-bin folder name is configured in Xclu.pro file
rem        * this script is configured for Visual Studio. To switch to mingw, use make instead of nmake.

rem dir /s /b /a:d "%programfiles%\Microsoft Visual Studio"
rem dir /s /b /a:d "%programfiles(x86)%\Microsoft Visual Studio"

rem this call is required to get path'es to visual studio compiler installed by windows-build.yml
call "%programfiles(x86)%\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

rem vcvars64 disables echo, turn on again
echo on
pushd "%~dp0"

mkdir temp-build
pushd temp-build

qmake ../../../Xclu.pro CONFIG+=Release
if %errorlevel% neq 0 exit /b %errorlevel%
rem Release word should start from Capital letter
rem no need this, its already in pro file: DEFINES+=XCLU_DEPLOY

rem this is for visual studio's make version:
rem following option is a speedup for nmake, see https://stackoverflow.com/questions/601970/how-do-i-utilise-all-the-cores-for-nmake
set CL=/MP
nmake
rem this is for mingw:
rem make
if %errorlevel% neq 0 exit /b %errorlevel%

popd

popd

echo BUILD SUCCESS
