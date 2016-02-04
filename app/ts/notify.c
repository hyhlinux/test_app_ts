#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <poll.h>

#define TEST_SYSFS_TRIGGER  "/sys/hello/trigger"
#define TEST_SYSFS_NOTIFY   "/sys/hello/notify"

int main(int argc, char **argv)
{
	int cnt, notifyFd, triggerFd, rv;
	char attrData[100];
	struct pollfd ufds[2];

	// Open a connection to the attribute file.
	if ((notifyFd = open(TEST_SYSFS_NOTIFY, O_RDWR)) < 0)
	{
		perror("Unable to open notify");
		exit(1);
	}
	// Open a connection to the attribute file.
	if ((triggerFd = open(TEST_SYSFS_TRIGGER, O_RDWR)) < 0)
	{
		perror("Unable to open trigger");
		exit(1);
	}

	ufds[0].fd = notifyFd;
	ufds[0].events = POLLIN;
	ufds[1].fd = triggerFd;
	ufds[1].events = POLLIN;

	// Someone suggested dummy reads before the poll() call
	cnt = read( notifyFd, attrData, 100 );
	cnt = read( triggerFd, attrData, 100 );
	ufds[0].revents = 0;
	ufds[1].revents = 0;
	if (( rv = poll( ufds, 2, 10000)) < 0 )
	{
		perror("poll error");
	}
	else if (rv == 0)
	{
		printf("Timeout occurred!\n");
	}
	else if (ufds[0].revents & POLLIN)
	{
		printf("triggered\n");
		cnt = read( notifyFd, attrData, 1 );
		printf( "Attribute file value: %02X (%c) [%d]\n", attrData[0], attrData[0], cnt );
	}
	printf( "revents[0]: %08X\n", ufds[0].revents );
	printf( "revents[1]: %08X\n", ufds[1].revents );

	close( triggerFd );
	close( notifyFd );
}
