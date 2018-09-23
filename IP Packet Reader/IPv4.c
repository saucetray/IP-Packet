//
//  IPv4.c
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/21/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//


#include "IPv4.h"

#define IHL(ihl) (0x0F & ihl)
#define FLAG_ONE(byte) (0x1 & (byte >> 15)) // (0x8000 & byte)
#define FLAG_TWO(byte) (0x1 & (byte >> 14)) //(0x4000 & byte)
#define FLAG_THREE(byte) (0x1 & (byte >> 13)) // (0x2000 & byte)
#define FRAG_OFFSET(byte) (printf("%i", 3));

void create_IPv4_packet_file(IPv4_Packet *packet, FILE *file, int8_t ihl) {
    int8_t byte;
    int16_t bytes;

    packet->IHL = IHL(ihl); // figure out the length of the header for iPv4.
    fread(&byte, 1, 1, file);
    packet->TOS = byte; // type of service
    fread(&bytes, 2, 1, file);
    printf("%i\n", packet->TOS);
    packet->TLength = bytes; // total length of the packet including its payload.
    printf("%i\n", packet->TLength);
    fread(&bytes, 2, 1, file);
    packet->ID = bytes;
    // flags for fragmentation
    fread(&bytes, 2, 1, file);
    packet->F1 = FLAG_ONE(byte);
    packet->F2 = FLAG_TWO(byte);
    packet->F3 = FLAG_THREE(byte);
    printf("%i\n", bytes);
    printf("%i\n", packet->F2);
    printf("%i\n", packet->F1);
    printf("%i\n", packet->F3);
    
}
