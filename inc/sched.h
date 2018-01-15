#pragma once

#include <stdlib.h>
#include <unistd.h>

typedef int cpu_set_t;

#ifdef __cplusplus
extern "C" {
#endif

void CPU_ZERO(cpu_set_t *set);
void CPU_SET(int cpu, cpu_set_t *set);

int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);

#ifdef __cplusplus
}
#endif
