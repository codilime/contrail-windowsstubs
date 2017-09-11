#include <posix_time.h>
#include <sstream>
#include <iomanip>

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
    if (e == 0)
    {
        strncpy(buf, buffer,100);
        return buf;
    }
    else
        return nullptr;
}
