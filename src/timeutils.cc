#include "winutils.h"
#include <winsock2.h> //for timeval
#include <ctime>

#include <iomanip>
#include <sstream>
#include <sys/time.h>
#include <sys/times.h>
#include <cassert>

#define BUF_SIZE 128
//C++ 11: Lot of OS specific functions can be replaced by using the boost::chrono library

bool ValidClockId(clockid_t clk_id) {
    if (clk_id == CLOCK_MONOTONIC || clk_id == CLOCK_REALTIME)
        return true;
    else
        return false;
}

int clock_getres_monotonic( struct timespec *res) {
    if (res != nullptr) {
        LARGE_INTEGER frequency;
        if (QueryPerformanceFrequency(&frequency) != 0) {
            double nanosecdbl = 1000000000.0 / frequency.QuadPart;
            long long nanosecll = static_cast<long long> (nanosecdbl);
            res->tv_nsec = static_cast<long>((nanosecll) % 1000000000);
            res->tv_sec = static_cast<long>((nanosecll) / 1000000000);
            return 0;
        }
    }
    return -1;
}

int clock_getres(clockid_t clk_id, struct timespec *res) {
    if (clk_id == CLOCK_MONOTONIC)
        return clock_getres_monotonic(res);
    return -1;
}

int clock_gettime_monotonic(struct timespec *ts) {
    static bool bInitDone = false;
    if (ts == nullptr)
        return -1;

    LARGE_INTEGER           t;
//	FILETIME            f;
    double                  nanoseconds;
    static LARGE_INTEGER    starttime;
    static double           TicksPerNanosecond;

    if (!bInitDone) {
        QueryPerformanceCounter(&starttime);

        LARGE_INTEGER performanceFrequency;
        QueryPerformanceFrequency(&performanceFrequency);
        bInitDone = true;
        TicksPerNanosecond = (double)performanceFrequency.QuadPart / 1000000000.;

    }

    QueryPerformanceCounter(&t);
    t.QuadPart -= starttime.QuadPart;

    nanoseconds = (double)t.QuadPart / TicksPerNanosecond;
    long long nanosecondsll = static_cast<long long> (nanoseconds);
    ts->tv_nsec = static_cast<long>((nanosecondsll) % 1000000000);
    ts->tv_sec = static_cast<long>((nanosecondsll) / 1000000000);

    return 0;
}

/* FILETIME for January 1st, 1970 */
unsigned __int64 jan_1_1970 = static_cast<unsigned __int64>(116444736000000000ULL);

int clock_gettime_realtime(struct timespec *ts) {
    int retval = -1;
    if (ts != nullptr) {
        FILETIME    filetime;
        SYSTEMTIME    systemtime;
        ULARGE_INTEGER ulI;

        GetSystemTimeAsFileTime(&filetime);
        FileTimeToSystemTime(&filetime, &systemtime);

        ulI.LowPart = filetime.dwLowDateTime;
        ulI.HighPart = filetime.dwHighDateTime;

        ts->tv_sec = static_cast<long>((ulI.QuadPart - jan_1_1970) / 10000000L);
        ts->tv_nsec = static_cast<long>(systemtime.wMilliseconds * 1000000);
        retval = 0;
    }
    return retval;


}

int clock_gettime(clockid_t clk_id, struct timespec *ts) {
    if (clk_id == CLOCK_MONOTONIC)
        return clock_gettime_monotonic(ts);
    else if (clk_id == CLOCK_REALTIME)
        return clock_gettime_realtime(ts);
    return -1;

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


char *ctime_r(const time_t *timep, char buf[]) {
    if (timep == nullptr || buf == nullptr)
        return nullptr;
    char buffer[101];
    errno_t e = ctime_s(buffer, 100, timep);
    if (e == 0)
    {
        strncpy(buf, buffer,100);
        return buf;
    }
    else
        return nullptr;
}



char* strptime(const char* str,const char* format, struct tm* tm) {
    std::istringstream input(str);
    input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
    input >> std::get_time(tm, format);
    if (input.fail()) 
    {
        return nullptr;
    }
    return const_cast<char*>(str + input.tellg());
}


__int64  timegm(struct tm *) {
    //windows-temp assert(0);
    return 0;
}
struct tm *  gmtime_r(__int64 const *, struct tm *) {
    //windows-temp assert(0);
    return nullptr; 
}

int TimeSpecToTimeVal(struct timespec *pts, struct timeval *ptv) {
    int retval = -1;
    if (pts != nullptr && ptv != nullptr) {
        ptv->tv_sec = pts->tv_sec;
        ptv->tv_usec = pts->tv_nsec / 1000;
        retval = 0;
    }
    return retval;
}

int gettimeofday(struct timeval *ptv, struct timezone *) {
    struct timespec ts;
    int retval = -1;
    if (clock_gettime_realtime(&ts) == 0) {
        if (TimeSpecToTimeVal(&ts, ptv) == 0) {
            retval = 0;
        }
    }
    return retval;
}

clock_t times(struct tms *buf) {

    if (buf != nullptr) {
        buf->tms_utime = clock();
        buf->tms_stime = buf->tms_cutime = buf->tms_cstime = 0;
    }

    return buf->tms_stime;
}

