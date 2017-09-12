#ifndef __POSIX_TIME_H__
#define __POSIX_TIME_H__

#include <time.h>
#include <winsock2.h>

#ifdef __cplusplus
extern "C" {
#endif

char *strptime(const char *s, const char *format, struct tm *tm);
time_t timegm(struct tm *tm);
struct tm *gmtime_r(const time_t *timep, struct tm *result);
char *ctime_r(const time_t *timep, char *buf);

#ifdef __cplusplus
}
#endif

#endif // __POSIX_TIME_H__
