


1.编译放到oneplus,开始测试.
hyh@hyh-OptiPlex-9020:~/workspace/test/app/ts$ arm-linux-gnueabihf-gcc --static evtest.c 
hyh@hyh-OptiPlex-9020:~/workspace/test/app/ts$ adb push a.out  /system/bin/hyh_ts
920 KB/s (518971 bytes in 0.550s)
hyh@hyh-OptiPlex-9020:~/workspace/test/app/ts$ 



2.同时打开内核触摸屏中断中上报数据进行检测,使用dmesg -c 找到对应的信息。
adb shell; sh /system/bin/ts.sh


3. getevent -lr 监听input事件。




evtest 可以在检测时间，和上报的坐标值，更接近kernel。


