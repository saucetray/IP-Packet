///
///  IPv6.c
///  IP Packet Reader
///
///  Created by Justin Sostre on 9/23/18.
///  Copyright © 2018 Justin Sostre. All rights reserved.
///

#include "IPv6.h"
#include "protocol.h"
#include <string.h>

#define IPv6_Header 40

/// address_parser - parses the address into an integer array
/// param address - pointer to the address location
/// param buffer - the buffer with the binary to the packet
/// param i - the starting index for the buffer
static void address_parser(unsigned int *address, unsigned char *buffer, int i) {
    int index = 0;
    for (int j = i; j < i+16; j++) {
        address[index] = buffer[j];
        index++;
    }
}

/// simplify_IPv6_address - formats the IPv6 address into standard notation
/// param address_string - output string buffer
/// param address - the address array
static void simplify_IPv6_address(unsigned char *address_string, unsigned int *address) {
    char temp[8][5]; // 8 groups of max 4 hex chars each
    int i, j;
    
    // Format each 16-bit group as hex
    for (i = 0; i < 8; i++) {
        int value = (address[i*2] << 8) | address[i*2+1];
        sprintf((char*)&temp[i], "%x", value);
    }
    
    // Find longest run of zeros for :: compression
    int zero_start = -1;
    int zero_length = 0;
    int current_start = -1;
    int current_length = 0;
    
    for (i = 0; i < 8; i++) {
        if (strcmp(temp[i], "0") == 0) {
            if (current_start == -1) {
                current_start = i;
                current_length = 1;
            } else {
                current_length++;
            }
        } else {
            if (current_length > zero_length) {
                zero_length = current_length;
                zero_start = current_start;
            }
            current_start = -1;
            current_length = 0;
        }
    }
    
    // Check if the last run is the longest
    if (current_length > zero_length) {
        zero_length = current_length;
        zero_start = current_start;
    }
    
    // Only compress if we have at least 2 consecutive zero groups
    if (zero_length < 2) {
        zero_start = -1;
    }
    
    // Build the final string
    address_string[0] = '\0';
    for (i = 0; i < 8; i++) {
        if (i == zero_start) {
            strcat((char*)address_string, "::");
            i += zero_length - 1; // Skip the compressed zeros
        } else {
            strcat((char*)address_string, temp[i]);
            if (i < 7 && (i + 1 != zero_start)) {
                strcat((char*)address_string, ":");
            }
        }
    }
}

void create_IPv6_packet(IPv6_Packet *packet, FILE *file, int8_t byte) {
    packet->version = 6;
    unsigned char buffer[IPv6_Header];
    
    size_t bytes_read = fread(buffer, sizeof(unsigned char), IPv6_Header - 1, file);
    if (bytes_read != IPv6_Header - 1) {
        fprintf(stderr, "Error: Could not read complete IPv6 header\n");
        return;
    }
    
    // Parse the IPv6 header fields
    packet->traffic_class = ((byte & 0x0F) << 4) | ((buffer[0] & 0xF0) >> 4);
    packet->flow_label = ((buffer[0] & 0x0F) << 16) | (buffer[1] << 8) | buffer[2];
    packet->payload_length = (buffer[3] << 8) | buffer[4];
    packet->next_header = buffer[5];
    packet->hop_limit = buffer[6];
    
    // Parse source and destination addresses
    address_parser(packet->source_address, buffer, 7);
    address_parser(packet->destination_address, buffer, 23);
    
    // Format addresses for display
    simplify_IPv6_address(packet->source_string, packet->source_address);
    simplify_IPv6_address(packet->destination_string, packet->destination_address);
}

void print_IPv6_packet(IPv6_Packet *packet) {
    static int number = 0;
    number++;
    printf("=====> Packet %i : IPv%i\n", number, packet->version);
    Print("Version", packet->version);
    Print("Traffic Class", packet->traffic_class);
    Print("Flow Label", packet->flow_label);
    Print("Payload Length", packet->payload_length);
    ProtocolPrint(get_protocol(packet->next_header), packet->next_header);
    Print("Hop Limit", packet->hop_limit);
    printf("Source Address:\t\t%s\n", packet->source_string);
    printf("Destination Address:\t%s\n", packet->destination_string);
}
