#!/bin/sh

#source ~/.bashrc
#arm-linux-gnueabihf-gcc --static $1
#adb remount 
adb push evtest_arm  /system/bin/hyh_ts
#adb push a.out  /system/bin/hyh_ts
#adb shell; cd /system/bin/
#chmod 777 hyh_ts
 

