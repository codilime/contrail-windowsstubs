#include "winutils.h"
#include "TlHelp32.h"
#include <cassert>
#include <DbgHelp.h>
#include <memory>
#include <unistd.h>

//     https://msdn.microsoft.com/en-us/library/windows/desktop/ms686701(v=vs.85).aspx
DWORD getppid() {
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



void bzero(void *to, int count) {
    unsigned char *chto = static_cast<unsigned char*>(to);
    while (count-- > 0)
    {
        *chto++ = 0;
    }
}


//Linux sleep's argument is in seconds
//Window's sleep argument is in milli seconds
unsigned int  sleep(unsigned int sec) { 
    ::Sleep(1000 * sec);
    return 0;
}

int usleep(useconds_t usec) {
    Sleep((usec + 999U) / 1000U); // divide by 1000 and round up
    return 0;
}

int  getrlimit(int, struct rlimit *) {
   //windows-temp    assert(0);
    return 0; 
}
int  getrusage(int, struct rusage *) {
    //windows-temp    assert(0);
    return 0; 
}

int  setrlimit(int, struct rlimit const *) {
    //windows-temp    assert(0);
    return 0; 
}
void  WindowsCloseTaskFiles(void) {
    //windows-temp    assert(0);
}
char * gettempdirectory(void) { 
      //windows-temp    assert(0);
    return nullptr; 
}

//similar functionality as ffsl in linux - called in bitset.cc
int find_first_set64(uint64_t value) {
    unsigned long index = 0;
    unsigned char isNonZero= _BitScanForward64(&index, value);
    if (isNonZero)	{

        return index + 1;
        //ffsl assumes least significant bit is position is 1.
        //_bitScanForward assumes least significant bt position is 0.
    }
    else return 0;
}

//modified from https://msdn.microsoft.com/en-us/library/windows/desktop/ms686701(v=vs.85).aspx
//useful utility to print detailed error message from error code.

std::string GetFormattedWindowsErrorMsg() {
    DWORD eNum = 0;
    const DWORD maxsize = 256;
    char sysMsg[maxsize];
    std::string errormsg;
    eNum = GetLastError();
    if(eNum !=0) {
        size_t size = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, eNum,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            sysMsg, maxsize, NULL);
        if (size != 0) {
            errormsg = sysMsg;
        }
     }
    return errormsg;
}

//https://msdn.microsoft.com/en-us/library/windows/desktop/ms724439(v=vs.85).aspx
//https://msdn.microsoft.com/en-us/library/windows/desktop/ms724832(v=vs.85).aspx
//other option is to USE wmi
std::string GetWindowsVersionString()
{
    OSVERSIONINFOEX infoex;

    ZeroMemory(&infoex, sizeof(OSVERSIONINFOEX));
    infoex.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    GetVersionEx((OSVERSIONINFO*)&infoex);

    std::stringstream strm;
    strm << "Major:" << infoex.dwMajorVersion << std::endl;
    strm << "Minor" << infoex.dwMinorVersion << std::endl;
    strm << "Build:" << infoex.dwBuildNumber << std::endl;
    strm << "Platform:" << infoex.dwPlatformId << std::endl;
    strm << "Pack:" << "(" << infoex.wServicePackMajor << "," << infoex.wServicePackMinor << ")"<<std::endl;;
    
    return strm.str();
}