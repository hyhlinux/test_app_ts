#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/inotify.h>
//#include <sys/limits.h>
#include <sys/poll.h>
#include <linux/input.h>
#include <errno.h>
#include <unistd.h>


enum {
	PRINT_DEVICE_ERRORS     = 1U << 0,
	PRINT_DEVICE            = 1U << 1,
	PRINT_DEVICE_NAME       = 1U << 2,
	PRINT_DEVICE_INFO       = 1U << 3,
	PRINT_VERSION           = 1U << 4,
	PRINT_POSSIBLE_EVENTS   = 1U << 5,
	PRINT_INPUT_PROPS       = 1U << 6,
	PRINT_HID_DESCRIPTOR    = 1U << 7,
	PRINT_ALL_INFO          = (1U << 8) - 1,
	PRINT_LABELS            = 1U << 16,
};

static void usage(char *name);

int main(int argc, char *argv[])
{

	int c;
	const char *device_path = "/dev/input";

	do {
		c = getopt(argc, argv, "tns:Sv::dpilqc:rh");
		if (c == EOF)
			break;
		switch (c) {
			case 't':
				printf("not achieve\n");
				break;
			case 'n':
				printf("not achieve\n");
				break;
			case 's':
				printf("not achieve\n");
				break;
			case 'S':
				printf("not achieve\n");
				break;
			case 'v':
				printf("not achieve\n");
				break;
			case 'd':
				printf("not achieve\n");
				break;
			case 'p':
				printf("not achieve\n");
				break;
			case 'i':
				printf("not achieve\n");
				break;
			case 'l':
				print_flags |= PRINT_LABELS;
				break;
			case 'r':
			 	sync_rate = 1;
				break;
			case 'q':
				printf("not achieve\n");
				break;
			case 'c':
				printf("not achieve\n");
				break;
			case '?':
				printf("not achieve\n");
			case 'h':
				usage(argv[0]);
				exit(1);
		}
	} while (1);

	return 0;
}

static void usage(char *name)
{
	fprintf(stderr, "Usage: %s [-t] [-n] [-s switchmask] [-S] [-v [mask]] [-d] [-p] [-i] [-l] [-q] [-c count] [-r] [device]\n", name);
	fprintf(stderr, "    -t: show time stamps\n");
	fprintf(stderr, "    -n: don't print newlines\n");
	fprintf(stderr, "    -s: print switch states for given bits\n");
	fprintf(stderr, "    -S: print all switch states\n");
	fprintf(stderr, "    -v: verbosity mask (errs=1, dev=2, name=4, info=8, vers=16, pos. events=32, props=64)\n");
	fprintf(stderr, "    -d: show HID descriptor, if available\n");
	fprintf(stderr, "    -p: show possible events (errs, dev, name, pos. events)\n");
	fprintf(stderr, "    -i: show all device info and possible events\n");
	fprintf(stderr, "    -l: label event types and names in plain text\n");
	fprintf(stderr, "    -q: quiet (clear verbosity mask)\n");
	fprintf(stderr, "    -c: print given number of events then exit\n");
	fprintf(stderr, "    -r: print rate events are received\n");
}

