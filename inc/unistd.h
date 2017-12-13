#pragma once

#include <io.h>
#include <process.h>

#define STDOUT_FILENO   1
#define _SC_OPEN_MAX    5

typedef unsigned int useconds_t;
typedef unsigned int pid_t;

#ifdef __cplusplus
extern "C" {
#endif

unsigned int sleep(unsigned int seconds);
int usleep(useconds_t usec);
int getppid();
long sysconf(int name);

#ifdef __cplusplus
}
#endif
