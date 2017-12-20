#pragma once

#include<windows.h>
#include <stdlib.h>

#include <string> // TODO: JW-522 Refactor
#include <sstream>

typedef ptrdiff_t ssize_t;

char *windows_if_indextoname(unsigned int ifindex, char *ifname);
char *gettempdirectory();

#define PACK( ___somestructure___ ) __pragma( pack(push, 1) ) ___somestructure___ __pragma( pack(pop) )
#define strtok_r strtok_s



void bzero(void *to, int count);


void sync(void);
