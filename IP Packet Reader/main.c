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

#define USAGE printf("./main [packet files]\n");
#define VERSION(version) ((0xF0 & version) >> 4);


// main - parses the packet files
// argc : the number of parameters
// argv : the parameters
int main(int argc, const char * argv[]) {
    int8_t version;
    
    if(strcmp(argv[1], "--help") == 0) {
        USAGE;
        return 0;
    }
    
    for(int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        fread(&version, 1, 1, file);
        version = VERSION(version)
        
        // hand over to IPv4 or IPv6
        if(version == 4) {
            //IPv4
        } else if(version == 6) {
            //IPv6
        } else {
            perror("This is not a packet. This program strictly takes packets.\n");
            return 1;
        }
    }
    
    return 0;
}

