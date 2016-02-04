
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


int ftm_at_init(void)
{
	int rc;

	rc = power_set_cannot_sleep();
	if(rc < 0)
		goto end;

	rc = tp_suspend();
	if(rc < 0)
		printf("tp_suspend fail with %d\n", rc);
	rc = ftm_lcd_init();
	if(rc < 0)
		printf("ftm_lcd_init fail with %d\n", rc);

//	rc = at_lcd_backlight_control(&(ftm_test_configs[LCD_BACKLIGHT]), 0);
	if(rc < 0)
		goto end;
	sleep(2);
end:
	return 0;
}

//at 
struct at_test_item at_test_items[] = {
//	{"help", "H",	at_print_commands},
//	{"lcd_backight_on",	"AT+EDFT=0,5",	at_lcd_backlight_on},
//	{"lcd_backight_off",	"AT+EDFT=0,0",	at_lcd_backlight_off},
	{"sleep_enable",	"AT+ESLP=1",	at_sleep_enable},
	{"sleep_disable",	"AT+ESLP=0",	at_sleep_disable},
	{NULL,	"AT+EXIT=1",	NULL},
};

static int at_parse(char buf[BUFFER_SIZE])
{
	uint i;
	int at_func_args_select;
	int ret = E_SUCCESS;
	pthread_t t;

	for (i = 0; i < ARRAY_SIZE(at_test_items); i++) {
		if (!strncmp(buf, at_test_items[i].cmd, strlen(at_test_items[i].cmd))) {
			if (at_test_items[i].name == NULL){
				at_send_result(__func__, "exit_at_thread\n");
				exit_at_thread = true;
				goto out;
			}
			printf("hyh:  create  cmd %s\n",at_test_items[i].name);
			ret = pthread_create(&t, NULL, at_test_items[i].func, NULL);
			if (E_SUCCESS != ret){
				LOGE("thread create error at cmd %s\n",at_test_items[i].name);
				goto out;
			}
		}
	}
out:
	return ret;
}

#if 1
int main(void)
{
	at_sleep_enable();

	//do_fb_notifier();
	return 0;
}
#else 
int main(int argc, char* argv[])
{
	int ftm_at_thread_create_retry = 0;
	int ftm_at_thread_create_result = E_SUCCESS;
	int ftm_at_thread_join_result = E_SUCCESS;
	int ret;


	ret = ftm_at_init();
	if(ret < 0){
		printf("ftm_at_init faiure with ret = %d\n",ret);
		goto dead;
	}

ftm_at_thread_create:
	ftm_at_thread_create_result = ftm_at_create_thread(&ftm_at_thread);
	if (ftm_at_thread_create_result != E_SUCCESS)
	{
		ftm_at_thread_create_retry++;
		if (ftm_at_thread_create_retry < FTM_AT_THREAD_CREATE_MAX_RETRY)
			goto ftm_at_thread_create;
		else
			printf("try to create at thread %d times still failed\n", FTM_AT_THREAD_CREATE_MAX_RETRY);
	}
	printf("watting ftm_at_thread finish\n");

	ftm_at_thread_join_result = pthread_join(ftm_at_thread, NULL);

	if (ftm_at_thread_join_result != E_SUCCESS)
		printf("ftm_at_thread finish error\n");
	else
		printf("ftm_at_thread finish success\n");

	ftm_at_deinit();
	printf("exit at current test\n");

dead:
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

	ret = file_write_int(POWER_WAKE_LOCK_FILE, 1);
	if (ret < 0)
		printf("power_set_cannot_sleep failed %d\n", ret);
	else
		printf("power_set_cannot_sleep success\n");
	return ret;

}
int power_enter_sleep(void)
{
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
//tp
int tp_suspend(void)
{
	return file_write_int(TP_SUSPEND_FILE, 0);
}

int at_lcd_backlight_control(struct ftm_test_device_config * config, bool enable)
{
	printf("%s\n",__func__);
	if(enable){
//		ftm_lcd_on();
		//file_write_int(config->dev_path, config->data0?:FLASH_DEFAULT_BACKLIGHT_BRIGHTNESS);
	}else{
//		ftm_lcd_off();
		//file_write_int(config->dev_path, 0);
	}

	return 0;
}
//lcd
static void * at_lcd_backlight_on(void * cookie)
{
//	struct ftm_test_device_config * config = cookie;
	if(at_lcd_backlight_control(config,1) < 0)
		//at_send_result(__func__, AT_RESULT_ERROR);
	else
		//at_send_result(__func__, AT_RESULT_OK);

	pthread_exit(NULL);
	return NULL;
}


