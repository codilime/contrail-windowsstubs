#include "winutils.h"
#include "TlHelp32.h"
#include <cassert>
#include <DbgHelp.h>
#include <memory>
#include <unistd.h>

void bzero(void *to, int count) {
    unsigned char *chto = static_cast<unsigned char*>(to);
    while (count-- > 0)
    {
        *chto++ = 0;
    }
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
