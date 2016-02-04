
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <termios.h>


#include "ftm_common.h"

int file_write_int(char const* path, int value);
//===========================power
#define POWER_ENTER_SLEEP_FILE  "/sys/power/state"
#define POWER_WAKE_LOCK_FILE "/sys/power/wake_lock"
#define POWER_UNWAKE_LOCK_FILE "/sys/power/wake_unlock"
#define TP_SUSPEND_FILE "/sys/class/input/input0/suspend"
int power_enter_sleep(void);
int power_set_cannot_sleep(void);
int power_set_can_sleep(void);
//===========================fb
#define ANDROID_FB0 "/dev/graphics/fb0"
#define FB_BLANK_POWERDOWN	4
#define FBIOBLANK		0x4611
static void do_fb_notifier();
//===========================tp
int tp_suspend(void);
//===========================at
static void * at_sleep_enable(void * cookie);
static void * at_sleep_disable(void * cookie);

#if 1 
int main(void)
{
	//at_sleep_enable(NULL);
	do_fb_notifier();
	printf("will disale at");
	sleep(10);
	//at_sleep_disable(NULL);


	//do_fb_notifier();
	return 0;
}

#endif

static void do_fb_notifier()
{
	int fb_fd = -1;
	int ret = -1;
	printf("hyh %s\n",__func__);
	fb_fd = open(ANDROID_FB0, O_RDWR);
	if (fb_fd < 0) {
		printf("cannot open fb %s\n",ANDROID_FB0);
		//LOGE("cannot open fb %s\n",ANDROID_FB0);
		return;
	}

	ret = ioctl(fb_fd, FBIOBLANK, FB_BLANK_POWERDOWN);
	if (ret  < 0) {
		//LOGE("ioctl FBIOBLANK failure %d\n",ret);
		printf("ioctl FBIOBLANK failure %d\n",ret);
		goto out;
	}
	sleep(1);
out:
	close(fb_fd);
}
//power
int power_set_can_sleep()
{
	int ret;

	printf("%s\n",__func__);
	ret = file_write_int(POWER_UNWAKE_LOCK_FILE, 1);
	if (ret < 0)
		printf("power_set_can_sleep failed %d\n", ret);
	else
		printf("power_set_can_sleep success\n");
	return ret;
}
int power_set_cannot_sleep()
{
	int ret;

	printf("%s\n",__func__);
	ret = file_write_int(POWER_WAKE_LOCK_FILE, 1);
	if (ret < 0)
		printf("power_set_cannot_sleep failed %d\n", ret);
	else
		printf("power_set_cannot_sleep success\n");
	return ret;

}
int power_enter_sleep(void)
{
	printf("%s\n",__func__);
	//	return autosuspend_enable();
	return 0;
}
//com
int file_write_int(char const* path, int value)
{
	int fd = -1;
	int ret = E_SUCCESS;
	if (path == NULL)
		return -E_FILE_NULL_PTR;

	fd = open(path, O_RDWR);
	if (fd < 0)	{
		printf("fail to open file %s\n", path);
		ret = -E_FILE_OPEN_FAIL;
	}else	{
		char buffer[20];
		int bytes = sprintf(buffer, "%d\n", value);
		ret = write(fd, buffer, bytes);
		printf("hyh2   %s\n", path);
		if (ret <= 0)		{
			printf("fail to write file %s\n", path);
			ret = -E_FILE_WRITE_FAIL;
		}
		close(fd);
	}
	return ret;
}
//at
static void * at_sleep_enable(void * cookie)
{
	//struct ftm_test_device_config * config = cookie;
	printf("%s\n",__func__);

	do_fb_notifier();
	power_set_can_sleep();
	//at_send_result(__func__, AT_RESULT_OK);
	power_enter_sleep();

	//pthread_exit(NULL);
	return NULL;
}
static void * at_sleep_disable(void * cookie)
{
//	struct ftm_test_device_config * config = cookie;
	printf("%s\n",__func__);

	power_set_cannot_sleep();
//	at_send_result(__func__, AT_RESULT_OK);
//	pthread_exit(NULL);
	return NULL;
}
//tp
int tp_suspend(void)
{
	return file_write_int(TP_SUSPEND_FILE, 0);
}
