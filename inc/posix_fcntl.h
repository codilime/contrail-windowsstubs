#pragma once

#define FD_CLOEXEC     1
#define F_SETFD        1

#ifdef __cplusplus
extern "C" {
#endif

int fcntl(int fildes, int cmd, ...);

#ifdef __cplusplus
}
#endif
