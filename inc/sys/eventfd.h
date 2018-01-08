#pragma once

#define EFD_SEMAPHORE   1
#define EFD_NONBLOCK    2
#define EFD_CLOEXEC     4

#ifdef __cplusplus
extern "C" {
#endif

int eventfd(unsigned int initval, int flags);

#ifdef __cplusplus
}
#endif
