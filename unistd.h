#pragma once

#include<io.h>

typedef unsigned int useconds_t;

#ifdef __cplusplus
extern "C" {
#endif

int usleep(useconds_t usec);

#ifdef __cplusplus
}
#endif
