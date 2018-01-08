#ifndef __POSIX_TIME_H__
#define __POSIX_TIME_H__

#include <time.h>
#include <winsock2.h>

#define CLOCK_REALTIME                  0
#define CLOCK_MONOTONIC                 1

typedef int clockid_t;
typedef unsigned int uint;
typedef unsigned long ulong;

#ifdef __cplusplus
extern "C" {
#endif

char *strptime(const char *s, const char *format, struct tm *tm);
time_t timegm(struct tm *tm);
struct tm *gmtime_r(const time_t *timep, struct tm *result);
char *ctime_r(const time_t *timep, char *buf);
int clock_gettime(clockid_t clk_id, struct timespec *tv);
int clock_getres(clockid_t clk_id, struct timespec *res);

#ifdef __cplusplus
}
#endif

#endif // __POSIX_TIME_H__
