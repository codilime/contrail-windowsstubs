#ifndef __POSIX_TIME_H__
#define __POSIX_TIME_H__

#include <ctime>

//typedef long long time_t;
//typedef long long suseconds_t;

//struct linux_timeval {
//	        time_t          tv_sec;         /* seconds */
//	        suseconds_t     tv_usec;        /* microseconds */
//};

char *strptime(const char *s, const char *format, struct tm *tm);
time_t timegm(struct tm *tm);
struct tm *gmtime_r(const time_t *timep, struct tm *result);

#endif // __POSIX_TIME_H__
