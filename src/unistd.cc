#include <unistd.h>
#include <windows.h>
#include <TlHelp32.h>

unsigned int sleep(unsigned int seconds) { 
    ::Sleep(1000 * seconds);
    return 0;
}

int usleep(useconds_t usec) {
    ::Sleep((usec + 999U) / 1000U); // divide by 1000 and round up
    return 0;
}

int getppid() {
    HANDLE hSnapshot = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0, pid = GetCurrentProcessId();

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    __try {
        if (hSnapshot == INVALID_HANDLE_VALUE)
            __leave;

        ZeroMemory(&pe32, sizeof(pe32));
        pe32.dwSize = sizeof(pe32);
        if (!Process32First(hSnapshot, &pe32))
            __leave;

        do {
            if (pe32.th32ProcessID == pid) {
                ppid = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));

    }
    __finally {
        if (hSnapshot != INVALID_HANDLE_VALUE)
            CloseHandle(hSnapshot);
    }
    return ppid;
}

long sysconf(int name) {
    return -1;
}

pid_t vfork(void) {
    return -1;
}
