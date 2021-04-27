rem Purpose: create a folder where Xclu comes with all shared libraries 
rem          required to run without Qt installation on target system.
rem Input: Xclu-bin folder
rem Output: Xclu-bin-portable folder and xclu-bin-windows-portable.zip file

call "%programfiles(x86)%\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
rem we need to call echo on again after vcvars64.bat
echo on

pushd "%~dp0"

rmdir /s /q Xclu-bin-portable
del /q xclu-bin-windows-portable.zip

rem copy
xcopy /e /k /h /i Xclu-bin Xclu-bin-portable

rem ****************************************************** windeployqt
rem for other options like --webkit2, --angle, see:
rem     https://doc.qt.io/Qt-5/windows-deployment.html
rem QT BUG: we should say 3drenderer here instead of 3drender
rem QT LOGIC BUG: must say --debug to copy runtime VC libs, see https://code.qt.io/cgit/qt/qttools.git/tree/src/windeployqt/main.cpp?h=5.15.2#n1158

windeployqt --verbose 1 --release --compiler-runtime -3drenderer -3dcore -3dinput Xclu-bin-portable/Xclu.exe
if %errorlevel% neq 0 exit /b %errorlevel%

rem ****************************************************** other dlls not found by windeployqt

copy "C:\Program Files (x86)\Intel RealSense SDK 2.0\bin\x64\realsense2.dll" Xclu-bin-portable\realsense2.dll

rem ****************************************************** pack to zip

7z a -bb xclu-bin-windows-portable.zip Xclu-bin-portable

popd

echo PORTABLE SUCCESS