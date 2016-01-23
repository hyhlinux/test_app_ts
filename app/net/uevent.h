#ifndef _HYH_UEVENT_H
#define _HYH_UEVENT_H
ssize_t uevent_kernel_multicast_recv(int socket, void *buffer, size_t length);
ssize_t uevent_kernel_multicast_uid_recv(int socket, void *buffer, size_t length, uid_t *uid);
ssize_t uevent_kernel_recv(int socket, void *buffer, size_t length, bool require_group, uid_t *uid);
int uevent_open_socket(int buf_sz, bool passcred);
#endif
