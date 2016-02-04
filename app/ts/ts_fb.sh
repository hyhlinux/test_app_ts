#!/bin/bash  
ts_get_ponit(){
	while [ 1 ]; do
	#dmesg -c | grep  -E  "Power-Key|synaptics,s3320|gesture_buffer|s1302|int|button_key|report|TP|resume|suspend"
	dmesg -c | grep  -E  "Power-Key|synaptics,s3320|s1302|report|TP|resume|suspend"
		int_change
	done
}

int_change(){
	s1302_new=`cat /proc/interrupts | grep -E "synaptics,s1302"`
	s3320_new=`cat /proc/interrupts | grep -E "synaptics,s3320"`
	fpc_new=`cat /proc/interrupts | grep -E "spi12.0"`
#
	if [ "$s1302_new" = "$s1302_old" ];then 
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

if [ "$fpc_new" = "$fpc_new" ];then 
		sleep 0.01
	else
		fpc_old=$fpc_new
		echo $fpc_old 	
	fi
}

path_proc_s1302=/proc/s1302
debug_log_on(){
echo "open key_rep/virtual_key/debug"
echo 1 > /sys/bus/i2c/drivers/synaptics,s3320/tp_debug_log
#echo 1 > $path_proc_s1302/key_rep
#echo 1 > $path_proc_s1302/virtual_key
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
#ts_get_ponit
debug_log_on
ts_get_ponit



