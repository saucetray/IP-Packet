//
//  IPv6.c
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/23/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//

#include "IPv6.h"

#define IPv6_Length 36


void create_IPv6_packet(IPv6_Packet *packet, FILE *file, int8_t byte) {
    packet->version = 6;
    unsigned char buffer[IPv6_Length];
    fread(buffer, sizeof(unsigned char), IPv6_Length - 1, file);
    
    packet->traffic_class = ((byte << 4) & 0x0F) | buffer[0];
}
