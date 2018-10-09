# About

This is a very raylib + libmicrohttpd setup meant to be run on the RPi 3b on a raspian based distribution.

If you found this accidentally, move on, nothing to see here - yet.


## Setup
This code needs raylib and libmicrohttpd as dependency. libmicrohttpd is fortunately available as a package. Raylib has to be compiled for use without X windows.

Perform the following steps for installation:

```
sudo apt-get update
sudo apt-get upgrade
sudo apt-get remove bluez pi-bluetooth
sudo apt-get install -y git cmake make libraspberrypi-dev raspberrypi-kernel-headers g++ libmicrohttpd-dev

#takes a while, because raylib repo is big
git clone https://github.com/raysan5/raylib.git
cd raylib/src
git checkout 2.0.0
PLATFORM=PLATFORM_RPI make PLATFORM=PLATFORM_RPI
sudo make PLATFORM=PLATFORM_RPI install
```

Update Memory-split using `raspi-config`. Set Advanced Options -> Memory Split to 256. Select legacy GL driver.
