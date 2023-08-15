# Raspberry Pi 4: Installing openFrameworks, Qt, NoMachine, Arduino, PureData, YOLO, Realsense

## Requirements
- Raspberry Pi 4B, 4Gb,
- Raspbian OS.
- SD 16 Gb, UHD Class 10.

## Commands
Run Terminal

`sudo raspi-config`

Select 1 Expand Filesystem and hit Enter
Select 7 Advanced Options and hit Enter
Select A3 Memory Split and hit Enter
Type 64 and Hit <ok>
openFrameworks requires X11 Desktop for Raspberry Pi 4 and newer:
Select 3 Boot Options
Select B1 Console or B2 Console Autologin or if you want a Desktop enviroment select B4 Desktop with Autologin
For openFrameworks 0.11.0 and onwards OF needs to use the new experimental GL driver instead of the legacy driver.

Select 7 Advanced Options and hit Enter
Select either GL Driver Fake KMS or GL Driver Full KMS or from the options and hit Enter

```
sudo apt-get clean
sudo apt-get update
sudo apt-get upgrade
cd
wget https://openframeworks.cc/versions/v0.11.0/of_v0.11.0_linuxarmv6l_release.tar.gz
mkdir openFrameworks
ls
tar vxfz of_v0.11.0_linuxarmv6l_release.tar.gz -C openFrameworks --strip-components 1
cd openFrameworks/scripts/linux/debian
sudo ./install_dependencies.sh 
HISTORY
history
make Release -C /home/pi/openFrameworks/libs/openFrameworksCompiled/project
cd
cd openFrameworks/examples/
ls
ls -l
cd sound
ls -l
cd audioOutputExample/
make
make run
sudo raspi-config
sudo tar zxvf nomachine_7.6.2_3_aarch64.tar.gz
sudo cp -p nomachine_7.6.2_3_aarch64.tar.gz /usr
ls
cd Downloads/
ls
cp --help
sudo cp nomachine_7.6.2_3_aarch64.tar.gz /usr
cd /usr
sudo tar zxf nomachine_7.6.2_3_aarch64.tar.gz
sudo /usr/NX/nxserver --install
ls
sudo raspi-config
deb-src http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi
sudo apt-get update
sudo apt-get build-dep qt5-qmake
sudo apt-get install qt5-default
sudo apt-get install qtcreator
sudo tools
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.51.tar.gz
cd~
ls
cd Downloads/
ls
tar -xf arduino-nightly-linuxarm.tar.xz 
sudo mv arduino-nightly /opt
sudo /opt/arduino-nightly/install.sh 
git clone https://github.com/pjreddie/darknet
cd darknet
make
ls
wget https://pjreddie.com/media/files/yolov3.weights
./darknet detect cfg/yolov3.cfg yolov3.weights data/dog.jpg
wget https://pjreddie.com/media/files/tiny.weights
make
git clone https://github.com/pjreddie/darknet
./darknet classify cfg/tiny.cfg tiny.weights data/dog.jpg
cd darknet
./darknet classify cfg/tiny.cfg tiny.weights data/dog.jpg
Here's how to use it in Darknet (and also how to install Darknet):
git clone https://github.com/pjreddie/darknet
cd darknet
make
wget https://pjreddie.com/media/files/tiny.weights
./darknet classify cfg/tiny.cfg tiny.weights data/dog.jpg
sudo apt-get install python-pip
sudo pip install --upgrade git+https://github.com/Maratyszcza/PeachPy
sudo pip install --upgrade git+https://github.com/Maratyszcza/confu
git clone https://github.com/ninja-build/ninja.git
cd ninja
git checkout release
./configure.py --bootstrap
export NINJA_PATH=$PWD
sudo apt-get install clang
git clone https://github.com/shizukachan/NNPACK
cd NNPACK
confu setup
NINJA_PATH/ninja
$NINJA_PATH/ninja
\
ls
bin/convolution-inference-smoketest
~
cd ~
$NINJA_PATH/ninja
sudo apt-get install cmake
git clone https://github.com/Idein/qmkl.git
cd qmkl
cmake .
sudo apt-get install flex
git clone https://github.com/Terminus-IMRC/qpu-assembler2
cd qpu-assembler2
make
cd qmkl
cd ~
cd qmkl
cmake .
YOLOv2
./darknet detector test cfg/coco.data cfg/yolo.cfg yolo.weights data/person.jpg
cd darknet/
./darknet detector test cfg/coco.data cfg/yolo.cfg yolo.weights data/person.jpg
wget https://pjreddie.com/media/files/yolov3-tiny.weights
cd darknet
wget https://pjreddie.com/media/files/yolov3-tiny.weights
ls
cd cfg
ls
cd ..
./darknet detector test cfg/coco.data cfg/yolov3-tiny.cfg yolov3-tiny.weights data/person.jpg
cd darknet
wget https://pjreddie.com/media/files/yolov3-tiny.cfg
sudo apt-get update && sudo apt-get dist-upgrade
sudo apt-get install automake libtool vim cmake libusb-1.0-0-dev libx11-dev xorg-dev libglu1-mesa-dev
sudo raspi-config
sudo vi /etc/dphys-swapfile
sudo /etc/init.d/dphys-swapfile restart swapon -s
cd ~
git clone https://github.com/IntelRealSense/librealsense.git
cd librealsense
sudo cp config/99-realsense-libusb.rules /etc/udev/rules.d/ 
sudo su
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
source ~/.bashrc
cd ~
git clone --depth=1 -b v3.10.0 https://github.com/google/protobuf.git
cd protobuf
./autogen.sh
./configure
make -j1
sudo make install
cd python
export LD_LIBRARY_PATH=../src/.libs
python3 setup.py build --cpp_implementation 
python3 setup.py test --cpp_implementation
sudo python3 setup.py install --cpp_implementation
export PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION=cpp
export PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION_VERSION=3
sudo ldconfig
protoc --version
cd ~
wget https://github.com/PINTO0309/TBBonARMv7/raw/master/libtbb-dev_2018U2_armhf.deb
sudo dpkg -i ~/libtbb-dev_2018U2_armhf.deb
sudo ldconfig
rm libtbb-dev_2018U2_armhf.debcd ~
wget https://github.com/PINTO0309/TBBonARMv7/raw/master/libtbb-dev_2018U2_armhf.deb
sudo dpkg -i ~/libtbb-dev_2018U2_armhf.deb
sudo ldconfig
rm libtbb-dev_2018U2_armhf.debcd ~
wget https://github.com/PINTO0309/TBBonARMv7/raw/master/libtbb-dev_2018U2_armhf.deb
sudo dpkg -i ~/libtbb-dev_2018U2_armhf.deb
sudo ldconfig
rm libtbb-dev_2018U2_armhf.debcd ~
wget https://github.com/PINTO0309/TBBonARMv7/raw/master/libtbb-dev_2018U2_armhf.deb
sudo dpkg -i ~/libtbb-dev_2018U2_armhf.deb
sudo ldconfig
rm libtbb-dev_2018U2_armhf.deb
cd ~
wget https://github.com/PINTO0309/TBBonARMv7/raw/master/libtbb-dev_2018U2_armhf.deb
sudo dpkg -i ~/libtbb-dev_2018U2_armhf.deb
sudo ldconfig
rm libtbb-dev_2018U2_armhf.deb
cd ~/librealsense
mkdir  build  && cd build
cmake .. -DBUILD_EXAMPLES=true -DCMAKE_BUILD_TYPE=Release -DFORCE_LIBUVC=true
make -j1
sudo make install
export PYTHONPATH=$PYTHONPATH:/usr/local/lib
source ~/.bashrc
sudo apt-get install python-opengl
sudo -H pip3 install pyopengl
sudo -H pip3 install pyopengl_accelerate==3.1.3rc1
sudo raspi-config
passwd
sudo -
sudo history
sudo
sudo ls
sudo apt-get install puredata
cd openFrameworks/examples/
ls
cd gl
ls
cd textureExample/
make
bin/textureExample 
cd ..
ls
cd..
is
ls
cd ..
ls
cd graphics/
ls
cd imageSubsectionExample/
make -j4
bin/imageSubsectionExample 
cd openFrameworks/apps/myApps/CrestPi/
make
bin/CrestPi