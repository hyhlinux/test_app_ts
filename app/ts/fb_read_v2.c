//2015年 12月 01日 星期二 15:09:35 CST

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include<math.h>

//./hyh_fb 1/0 std:on/off
void read_fb_file(int x, int y, void *addr);
int main(int argc, char *argv[])
{
		int fd, fd_tmp, ret;
		struct fb_var_screeninfo var;
		char *fba;
		int i,j;
		printf("hyh test fb in andorid argc:%d\n", argc);

		if (argc != 3) {
			perror("us:./a.out fd[0/1]on [stdout:]on/off");	
			exit(-1);
		}
		if (strncpy(argv[1], "fd1on", 5) == 0) {
				fd = open("/dev/graphics/fb1", O_RDWR);
		} else {
				fd = open("/dev/graphics/fb0", O_RDWR);
		}
		if(fd < 0){
				perror("open");
				exit(1);
		}	
		

		fd_tmp = open("/data/tmp_fb",O_CREAT | O_RDWR, 0777);
		if(fd_tmp < 0){
				perror("open2");
				exit(1);
		}	

	printf("hello\n");
		if (strncpy(argv[2], "off", 2) == 0) {
			if(dup2(fd_tmp,1) < 0) {
				perror("dup2()");
				exit(1);
			}
		}
	printf("hello\n");

#if 1
		ret = ioctl(fd, FBIOGET_VSCREENINFO, &var);
		if(ret < 0){
				perror("ioctl");
				exit(1);
		}
		printf("------------ lcd info -------------\n");
		printf("-            X*Y: %d*%d\n", var.xres, var.yres);
		printf("-        xoffset: %d  yoffset: %d\n", var.xoffset, var.yoffset);
		printf("- bits_per_pixel: %d\n", var.bits_per_pixel);
		printf("-        red bit: %d,  offset: %d\n", var.red.length, var.red.offset);
		printf("-      green bit: %d,  offset: %d\n", var.green.length, var.green.offset);
		printf("-       blue bit: %d,  offset: %d\n", var.blue.length, var.blue.offset);

		fba = mmap(NULL, var.xres*var.yres*var.bits_per_pixel>>3, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		if(fba == MAP_FAILED){
				perror("mmap()");
				exit(-1);
		}

		
		while(1) {
			sleep(0.1);
			read_fb_file(var.xres, var.yres, fba);			
			system("date >> ./tmp_fb");
			puts("\n");
		}


#endif

		close(fd_tmp);
		close(fd);
		return 0;	
}

void read_fb_file(int x, int y, void *addr) 
{
	int i,j;

	//for(i = 0; i < var.xres; i++){
	for(i = 0; i < x; i++){
		//for(j = 0; j < var.yres; j++){
		for(j = 0; j < y; j++){
			int tmp = ((int*)addr)[i*x+j];
//				printf("%#2x ", tmp);
//			if(write(1, &tmp, 4) < 0) {
//				perror("write()");		
//				exit(-1);
//			}
			if (tmp)
				printf("%#2x ", tmp);
			if (j == 16)
				puts("\n");
		}	
	}

}
