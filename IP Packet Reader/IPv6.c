///
///  IPv6.c
///  IP Packet Reader
///
///  Created by Justin Sostre on 9/23/18.
///  Copyright © 2018 Justin Sostre. All rights reserved.
///

#include "IPv6.h"
#include "protocol.h"

#define IPv6_Header 40

static void address_parser(unsigned int *address, unsigned char *buffer, int i) {
    int index = 0;
    for (int j = i; j < i+16; j++) {
        address[index] = buffer[j];
        index++;
    }
}

/// simplify_IPv6_address - turns the address into a char of hex.
/// param packet - the pointer to the IPv6
/// param address - the address pointer
static void simplify_IPv6_address(unsigned char *address_string, unsigned int *address) {
    int i = 0;
    
    for (int j = 0; j < 16; j += 2) {
        int compressed = 1;
        
        int n = (address[j] << 8) | address[j+1];
        if (n == 0 && j != 14 && compressed) {
            int m = (address[j+2] << 8) | address[j+3];
            if (m == 0) {
                j += 4;
                for (int k = j; j < 16; j += 2) {
                    int b = (address[k] << 8) | address[k+1];
                    if (b != 0) {
                        j = k-2;
                        k = 16;
                    }
                }
                address[i] = ':';
                compressed = 0;
            } else {
                address_string[i] = '0';
                address_string[i+1] = ':';
                i += 2;
            }
        } else {
            while(n != 0) {
                // temporary variable to store remainder
                int temp  = 0;
                
                // storing remainder in temp variable.
                temp = n % 16;
                
                // check if temp < 10
                if(temp < 10) {
                    address_string[i] = temp + 48;
                    i++;
                }
                else {
                    address_string[i] = temp + 55;
                    i++;
                }
                n = n/16;
            }
            address_string[i] = ':';
            i++;
        }
    }
}

void create_IPv6_packet(IPv6_Packet *packet, FILE *file, int8_t byte) {
    packet->version = 6;
    unsigned char buffer[IPv6_Header];
    fread(buffer, sizeof(unsigned char), IPv6_Header - 1, file);
    
    packet->traffic_class = ((byte << 4) & 0x0F) | buffer[0];
    packet->flow_label = ((((buffer[0] & 0x0F) << 8) | buffer[1]) << 8) | buffer[2];
    packet->payload_length = (buffer[3] << 8) | buffer[4];
    packet->next_header = (buffer[5]);
    packet->hop_limit = (buffer[6]);
    
    address_parser(packet->source_address, buffer, 7);
    address_parser(packet->source_address, buffer, 23);
    
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
    Print("Next Header", packet->next_header);
    printf("Source Address\t\t%s", packet->source_string);
    printf("Destination Address\t\t%s", packet->destination_string);
}
