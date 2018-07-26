# About

This is a very minimal setup meant to be run on the RPi 3b on a raspian based distribution.

If you found this accidentally, move on, nothing to see here - yet.


## Setup
This setup needs go and raylib. Unfortunately this currently doesn't work as raylib-go isn't updated to the 
current raylib version.

```
sudo apt-get install git cmake make libraspberrypi-dev raspberrypi-kernel-headers g++

sudo apt-get install go-lang
export PLATFORM=PLATFORM_RPI
GOPATH=/home/pirate/go go get -v -u github.com/gen2brain/raylib-go/raylib
```

Update Memory-split using `raspi-config`. Set Advanced Options -> Memory Split to 256. Turn on proprietary GL driver.
