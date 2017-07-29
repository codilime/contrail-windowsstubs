#include<iostream>
#include "cpuutil.h"
using namespace std;

DWORD GetWindowsOSProcessorCount()
{

    SYSTEM_INFO siSysInfo;
    ::GetSystemInfo(&siSysInfo); 
    return (siSysInfo.dwNumberOfProcessors==0)?1: siSysInfo.dwNumberOfProcessors;
}


MEMORYSTATUSEX GetMemoryStatus()
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	cout << "dwMemoryLoad"<< statex.dwMemoryLoad <<endl;
	cout << "ullTotalPhys" << statex.ullTotalPhys << endl;
	cout << "ullAvailPhys" << statex.ullAvailPhys << endl;
	cout << "ullTotalPageFile" << statex.ullTotalPageFile << endl;
	cout << "ullAvailPageFile" << statex.ullAvailPageFile<< endl;
	cout << "ullTotalVirtual" << statex.ullTotalVirtual << endl;
	cout << "ullAvailVirtual" << statex.ullAvailVirtual << endl;
	cout << "ullAvailExtendedVirtual" << statex.ullAvailExtendedVirtual<< endl;

	return statex;
}
