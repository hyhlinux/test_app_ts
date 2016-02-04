#ifndef _FTM_COMMON_H_
#define _FTM_COMMON_H_

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof array / sizeof array[0])
#endif

#define BUF_LEN 64

#define AT_RESULT_OK "OK"
#define AT_RESULT_ERROR "ERROR"
#define AT_FTM_READY "AT_FTM_READY"
#define AT_UNDEF_CMD "UNDEFINED COMMAND"
#define E_SUCCESS 		   0
#define E_FILE_OPEN_FAIL  0x01
#define E_FILE_READ_FAIL  0x02
#define E_FILE_WRITE_FAIL 0x03
#define E_FILE_NULL_PTR    0x04
#define E_IOCTL_GET_FAIL 0x10
#define E_IOCTL_SET_FAIL 0x20
#define E_MEM_MAP_FAIL 0x30
#define E_PCB_GET_FAIL 0x40
#define E_MODULE_LOAD_FAIL 0x50
#define E_PROCESS_CREATE_FAIL 0x60

#endif

