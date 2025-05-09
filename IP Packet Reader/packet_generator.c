//
//  packet_generator.c
//  IP Packet Reader
//
//  Created by Codegen on 2025-05-09.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to generate a random IPv4 packet
void generate_ipv4_packet(FILE *file) {
    unsigned char packet[20]; // Basic IPv4 header without options
    memset(packet, 0, sizeof(packet));
    
    // Version (4) and IHL (5 words = 20 bytes)
    packet[0] = 0x45;
    
    // Type of Service / DSCP
    packet[1] = 0x00;
    
    // Total Length (header + data) - just header for simplicity
    packet[2] = 0x00;
    packet[3] = 0x14; // 20 bytes
    
    // Identification
    packet[4] = rand() % 256;
    packet[5] = rand() % 256;
    
    // Flags and Fragment Offset
    packet[6] = 0x40; // Don't fragment
    packet[7] = 0x00;
    
    // TTL
    packet[8] = 0x40; // 64
    
    // Protocol (TCP = 6, UDP = 17, ICMP = 1)
    packet[9] = 0x06; // TCP
    
    // Header Checksum (set to 0 for simplicity)
    packet[10] = 0x00;
    packet[11] = 0x00;
    
    // Source IP (192.168.1.1)
    packet[12] = 192;
    packet[13] = 168;
    packet[14] = 1;
    packet[15] = 1;
    
    // Destination IP (10.0.0.1)
    packet[16] = 10;
    packet[17] = 0;
    packet[18] = 0;
    packet[19] = 1;
    
    // Write the packet to the file
    fwrite(packet, 1, sizeof(packet), file);
}

// Function to generate a random IPv6 packet
void generate_ipv6_packet(FILE *file) {
    unsigned char packet[40]; // Basic IPv6 header
    memset(packet, 0, sizeof(packet));
    
    // Version (6), Traffic Class, and Flow Label
    packet[0] = 0x60;
    packet[1] = 0x00;
    packet[2] = 0x00;
    packet[3] = 0x00;
    
    // Payload Length (0 for simplicity)
    packet[4] = 0x00;
    packet[5] = 0x00;
    
    // Next Header (TCP = 6)
    packet[6] = 0x06;
    
    // Hop Limit
    packet[7] = 0x40; // 64
    
    // Source Address (2001:db8::1)
    packet[8] = 0x20;
    packet[9] = 0x01;
    packet[10] = 0x0d;
    packet[11] = 0xb8;
    // Rest of source address (12-23) left as zeros
    packet[23] = 0x01;
    
    // Destination Address (2001:db8::2)
    packet[24] = 0x20;
    packet[25] = 0x01;
    packet[26] = 0x0d;
    packet[27] = 0xb8;
    // Rest of destination address (28-39) left as zeros
    packet[39] = 0x02;
    
    // Write the packet to the file
    fwrite(packet, 1, sizeof(packet), file);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <output_file> <type> [count]\n", argv[0]);
        printf("  type: 4 for IPv4, 6 for IPv6\n");
        printf("  count: number of packets to generate (default: 1)\n");
        return 1;
    }
    
    const char *filename = argv[1];
    int type = atoi(argv[2]);
    int count = (argc > 3) ? atoi(argv[3]) : 1;
    
    if (type != 4 && type != 6) {
        printf("Error: Type must be 4 (IPv4) or 6 (IPv6)\n");
        return 1;
    }
    
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Could not open file %s for writing\n", filename);
        return 1;
    }
    
    // Seed the random number generator
    srand(time(NULL));
    
    // Generate the specified number of packets
    for (int i = 0; i < count; i++) {
        if (type == 4) {
            generate_ipv4_packet(file);
        } else {
            generate_ipv6_packet(file);
        }
    }
    
    fclose(file);
    printf("Generated %d IPv%d packet(s) in file %s\n", count, type, filename);
    
    return 0;
}

