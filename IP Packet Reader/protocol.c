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
        case 0:
            return "HOPOPT";     // IPv6 Hop-by-Hop Option
        case 1:
            return "ICMP";       // Internet Control Message Protocol
        case 2:
            return "IGMP";       // Internet Group Management Protocol
        case 3:
            return "GGP";        // Gateway-to-Gateway Protocol
        case 4:
            return "IP-in-IP";   // IP in IP (encapsulation)
        case 6:
            return "TCP";        // Transmission Control Protocol
        case 8:
            return "EGP";        // Exterior Gateway Protocol
        case 9:
            return "IGRP";       // Interior Gateway Routing Protocol
        case 17:
            return "UDP";        // User Datagram Protocol
        case 41:
            return "IPv6";       // IPv6 encapsulation
        case 43:
            return "IPv6-Route"; // Routing Header for IPv6
        case 44:
            return "IPv6-Frag";  // Fragment Header for IPv6
        case 47:
            return "GRE";        // Generic Routing Encapsulation
        case 50:
            return "ESP";        // Encapsulating Security Payload
        case 51:
            return "AH";         // Authentication Header
        case 57:
            return "SKIP";       // SKIP
        case 58:
            return "IPv6-ICMP";  // ICMP for IPv6
        case 59:
            return "IPv6-NoNxt"; // No Next Header for IPv6
        case 60:
            return "IPv6-Opts";  // Destination Options for IPv6
        case 88:
            return "EIGRP";      // Enhanced Interior Gateway Routing Protocol
        case 89:
            return "OSPF";       // Open Shortest Path First
        case 103:
            return "PIM";        // Protocol Independent Multicast
        case 112:
            return "VRRP";       // Virtual Router Redundancy Protocol
        case 115:
            return "L2TP";       // Layer 2 Tunneling Protocol
        case 132:
            return "SCTP";       // Stream Control Transmission Protocol
    }
    return "Unknown Protocol";
}
