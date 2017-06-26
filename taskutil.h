#ifndef __TASKUTIL_H__
#define __TASKUTIL_H__

#include <string>

bool TaskExecuteAndWait(std::string execpath, std::string *pOutput = nullptr);
int osspecific_getpid(void);
FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);
int CountProcessThreads(DWORD dwOwnerPID);
DWORD GetNumberOfCPUs();
int getloadavg(double loadavg[], int nelem);

#endif // __TASKUTIL_H__
