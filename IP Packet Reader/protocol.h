//
//  protocol.h
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/23/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//

#ifndef protocol_h
#define protocol_h

#include <stdio.h>

/// get_protocol - obtains the protocol string from the number of the protocol.
/// param protocol - the number of the protocol
/// return - the name of the protocol
char *get_protocol(unsigned int protocol);

#endif /* protocol_h */
