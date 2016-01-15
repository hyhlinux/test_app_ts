#!/bin/bash  

#########################
#use: 
#1.	adb shell
#2.	sh /.../ts.sh
#
#########################
ts_get_ponit(){
	while [ 1 ]; do
		dmesg -c | grep  -E  "hyh|synaptics,s3320|gesture_buffer|s1302|int|button_key"
	done
}

echo "start....."
#ts_get_ponit&
ts_get_ponit



