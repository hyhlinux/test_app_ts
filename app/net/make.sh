if [ -f a.out ]; then 
	echo "rm old a.out"
	rm a.out
fi
echo "arm $1"
src=$1.c
adb remount
arm-linux-gnueabihf-gcc -static $src
echo "sudo adb push a.out  /data/hyh_$1"
sleep 2
#sudo adb push a.out  /data/hyh_$1
adb push a.out  /data/hyh_$1
