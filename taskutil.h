#ifndef __TASKUTIL_H__
#define __TASKUTIL_H__
#include <string>
bool TaskExecuteAndWait(std::string execpath, std::string *pOutput = nullptr);
#endif
