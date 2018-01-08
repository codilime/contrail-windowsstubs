#pragma once

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int ffs(int i);

int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);

#ifdef __cplusplus
}
#endif
