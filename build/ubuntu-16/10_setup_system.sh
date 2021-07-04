#!/bin/bash -ex

# Purpose: install packages required for compilation (Qt, Realsense, etc)

# Notes. Here we use Qt 5.9.5 for ubuntu 16 xenial from https://launchpad.net/~beineri/+archive/ubuntu/opt-qt595-xenial

################################### primary things
# see also https://forum.xclu.dev/t/setting-up-jetson-nano-for-xclu-qt-nomachine-arduino-realsense-git/25

sudo apt-get install gcc g++ -y
sudo apt-get install zip unzip -y # this will be required for portable zip

sudo add-apt-repository ppa:beineri/opt-qt595-xenial -y
sudo apt-get update

sudo apt-get install -y qt59-meta-full

# need this to run in github actions server:
sudo apt-get install mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev
# also need this, see https://stackoverflow.com/questions/42141004/qt-multimedia-cannot-find-lpulse
sudo apt-get install libpulse-dev

################################### realsense2
# see also https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md

sudo apt-key adv --keyserver keys.gnupg.net --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE || sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE

echo "lsb_release = $(lsb_release -cs)"
sudo add-apt-repository "deb https://librealsense.intel.com/Debian/apt-repo $(lsb_release -cs) main" -u

sudo apt-get install -y librealsense2-dev librealsense2-dbg

# following is for kernel driver on user machine, but it is not required for build
# sudo apt-get install -y librealsense2-dkms librealsense2-utils

echo SETUP SUCCESS
