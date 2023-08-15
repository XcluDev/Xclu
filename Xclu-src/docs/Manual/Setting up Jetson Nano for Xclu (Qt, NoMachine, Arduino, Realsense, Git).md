Here we will discuss how set up **Jetson Nano (A)** for running Xclu and more, including:
1. Create SD card and install Ubuntu 
2. Starting Nano: power supply, display, keyboard and mouse
3. Connect to Internet, enable sound
4. Disable sleeping, start fan
5. Install NoMachine for remote access from Windows Machine and setup screen size
6. Install Git with GUI and download Xclu
7. Install Qt and Qt Creator for building Xclu
8. Install Arduino IDE for connecting Arduino
9. Install Realsense SDK for using Realsense cameras
10. Shutting down command
11. (Optionally - install openFrameworks for developing)
12. Go to 5 Watt mode if powering from USB


## 1. Create SD card and install OS to Jetson Nano
Requirements: **32 Gb microSD card**, **UHC-1 (Class 10)**, for example, Samsung Evo.
Official guide: https://developer.nvidia.com/embedded/learn/get-started-jetson-nano-devkit#intro 

You need laptop for preparing SD card. Here is all required for Windows laptop: https://drive.google.com/drive/folders/14aEbz9yeqb33D5jzowlb7WurXQk_p44e?usp=sharing

*  `nv-jetson-nano-sd-card-image-r32.4.2.zip`  - need to unzip it to `sd-blob-b01.img`
*  balenaEtcher-Setup-1.5.99 - run and choose "Flash from file", select `sd-blob-b01.img` - and it will be written to SD card. 

In this way, you will get Ubuntu 18.04 LTS on the SD card.


## 2. Starting Nano: power supply, display, keyboard and mouse

