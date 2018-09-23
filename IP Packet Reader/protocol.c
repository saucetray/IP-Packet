//
//  protocol.c
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/23/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//

#include "protocol.h"

char *get_protocol(unsigned int protocol) {
    switch (protocol) { // checks protocols and prints which one it is.
        case 1:
            return "ICMP";
        case 2:
            return "IGMP";
        case 6:
            return "TCP";
        case 9:
            return "IGRP";
        case 17:
            return "UDP";
        case 47:
            return "GRE";
        case 50:
            return "ESP";
        case 51:
            return "AH";
        case 57:
            return "SKIP";
        case 88:
            return "EIGZRP";
        case 89:
            return "OSPF";
        case 115:
            return "L2TP";
    }
    return "Unknown Protocol";
}
