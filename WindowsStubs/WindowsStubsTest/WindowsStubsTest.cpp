// WindowsStubsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winutils.h"
#include "wmi.h"
#include "cpuinfo.h"

#include<time.h>

int main()
{
	timespec ts;

	clock_getres(CLOCK_MONOTONIC, &ts);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	GetprocessPerformance();
    return 0;
}

