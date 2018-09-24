//
//  main.c
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/14/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "IPv4.h"
#include "IPv6.h"


#define USAGE printf("./main [packet files]\n");
#define VERSION(version) ((0xF0 & version) >> 4);


/// main - parses the packet files
/// param argc - the number of parameters
/// param argv - the parameters
int main(int argc, const char * argv[]) {
    int8_t byte;
    int8_t version;
    
    if (argc < 1) {
        USAGE;
        return 1;
    }
    if(strcmp(argv[1], "--help") == 0) {
        USAGE;
        return 2;
    }
    
    for(int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        while ((fread(&byte, 1, 1, file))) {
            version = VERSION(byte)
            // hand over to IPv4 or IPv6
            if(version == 4) {
                IPv4_Packet packet;
                create_IPv4_packet_file(&packet, file, byte);
                print_IPv4_packet(&packet);
            } else if(version == 6) {
                IPv6_Packet packet;
                create_IPv6_packet(&packet, file, byte);
                print_IPv6_packet(&packet);
            } else {
                perror("This is not a packet. This program strictly takes packets.\n");
                return 3;
            }
        }
    }
    return 0;
}

