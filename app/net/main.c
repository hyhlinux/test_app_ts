#include <fcntl.h> 
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <linux/netlink.h>


//#include "uevent.h"
//#include "ueventd_parser.h"
#define UEVENT_MSG_LEN  2048


/*********************************************************************/
struct uevent {
	const char *action;
	const char *path;
	const char *subsystem;
	const char *firmware;
	const char *partition_name;
	const char *device_name;
	int partition_num;
	int major;
	int minor;
};
static int device_fd = 0;
/*********************************************************************/
ssize_t uevent_kernel_multicast_recv(int socket, void *buffer, size_t length);
ssize_t uevent_kernel_multicast_uid_recv(int socket, void *buffer, size_t length, uid_t *uid);
ssize_t uevent_kernel_recv(int socket, void *buffer, size_t length, int require_group, uid_t *uid);
int uevent_open_socket(int buf_sz, int passcred);
void handle_device_fd(void);
static void parse_event(const char *msg, struct uevent *uevent);
/*********************************************************************/

int main(int argc, char **argv)
{
	struct pollfd ufd;
	ufd.events = POLLIN;
	ufd.fd = uevent_open_socket(256*1024, 1);
	device_fd = ufd.fd;
	printf("ufd.fd ..%d\n", ufd.fd);

	while (1) {
		ufd.revents = 0;
		int nr = poll(&ufd, 1, -1);
		if (nr <= 0) {
			continue;
		}
		if (ufd.revents & POLLIN) {
			//	printf("ok...\n");
			handle_device_fd();
		}
	}

	return 0;
}

ssize_t uevent_kernel_multicast_recv(int socket, void *buffer, size_t length)
{
	uid_t uid = -1;
	return uevent_kernel_multicast_uid_recv(socket, buffer, length, &uid);
}

ssize_t uevent_kernel_multicast_uid_recv(int socket, void *buffer, size_t length, uid_t *uid)
{
	return uevent_kernel_recv(socket, buffer, length, 1, uid);
}

ssize_t uevent_kernel_recv(int socket, void *buffer, size_t length, int require_group, uid_t *uid)
{
	struct iovec iov = { buffer, length };
	struct sockaddr_nl addr;
	char control[CMSG_SPACE(sizeof(int) * 3)];
	struct msghdr hdr = {
		&addr,
		sizeof(addr),
		&iov,
		1,
		control,
		sizeof(control),
		0,
	};

	*uid = -1;
	ssize_t n = recvmsg(socket, &hdr, 0);
	if (n <= 0) {
		return n;
	}

	struct cmsghdr *cmsg = CMSG_FIRSTHDR(&hdr);
	//if (cmsg == NULL || cmsg->cmsg_type != SCM_CREDENTIALS) {
	if (cmsg == NULL || cmsg->cmsg_type != 0x02) {
		/* ignoring netlink message with no sender credentials */
		goto out;
	}

	struct ucred *cred = (struct ucred *)CMSG_DATA(cmsg);
	//*uid = cred->uid;
	*uid = ((int*)cred)[1];
	//if (cred->uid != 0) {
	if (*uid != 0) {
		/* ignoring netlink message from non-root user */
		goto out;
	}

	if (addr.nl_pid != 0) {
		/* ignore non-kernel */
		goto out;
	}
	if (require_group && addr.nl_groups == 0) {
		/* ignore unicast messages when requested */
		goto out;
	}

	return n;

out:
	/* clear residual potentially malicious data */
	bzero(buffer, length);
	errno = EIO;
	return -1;
}


int uevent_open_socket(int buf_sz, int passcred)
{
	struct sockaddr_nl addr;
	int on = passcred; 
	int  s;
	memset(&addr, 0, sizeof(addr));
	addr.nl_family = AF_NETLINK;
	addr.nl_pid = getpid();
	addr.nl_groups = 0xffffffff;

	s = socket(PF_NETLINK, SOCK_DGRAM | SOCK_CLOEXEC, NETLINK_KOBJECT_UEVENT);
	if(s < 0)
		return -1;

	setsockopt(s, SOL_SOCKET, SO_RCVBUFFORCE, &buf_sz, sizeof(buf_sz));
	setsockopt(s, SOL_SOCKET, SO_PASSCRED, &on, sizeof(on));

	if(bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		close(s);
		return -1;
	}

	return s;
}
void handle_device_fd(void)
{
	char msg[UEVENT_MSG_LEN+2];
	int n;

	while ((n = uevent_kernel_multicast_recv(device_fd, msg, UEVENT_MSG_LEN)) > 0) {
		printf("%s:n..%d\n",__func__,n);
		if(n >= UEVENT_MSG_LEN)   /* overflow -- discard */
			continue;

		msg[n] = '\0';
		msg[n+1] = '\0';

		struct uevent uevent;
		parse_event(msg, &uevent);

		//handle_device_event(&uevent);
		//handle_firmware_event(&uevent);
	}
}
static void parse_event(const char *msg, struct uevent *uevent)
{
	uevent->action = "";
	uevent->path = "";
	uevent->subsystem = "";
	uevent->firmware = "";
	uevent->major = -1;
	uevent->minor = -1;
	uevent->partition_name = NULL;
	uevent->partition_num = -1;
	uevent->device_name = NULL;

	/* currently ignoring SEQNUM */
	while(*msg) {
		if(!strncmp(msg, "ACTION=", 7)) {
			msg += 7;
			uevent->action = msg;
		} else if(!strncmp(msg, "DEVPATH=", 8)) {
			msg += 8;
			uevent->path = msg;
		} else if(!strncmp(msg, "SUBSYSTEM=", 10)) {
			msg += 10;
			uevent->subsystem = msg;
		} else if(!strncmp(msg, "FIRMWARE=", 9)) {
			msg += 9;
			uevent->firmware = msg;
		} else if(!strncmp(msg, "MAJOR=", 6)) {
			msg += 6;
			uevent->major = atoi(msg);
		} else if(!strncmp(msg, "MINOR=", 6)) {
			msg += 6;
			uevent->minor = atoi(msg);
		} else if(!strncmp(msg, "PARTN=", 6)) {
			msg += 6;
			uevent->partition_num = atoi(msg);
		} else if(!strncmp(msg, "PARTNAME=", 9)) {
			msg += 9;
			uevent->partition_name = msg;
		} else if(!strncmp(msg, "DEVNAME=", 8)) {
			msg += 8;
			uevent->device_name = msg;
		}

		/* advance to after the next \0 */
		while(*msg++)
			;
	}

	if (1) {
		printf("event { '%s', '%s', '%s', '%s', %d, %d }\n",
				uevent->action, uevent->path, uevent->subsystem,
				uevent->firmware, uevent->major, uevent->minor);
	}
}



