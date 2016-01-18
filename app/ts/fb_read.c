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

//./hyh_fb 1/0
int main(int argc, char *argv[])
{
		int fd, ret;
		struct fb_var_screeninfo var;
		char *fba;
		int i,j;
		printf("hyh test fb in andorid argc:%d\n", argc);
		if (argc == 2) {
				fd = open("/dev/graphics/fb1", O_RDWR);
		}else {
				fd = open("/dev/graphics/fb0", O_RDWR);
		}
		if(fd < 0){
				perror("open");
				exit(1);
		}	

		ret = ioctl(fd, FBIOGET_VSCREENINFO, &var);
		if(ret < 0){
				perror("ioctl");
				exit(1);
		}
#if 1
		printf("------------ lcd info -------------\n");
		printf("-            X*Y: %d*%d\n", var.xres, var.yres);
		printf("-        xoffset: %d  yoffset: %d\n", var.xoffset, var.yoffset);
		printf("- bits_per_pixel: %d\n", var.bits_per_pixel);
		printf("-        red bit: %d,  offset: %d\n", var.red.length, var.red.offset);
		printf("-      green bit: %d,  offset: %d\n", var.green.length, var.green.offset);
		printf("-       blue bit: %d,  offset: %d\n", var.blue.length, var.blue.offset);
#endif
		fba = mmap(NULL, var.xres*var.yres*var.bits_per_pixel>>3, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
		if(fba == MAP_FAILED){
				perror("mmap()");
				exit(-1);
		}

		for(i = 0; i < var.xres; i++){
				for(j = 0; j < var.yres; j++){
							printf(" %#2x ", *(int *)fba);
							if (j == 16)
									puts("\n");
						}	
				}

		return 0;	
}

