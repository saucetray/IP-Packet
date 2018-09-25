///
/// IPv6.h
/// IP Packet Reader
///
/// Created by Justin Sostre on 9/23/18.
/// Copyright © 2018 Justin Sostre. All rights reserved.
///
///                                  IPv6 Packet Header Design
///                                            Bits
///        |0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31|
///    0   |-vers--|---Trafic-Class--|-----------------------Flow-Label--------------------------|
///    4   |--------------Payload-Length---------|------Next-Header-----|------Hop-Limit---------|
/// B  8   |-------------------------------Source-Address----------------------------------------|
/// Y  12  |-------------------------------------------------------------------------------------|
/// T  16  |-------------------------------------------------------------------------------------|
/// E  20  |-------------------------------------------------------------------------------------|
/// S  24  |-----------------------------Destination-Address-------------------------------------|
///    28  |-------------------------------------------------------------------------------------|
///    32  |-------------------------------------------------------------------------------------|
///    36  |-------------------------------------------------------------------------------------|

#ifndef IPv6_h
#define IPv6_h

#include <stdio.h>

typedef struct {
    unsigned int version: 4, traffic_class: 8, flow_label: 20;
    unsigned int payload_length: 16, next_header: 8, hop_limit: 8;
    unsigned int source_address[16], destination_address[16];
    unsigned char source_string[40], destination_string[40];
} IPv6_Packet;

void create_IPv6_packet(IPv6_Packet *packet, FILE *file, int8_t byte);

void print_IPv6_packet(IPv6_Packet *packet);

#endif /* IPv6_h */
