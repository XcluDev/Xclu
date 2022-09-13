#!/bin/bash -ex

# Purpose: install packages required for compilation (Qt, Realsense, etc)
# Notes. Current method is to get Qt from official repos. That is Qt 5.7 for Debian Stretch, Qt 5.11 for Debian Buster.
# Todo: add if-statement and in debian stetch: bypass gamepad packages, use xenial 

################################### primary things
# see also https://forum.xclu.dev/t/setting-up-jetson-nano-for-xclu-qt-nomachine-arduino-realsense-git/25

sudo apt-get install gcc g++ -y
sudo apt-get install zip unzip -y # this will be required for portable zip
sudo apt-get install -y \
    qt5-default \
    qtbase5-dev \
    qtmultimedia5-dev libqt5serialport5-dev libqt5serialport5 \
    libqt53drender5 qt3d5-dev

# the following packages for some reason not found for stretch:
LSB_RELEASE=$(lsb_release -cs)
echo "SETUP_SYSTEM: lsb_release = $LSB_RELEASE"
if [ "$LSB_RELEASE" = "stretch" ]; then
    echo "SETUP_SYSTEM: in debian stretch we skip libqt5gamepad5 libqt5gamepad5-dev"
elif [ "$LSB_RELEASE" = "bionic" ]; then
    echo "SETUP_SYSTEM: in ubuntu bionic we skip libqt5gamepad5 libqt5gamepad5-dev"
else
    sudo apt-get install -y libqt5gamepad5 libqt5gamepad5-dev
fi

################################### realsense2
# see instruction https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md

sudo apt-key adv --keyserver keys.gnupg.net --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE || sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE

if [ "$LSB_RELEASE" = "stretch" ]; then
   # to compile for debian stretch, we have to choose xenial because intel doesn't provide stretch's package. also repos are - focal, bionic.
   sudo add-apt-repository "deb https://librealsense.intel.com/Debian/apt-repo xenial main" -u
else
   sudo add-apt-repository "deb https://librealsense.intel.com/Debian/apt-repo $(lsb_release -cs) main" -u
fi

sudo apt-get install -y librealsense2-dev librealsense2-dbg

# following is for kernel driver on user machine, but it is not required for build
# sudo apt-get install -y librealsense2-dkms librealsense2-utils
echo "SETUP_SYSTEM: on user machine, run: sudo apt-get install -y librealsense2-dkms librealsense2-utils"

echo SETUP SUCCESS
