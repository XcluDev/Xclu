echo on

rem Purpose: install required libraries

rem ************************ realsense2 lib

rem this is too slow:
rem git clone https://github.com/Microsoft/vcpkg.git
rem cd vcpkg
rem call bootstrap-vcpkg.bat
rem vcpkg integrate install
rem vcpkg install realsense2

rem faster variant (windows 10 has built-in curl)
if not exist Intel.RealSense.SDK-WIN10-2.33.1.1360.exe (
  curl.exe -o Intel.RealSense.SDK-WIN10-2.33.1.1360.exe -L https://github.com/IntelRealSense/librealsense/releases/download/v2.33.1/Intel.RealSense.SDK-WIN10-2.33.1.1360.exe
)
Intel.RealSense.SDK-WIN10-2.33.1.1360.exe /verysilent /log=realsense.log /sp-

rem ************************ arduino
rem uncomment this if arduino is required for build:
if not exist arduino-1.6.13-windows.zip (
  rem curl.exe -o arduino-1.6.13-windows.zip https://downloads.arduino.cc/arduino-1.6.13-windows.zip
)
rem 7z -y x arduino-1.6.13-windows.zip

rem ************************ Qt
echo please install Qt manually.

rem ************************ Compiler
echo please install Visual Studio or Mingw manually.
