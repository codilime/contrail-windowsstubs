#ifndef __ENDIAN_H__
#define __ENDIAN_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t htobe64(uint64_t host_64bits);

#ifdef __cplusplus
}
#endif

#endif // __ENDIAN_H__
