// WindowsStubsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winutils.h"
#include "wmi.h"
#include "cpuinfo.h"
#include "taskutil.h"

#include<time.h>

int main()
{
    std::string output;
    TaskExecuteAndWait("where python", &output);
    TaskExecuteAndWait("dir", nullptr);
    return 0;
}

