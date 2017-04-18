

#include<iostream>
using namespace std;
#include "cpuinfo.h"

DWORD GetWindowsOSProcessorCount()
{

	SYSTEM_INFO siSysInfo;
	::GetSystemInfo(&siSysInfo);

	/*
	cout << "  Hardware information: " <<endl;
	cout << "  OEM ID: "<< siSysInfo.dwOemId<<endl;
	cout << "  Number of processors: "<<siSysInfo.dwNumberOfProcessors <<endl;
	cout << "  Page size: "<< siSysInfo.dwPageSize<<endl;
	cout << "  Processor type:" << siSysInfo.dwProcessorType <<endl;
	cout << "  Minimum application address: "<< siSysInfo.lpMinimumApplicationAddress<<endl;
	cout << "  Maximum application address: " <<siSysInfo.lpMaximumApplicationAddress <<endl;
	cout << "  Active processor mask: " <<	siSysInfo.dwActiveProcessorMask <<endl;
	*/

	return siSysInfo.dwNumberOfProcessors;
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