1. Put this SD card inside Nano.
2. Connect power supply to Nano. 
* You may use power by Micro USB, 5V, 2A or more (less power can be not enough for Realsense powering). In this case, you need immediately put Nano into "5W" mode by command
`sudo nvpmodel -m 1`
Also this setting can be done by pressing using NVidia icon in the right top part of the window. 
**Note**: if you are using Micro USB and not put Nano into 5W mode - your Nano will hangs out occasionally!
(See more at https://desertbot.io/blog/jetson-nano-power-supply-barrel-vs-micro-usb)

* When it's possible, I recommend to use separate power supply 5V 4A (2.1mm). For using it instead of USB, you need to place a jumper number 48 on Jetson Nano board. Particular place for jumper is titled on the board as *ADD JUMPER TO DISABLE USB PWR*. In this case Nano may work in "10W" mode,
`sudo nvpmodel -m 0` (it's default mode, so normally no special actions is required).

3. Connect display. Good news: you can ALL displays, using HDMI and Display port available outputs. For me was important what it can be used Display Port - VGA (D-Sub) cable to connect old VGA (D-Sub) display!
4. Connect USB keyboard and mouse. It can be wired, but also for me works Logitect wireless devices. Also you may use USB hub to save USB Nano outputs for bit-rate devices such as sound card and cameras. 
5. Enable power and start Jetson Nano!

## 3. Connect to Internet, enable sound
Connect Nano to Internet using LAN cable or Wifi module.
For me works TP-Link Wifi module (TL-WN822N Ver. 3.0).

Connect some USB sound card. For me works Espada USB 2.0 Sound Adapter USB. 
Press "Speakers" icon at right top part of the desktop and choose device, and test it’s working by pressing "Test" button. 

## 4. Disable sleeping, start fan

To disable sleeping, press "Gear" icon at right top part of the desctop, go to  "System Settings", Brightness & Lock, and disable locking: 
* Turn screen off -> Never,
* Lock -> OFF

If Jetson Nano has fan and became hot, you may enable fan at maximal speed by starting Terminal and typing

    sudo /usr/bin/jetson_clocks 

To make fan slower, use this:

    echo 100 | sudo tee /sys/devices/pwm-fan/target_pwm
The value "100" is PWM value, so, "0" will stop fan, "255" will start at maximal speed again.

## 5. Install NoMachine for remote access from Windows Machine 
Here is all you need: https://drive.google.com/drive/folders/1kTBcpoYyc4brXm4I95A9ZC7jUIW4CQgB?usp=sharing

(or download  https://www.nomachine.com/AR02R01074)
 
Run `sudo dpkg -i nomachine_6.11.2_1_arm64.deb`  

After that, you can install NoMachine on Windows (nomachine_6.11.2_1.exe) and connect to Nano, and control it from Windows:
* Get local IP address of Jetson by typing in Terminal `ifconfig` or by pressing NoMachine icon in Jetson's right top part of the desktop.
* Click NoMachine icon at Windows right bottom part of desktop and choose "New connection" and type IP there.
* Connect! :slight_smile:
* Note: you may use computer's name instead IP - it's preferrable for connecting your Nano in headless mode (that is without display) using wired LAN connection, without knowing its IP address.

If you are using barrel-power (non-MicroUSB), you may connect to Nano via USB:
https://desertbot.io/blog/jetson-nano-micro-usb-login

#### Show menu, enable audio transferring
To show NoMachine menu, at first connect to Jetson, then press Ctrl+Alt+0.

To enable audio transferring, go to NoMachine Menu -> Audio -> Enable sound.

#### Setting screen size
If connect to Jetson without display, the resolution is 640x480. To change it, type in Terminal:

    xrandr --fb 1280x720

After that, reconnect NoMachine.
Just to check current resolution, type just `xrandr`.

#### Setting screen quality
If screen transfer often freezes, I recommend to do the following at NoMachine display settings menu:
* Set solid color to background by clicking right mouse button on the desktop and choosing "Change background".
* Disable "high quality" visual effects: on the Background changing window, switch from "Look" to "Behavior" tab, and set "Visual effect" to "Low".
* Go to NoMachine Display settings, and set "Quality" slider to lower value.
* Also disable there "Adopt quality to connection" checkbox.

#### Setting "Windows-style" menu behavior

To make menu's looking as in Windows:
1. Go to "Change Background" from desktop's context menu and switch to "Behavior" tab.
2. Set "Show menus for a window" at "In the window's title bar"
3. Set "Menus visibility"  to "Always displayed"

## 6. Install Git with GUI and download Xclu

    sudo apt update
    sudo apt-get install git-gui
    sudo apt-get install gitk

Check Git version:
    
    git --version

Run Git GUI: 
  
    git gui

- there you can clone Xclu, by specifying `https://github.com/XcluDev/Xclu.git`

Also, you will be asked to choose folder to clone Xclu - choose for example `Desktop/Xclu`.

#### About `git pull`
Using `git gui` you can choose files to commit by clicking their left corner, then commit and push changes.
But `pull` is not working for me, so I use Terminal for that:
1. Right-click folder and choose "Open in Terminal"
2. (Choose branch to pull, this command only one time needed:)
    `git branch --set-upstream-to=origin/master master`
3. `git pull`


## 7. Install Qt and Qt Creator for building Xclu
Right-click mouse on desktop and click “Open Terminal” 

In Terminal type: 

    sudo apt update  
    sudo apt-get install qt4-default 
    sudo apt-get install qt5-default 
    sudo apt-get install qtcreator 
    sudo apt-get install libqt5* 
    #(sudo apt-get install libqt5serialport*)
    sudo apt-get install qt*-dev
    #(sudo apt-get install qt4)
    apt-cache search qt*multimedia
    sudo apt-get install qtmultimedia5-dev
    sudo apt-get install qtbase5-examples qtbase5-doc-html
    

After that you can build, for example, Xclu, but set up using Qt5 in Qt Creator:
Projects -> Manage Kits -> Build & Run -> Kits -> Desktop -> Qt version - set to Qt 5.xx.xx.

After that you can build and run Xclu.

## 8. Install Arduino IDE for connecting Arduino
1. Go to https://arduino.cc - "Download" and dowload "Linux Arm x64", or download here:
https://drive.google.com/drive/folders/1hME6nGMbStnB8-PsYaeRe8IcjVL40Rcl?usp=sharing

2. Unzip, go into it and type in Terminal 
    `./arduino-linux-setup.sh $USER`
     `sudo ./install.sh`
3. Now you can run Arduino IDE from applications list. 
When connecting Arduino board, normally it's required to choose `/dev/ttyUSB0` port.

## 9. Install Realsense SDK for using Realsense cameras

follow https://github.com/IntelRealSense/librealsense/blob/master/doc/installation_jetson.md 

    sudo apt-key adv --keyserver keys.gnupg.net --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE || sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE 

    sudo add-apt-repository "deb http://realsense-hw-public.s3.amazonaws.com/Debian/apt-repo bionic main" -u 
    sudo apt-get install librealsense2-dev 
    sudo apt-get install librealsense2-utils 

Connect Realsense camera D415 or D435 and test it by running viewer: 

    realsense-viewer

## 10. Shutting down command

```
sudo shutdown -h now
```
(From https://desertbot.io/blog/jetson-nano-micro-usb-login)


## 11. (Install openFrameworks for developing)
(Not tested, but keep it here for now:) https://gist.github.com/madelinegannon/237733e6c114f156b31366f47c1f3d32

## 12. Go to 5 Watt mode if powering from USB
(Based on https://desertbot.io/blog/jetson-nano-power-supply-barrel-vs-micro-usb)

If you plan to use Jetson autonomously and powering it from powerbank, put Jetson to low-power mode in order to avoid sudden turning-off due not sufficient power. Of course, Jetson will work slower.

To set up 5 Watt mode (less power) use the following command:
```
sudo nvpmodel -m 1
```
After this, you will see tip "5W" at the top right corner of the desktop.

To set up 10 Watt mode (more power) use this command:
```
sudo nvpmodel -m 0
```

Check current mode:
```
sudo nvpmodel -q
```