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
		int_change
	done
}


int_change(){
	s1302_new=`cat /proc/interrupts | grep -E "synaptics,s1302"`
	s3320_new=`cat /proc/interrupts | grep -E "synaptics,s3320"`

	#echo $s1302_new
	#echo $s3320_new
#
	if [ "$s1302_new" = "$s1302_old" ];then 
	#	usleep 1000000*60
		sleep 0.01
	else 
		s1302_old=$s1302_new
		echo "-----------------"
		echo $s1302_old 
	fi
#
	if [ "$s3320_new" = "$s3320_old" ];then 
		sleep 0.01
	else
		s3320_old=$s3320_new
		echo $s3320_old 	
	fi
}
echo "start....."
#ts_get_ponit&
ts_get_ponit
#int_change 


	



