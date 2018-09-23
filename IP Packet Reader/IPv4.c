//
//  IPv4.c
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/21/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//


#include "IPv4.h"

#define IHL(ihl) (0x0F & ihl)
#define FLAGS(byte) (0xE0 & byte) // (0x8000 & byte)
#define FRAG_OFFSET(byte) (printf("%i", 3));


static void address_parser(unsigned int *address, unsigned char *buffer, int i) {
    
    int index = 0;
    
    for (int j = i; j < i+4; j++) {
        address[index] = buffer[i];
        index ++;
    }
    
}


void create_IPv4_packet_file(IPv4_Packet *packet, FILE *file, int8_t ihl) {

    packet->IHL = IHL(ihl); // figure out the length of the header for iPv4.
    
    unsigned char buffer[(packet->IHL)*4];
    fseek(file, 0, SEEK_SET);
    fread(buffer, sizeof(char), (packet->IHL), file);
    
    for (int i = 0; i < 12; i++) {
        printf("%i\n", buffer[i]);
    }
    packet->TOS = buffer[0];
    packet->TLength = (buffer[1] << 8) | buffer[2]; // total length of the packet including its payload.
    packet->ID = (buffer[3] << 8) | buffer[4];
    
    // flags for fragmentation
    packet->Flags = FLAGS(buffer[5]);
    packet->fragment_off = (buffer[5] << 3) |  buffer[6];
    
    packet->TTL = buffer[7];
    packet->protocol = buffer[8];
    packet->checksum = (buffer[9] << 8) | buffer[10];
    
    address_parser(packet->source_address, buffer, 11);
    address_parser(packet->destination_addres, buffer, 15);
}


