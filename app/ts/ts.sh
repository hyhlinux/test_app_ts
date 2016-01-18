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

##########################################
# open debug log
# virtual_key
# key_rep
##########################################
path_proc_s1302=/proc/s1302

debug_log_on(){
echo "open key_rep/virtual_key/debug"
echo 1 > /sys/bus/i2c/drivers/synaptics,s3320/tp_debug_log
echo 1 > /sys/bus/i2c/drivers/synaptics,s3320/tp_debug_log
echo 1 > $path_proc_s1302/key_rep
echo 1 > $path_proc_s1302/virtual_key
echo 1 > $path_proc_s1302/debug 
}
debug_log_off(){
echo "close key_rep/virtual_key/debug"
echo 0 > /sys/bus/i2c/drivers/synaptics,s3320/tp_debug_log
echo 0 > /sys/bus/i2c/drivers/synaptics,s3320/tp_debug_log
echo 0 > $path_proc_s1302/key_rep
echo 0 > $path_proc_s1302/virtual_key
echo 0 > $path_proc_s1302/debug 
}



#ts_get_ponit&
#int_change 


echo "start....."

info_ts(){
	echo "******hyh*****"
	echo $#
	echo "---------$1" 
	echo $2 
	echo $3 

	if [ "$1" = "on" ];then
		log_flag="on"
	else 
		log_flag="off"
	fi

	if [ "$2" = "on" ];then
		vk_flag="on"
	else 
		vk_flag="off"
	fi

	if [ "$3" = "on" ];then
		kr_flag="on"
	else 
		kr_flag="off"
	fi
	echo "==================="
	echo $log_flag 
	echo $vk_flag 
	echo $kr_flag 
	echo "==================="
}
# sh ./test.sh $1 $2 ...
# $1    on/off  ---log
# $2    on/off  ---vir_key
# $3    on/off  ---key_rep
info_ts 
#ts_get_ponit

