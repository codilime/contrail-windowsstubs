#include "winutils.h"
#include "TlHelp32.h"

DWORD getppid()
{
    HANDLE hSnapshot = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0, pid = GetCurrentProcessId();

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    __try {
        if (hSnapshot == INVALID_HANDLE_VALUE) __leave;

        ZeroMemory(&pe32, sizeof(pe32));
        pe32.dwSize = sizeof(pe32);
        if (!Process32First(hSnapshot, &pe32)) __leave;

        do {
            if (pe32.th32ProcessID == pid) {
                ppid = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));

	}

	__finally {
        if (hSnapshot != INVALID_HANDLE_VALUE) CloseHandle(hSnapshot);
	}
	return ppid;
}

void bzero(void *to, int count)
{
	unsigned char *chto = static_cast<unsigned char*>(to);
	while (count-- > 0)
	{
		*chto++ = 0;
	}
}

unsigned int  sleep(unsigned int sec) { Sleep(1000 * sec); return 0; }

int usleep(unsigned int x) {
    Sleep((x + 999U) / 1000U); // divide by 1000 and round up
    return 0;
}

int  getrlimit(int, struct rlimit *) { return 0; }

int  getrusage(int, struct rusage *) { return 0; }

int  close(int) { return 0; }

int  setrlimit(int, struct rlimit const *) { return 0; }

void  WindowsCloseTaskFiles(void) {}

char * gettempdirectory(void) 
{ 
    DWORD WINAPI GetTempPath(
        _In_  DWORD  nBufferLength,
        _Out_ LPTSTR lpBuffer
    );

    return 0; 
}

int ioctl(int fd, unsigned long request, ...) { return 0; }

//similar functionality as ffsl in linux - called in bitset.cc
int find_first_set64(uint64_t value) 
{
    unsigned long index = 0;
    unsigned char isNonZero= _BitScanForward64(&index, value);
    if (isNonZero)	{
        return index + 1;
        //ffsl assumes least significant bit is position is 1.
        //_bitScanForward assumes least significant bt position is 0.
    } else {
        return 0;
    }
}
