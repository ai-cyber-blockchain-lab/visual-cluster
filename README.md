# About
This is a very minimal setup meant to be run on the RPi 3b on a raspian based distribution.

If you found this accidentally, move on, nothing to see here - yet.

## Setup:

Update Memory-split using `raspi-config`. Set Advanced Options -> Memory Split to 256. Turn off proprietary GL driver.

Install required libraries:

`sudo apt-get install make gcc git libjpeg8-dev indent libfreetype6-dev ttf-dejavu-core libraspberrypi-dev`

