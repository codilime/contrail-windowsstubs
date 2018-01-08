#include "winutils.h"
#include <winsock2.h> //for timeval
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/time.h>
#include <sys/times.h>
#include <cassert>
#include <posix_time.h>

#define BUF_SIZE 128
//C++ 11: Lot of OS specific functions can be replaced by using the boost::chrono library

bool ValidClockId(clockid_t clk_id) {
    if (clk_id == CLOCK_MONOTONIC || clk_id == CLOCK_REALTIME)
        return true;
    else
        return false;
}

LARGE_INTEGER getFILETIMEoffset() {
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime(&s, &f);
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart <<= 32;
    t.QuadPart |= f.dwLowDateTime;
    return (t);
}

clock_t times(struct tms *buf) {
    if (buf != nullptr) {
        buf->tms_utime = clock();
        buf->tms_stime = buf->tms_cutime = buf->tms_cstime = 0;
    }

    return buf->tms_stime;
}
