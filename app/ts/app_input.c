#include <stdio.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>

#define ARG 0
#if ARG
	static struct input_event event;
	void  check(void);
#else 
	void  check(struct input_event event);
#endif

int main(int argc, char **argv)
{
	int i, ret;

	struct input_event event;

	printf("hyh test in android\n");
	char *devices[] = {
		"/dev/input/event0", 
		"/dev/input/event1", 
		"/dev/input/event2", 
	};
	

	struct pollfd fdsets[sizeof(devices)/sizeof(devices[0])];

	for(i = 0; i < sizeof(devices)/sizeof(devices[0]); i++){
		fdsets[i].fd = open(devices[i], O_RDONLY);
		if(fdsets[i].fd < 0){
			perror("open");
			exit(1);
		}
		fdsets[i].events = POLLIN;
	}		

	for(;;){
		printf("bf poll\n");
		ret = poll(fdsets,sizeof(devices)/sizeof(devices[0]), -1);
		if(ret < 0){
			perror("poll");
			exit(1);
		}else{
			for(i = 0; i < sizeof(devices)/sizeof(devices[0]); i++){
				if(fdsets[i].revents & POLLIN){
					ret = read(fdsets[i].fd, (void *)&event, sizeof(event));
					if(ret < 0){
						perror("read");
						exit(1);
					}else{
#if ARG
						check();
#else 
						check(event);
#endif 

					}

				}
			}
		}	
	}

	return 0;
}

#if ARG
	void  check(void)
#else 
void  check(struct input_event event)
#endif 
{
	switch(event.type){
		case EV_SYN:
			printf("------- sync -------\n");
			break;
		case EV_KEY:
			if(event.value){
				printf("KEY: %d press down!\n", event.code);
			}else{
				printf("KEY: %d release up!\n", event.code);
			}
			break;
		case EV_ABS:
			if((event.code == ABS_X) || (event.code == ABS_MT_POSITION_X)){
				printf("ABS: x = %d\n", event.value);
			}else if((event.code == ABS_Y) ||  (event.code == ABS_MT_POSITION_Y)){
				printf("ABS: y = %d\n", event.value);
			}
			break;
		case EV_REL:
			if(event.code == REL_X){
				printf("REL: x = %d\n", event.value);
			}else if(event.code == REL_Y){
				printf("REL: y = %d\n", event.value);
			}
			break;
		default:
			break;
	}
}
