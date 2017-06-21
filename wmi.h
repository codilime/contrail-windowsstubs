#ifndef __WMI_H__
#define __WMI_H__
#include "winutils.h"
#include<map>

std::map<std::string, std::string> OS_WMI_Information();
std::map<std::string, std::string> GetprocessPerformance();

#endif
