#include "cpuutil.h"
#include <iostream>

DWORD GetWindowsOSProcessorCount()
{
    SYSTEM_INFO siSysInfo;
    ::GetSystemInfo(&siSysInfo); 
    return (siSysInfo.dwNumberOfProcessors == 0) ? 1 : siSysInfo.dwNumberOfProcessors;
}

MEMORYSTATUSEX GetMemoryStatus()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	std::cout << "dwMemoryLoad"<< statex.dwMemoryLoad << std::endl;
	std::cout << "ullTotalPhys" << statex.ullTotalPhys << std::endl;
	std::cout << "ullAvailPhys" << statex.ullAvailPhys << std::endl;
	std::cout << "ullTotalPageFile" << statex.ullTotalPageFile << std::endl;
	std::cout << "ullAvailPageFile" << statex.ullAvailPageFile<< std::endl;
	std::cout << "ullTotalVirtual" << statex.ullTotalVirtual << std::endl;
	std::cout << "ullAvailVirtual" << statex.ullAvailVirtual << std::endl;
	std::cout << "ullAvailExtendedVirtual" << statex.ullAvailExtendedVirtual<< std::endl;

	return statex;
}
