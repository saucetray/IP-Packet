//
//  IPv4.h
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/21/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//

//                                   IPv4 Packet Header Design
//                                            Bits
//        |0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
// B  0   |-vers-|--IHL--|---------TOS---------|--------------------TLength--------------------|
// Y  4   |----------------ID------------------|F1|F2|F3|-----------FragmentOffSet-------------|
// T  8   |------TTL-------|-----Protocol------|------------------Checksum---------------------|
// E  12  |------------------------------Source Address----------------------------------------|
// S  16  |-----------------------------Destination Address------------------------------------|
//    20  |---------------------------------Options--------------------------------------------|

#ifndef IPv4_h
#define IPv4_h

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int version: 4, IHL:4,
                 TOS: 8, TLength: 16, ID: 16;
} IPv4_packet;

void print_IPv4_packet(IPv4_packet packet);

void create_IPv4_packet(FILE *file);

#endif /* IPv4_h */
