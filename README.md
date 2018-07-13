# About

This is a very minimal setup meant to be run on the RPi 3b on a raspian based distribution.

If you found this accidentally, move on, nothing to see here - yet.


## Setup
This code needs raylib. perform the following steps for installation (takes a while, because raylib repo is big):

```
sudo apt-get git cmake make libraspberrypi-dev raspberrypi-kernel-headers g++

git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_RPI
sudo make PLATFORM=PLATFORM_RPI install
```

Update Memory-split using `raspi-config`. Set Advanced Options -> Memory Split to 256. Turn on proprietary GL driver.
