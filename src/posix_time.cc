#include <posix_time.h>
#include <sstream>
#include <iomanip>

char* strptime(const char* str,const char* format, struct tm* tm) {
    std::istringstream input(str);
    input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
    input >> std::get_time(tm, format);
    if (input.fail())
        return nullptr;
    return const_cast<char*>(str + input.tellg());
}

time_t timegm(struct tm *_tm) {
    return _mkgmtime(_tm);
}

struct tm *gmtime_r(const time_t *time, struct tm *_tm) {
    errno_t ret = gmtime_s(_tm, time);
    if (ret == 0)
        return _tm;
    else
        return NULL;
}

char *ctime_r(const time_t *timep, char buf[]) {
    if (timep == nullptr || buf == nullptr)
        return nullptr;
    char buffer[101];
    errno_t e = ctime_s(buffer, 100, timep);
    if (e == 0) {
        strncpy(buf, buffer,100);
        return buf;
    } else
        return nullptr;
}

int clock_gettime_monotonic(struct timespec *ts) {
    static bool bInitDone = false;
    if (ts == nullptr)
        return -1;

    LARGE_INTEGER t;
    // FILETIME f;
    double nanoseconds;
    static LARGE_INTEGER starttime;
    static double TicksPerNanosecond;

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
        ULARGE_INTEGER ulI;

        GetSystemTimeAsFileTime(&filetime);

        ulI.LowPart = filetime.dwLowDateTime;
        ulI.HighPart = filetime.dwHighDateTime;

        unsigned long long time_diff_100nsec = ulI.QuadPart - jan_1_1970;
        ts->tv_sec = static_cast<time_t>(time_diff_100nsec / 10000000ULL);
        ts->tv_nsec = static_cast<long>((time_diff_100nsec % 10000000ULL) * 100);
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
