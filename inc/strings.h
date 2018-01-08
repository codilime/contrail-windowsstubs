#pragma once

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int ffs(int i);

#define strncasecmp _strnicmp
#define strcasecmp _stricmp

#ifdef __cplusplus
}
#endif
