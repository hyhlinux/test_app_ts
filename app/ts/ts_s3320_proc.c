#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>



int main(void)
{
	int fd;
	char c;
	char cmd[64];
	char tmp[128];

	printf("hello\n ");
	while(1) {
		//step1
		printf("input:path\n");
		scanf(" %s", &cmd);

		sprintf(tmp, "/proc/touchpanel/%s",cmd);
		puts(tmp);
		//
		fd = open(tmp, O_RDWR);
		if(fd < 0) {
			perror("open()");
			exit(-1);
		}
		memset(tmp, 0, sizeof(tmp));

		//step2
		printf("input:c\n");
		scanf(" %c", &c);

		printf("input:%c\n",c);

		if(write(fd, &c, 1) < 0) {
			perror("write()");		
			exit(-1);
		}
		fd=-1;
	}

	return 0;
}
