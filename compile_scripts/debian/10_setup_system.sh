#!/bin/bash -ex

# Purpose: install packages required for compilation (Qt, Realsense, etc)

# Notes. Current idea is to get Qt from official repos. That is Qt 5.7 for Stretch, Qt 5.11 for Buster.
#        Another approach may be to try installing these custom-build packages
#        which gives more freedom on Qt versions available via apt:
#        https://launchpad.net/~beineri/+archive/ubuntu/opt-qt-5.10.0-xenial


################################### primary things
# see also https://forum.xclu.dev/t/setting-up-jetson-nano-for-xclu-qt-nomachine-arduino-realsense-git/25

sudo apt-get install gcc g++ -y
sudo apt-get install zip unzip -y # this will be required for portable zip
sudo apt-get install -y \
	qt5-default  \
    qtbase5-dev \
	qtmultimedia5-dev libqt5serialport5-dev libqt5serialport5 \
	libqt53drender5 qt3d5-dev \
    libqt5gamepad5 libqt5gamepad5-dev
	
################################### realsense2
# see also https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md

sudo apt-key adv --keyserver keys.gnupg.net --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE || sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE

# modern repos:
#   sudo add-apt-repository "deb http://realsense-hw-public.s3.amazonaws.com/Debian/apt-repo focal main" -u
#   sudo add-apt-repository "deb http://realsense-hw-public.s3.amazonaws.com/Debian/apt-repo bionic main" -u

# repo compatible with debian stretch:
sudo add-apt-repository "deb http://realsense-hw-public.s3.amazonaws.com/Debian/apt-repo xenial main" -u

sudo apt-get install -y librealsense2-dev librealsense2-dbg

# following is for kernel driver on user machine, but it is not required for build
# sudo apt-get install -y librealsense2-dkms librealsense2-utils

echo SETUP SUCCESS
