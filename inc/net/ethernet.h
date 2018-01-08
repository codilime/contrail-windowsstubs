#pragma once

#include "sys/wintypes.h"

#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )

#define ETH_ALEN   6
#define ETHERTYPE_VLAN (0x8100)

#define ETHERTYPE_IPV4  0x0800
#define ETHERTYPE_IPV6  0x86dd

#define ETHER_ADDR_LEN 6

PACK(
struct ether_addr
{
	unsigned char ether_addr_octet[ETH_ALEN];
};
);