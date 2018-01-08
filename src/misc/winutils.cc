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

char * gettempdirectory(void) { 
      //windows-temp    assert(0);
    return nullptr; 
}
