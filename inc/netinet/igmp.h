#pragma once

#include <winsock2.h>

struct igmp {
    uint8_t        igmp_type;
    uint8_t        igmp_code;
    uint16_t       igmp_cksum;
    struct in_addr igmp_group;
}; 
