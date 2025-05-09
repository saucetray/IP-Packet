//
//  IPv4.c
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/21/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//


#include "IPv4.h"
#include "protocol.h"

#define IHL(ihl) (0x0F & ihl)
#define FLAGS(byte) ((byte & 0xE0) >> 5) // Extract the 3 flag bits
#define IPv4AddressPrint(identifier, addr) \
                     printf("%s:\t\t%d.%d.%d.%d\n", identifier, addr[0], addr[1], addr[2], addr[3]);



/// address_parser - parses the address into a integer array
/// param address - pointer to the address location
/// param buffer - the buffer with the binary to the packet
/// param i - the starting index for the buffer
static void address_parser(unsigned int *address, unsigned char *buffer, int i) {
    int index = 0;
    for (int j = i; j < i+4; j++) {
        address[index] = buffer[j];
        index++;
    }
}


void create_IPv4_packet_file(IPv4_Packet *packet, FILE *file, int8_t ihl) {
    packet->version = 4;
    packet->IHL = IHL(ihl); // figure out the length of the header for IPv4.
    
    unsigned char buffer[packet->IHL * 4];
    if (packet->IHL < 5) {
        fprintf(stderr, "Error: Invalid IHL value %d (must be at least 5)\n", packet->IHL);
        return;
    }
    
    size_t bytes_read = fread(buffer, sizeof(char), packet->IHL * 4 - 1, file);
    if (bytes_read != packet->IHL * 4 - 1) {
        fprintf(stderr, "Error: Could not read complete IPv4 header\n");
        return;
    }
    
    packet->TOS = buffer[0];
    packet->total_length = (buffer[1] << 8) | buffer[2]; // total length of the packet including its payload.
    packet->ID = (buffer[3] << 8) | buffer[4];
    
    // flags for fragmentation
    packet->Flags = FLAGS(buffer[5]);
    packet->fragment_off = ((buffer[5] & 0x1F) << 8) | buffer[6];
    
    packet->TTL = buffer[7]; // time to live
    packet->protocol = buffer[8]; // protocol
    packet->checksum = (buffer[9] << 8) | buffer[10];
    
    // parses the addresses into the address space
    address_parser(packet->source_address, buffer, 11);
    address_parser(packet->destination_address, buffer, 15);
}


void print_IPv4_packet(IPv4_Packet *packet) {
    static int number = 0;
    number++;
    printf("=====> Packet %i : IPv%i\n", number, packet->version);
    Print("Version", packet->version);
    Print("Header Length", packet->IHL);
    Print("DSCP", packet->TOS);
    Print("Total Length", packet->total_length);
    Print("Identification", packet->ID);
    Print("Flags", packet->Flags);
    Print("Fragment Offset", packet->fragment_off);
    ProtocolPrint(get_protocol(packet->protocol), packet->protocol);
    Print("TTL", packet->TTL);
    Print("Checksum", packet->checksum);
    IPv4AddressPrint("Source Address", packet->source_address);
    IPv4AddressPrint("Destination Address", packet->destination_address);
}


void create_IPv4_packets(int amount, FILE *file) {
    if (file == NULL) {
        fprintf(stderr, "Error: Invalid file pointer\n");
        return;
    }
    
    for(int i = 0; i < amount; i++) {
        IPv4_Packet packet;
        packet.version = 4;
        packet.IHL = 5;
        packet.TOS = 0;
        packet.total_length = 20 + (rand() % 1480); // Typical MTU is 1500
        packet.TTL = 64; // Common TTL value
        packet.ID = rand() % 65536;
        packet.Flags = 0;
        packet.fragment_off = 0;
        packet.protocol = 6; // TCP
        packet.checksum = 0; // Would need to calculate actual checksum
        
        // Generate random source and destination addresses
        for (int j = 0; j < 4; j++) {
            packet.source_address[j] = rand() % 256;
            packet.destination_address[j] = rand() % 256;
        }
        
        // Write the packet to the file
        // This would need to be implemented to actually write the binary data
    }
}
