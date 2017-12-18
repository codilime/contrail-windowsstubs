#include <posix_fcntl.h>
#include <windows.h>

int fcntl(int fildes, int cmd, ...) {
    va_list vl;

    if(cmd == F_SETFD) {
        int flag;
        va_start(vl, cmd);
        flag = va_arg(vl, int);
        va_end(vl);

        // We don't need to disable handle inheritance on Windows, since we don't run exec functions
        if (flag == FD_CLOEXEC) {
            return 0;
        }
    }
    return -1;
}
