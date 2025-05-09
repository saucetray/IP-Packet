# IP-Packet Parser

A C-based tool for parsing and analyzing IPv4 and IPv6 packet headers.

## Overview

This project provides a packet parser that can read binary IP packet data from files and display the header information in a human-readable format. It supports both IPv4 and IPv6 protocols and identifies various transport layer protocols.

The parser extracts and displays key information from packet headers, including:

- IP version
- Header length
- Traffic class/Type of service
- Flow labels
- Packet length
- Fragmentation information
- TTL/Hop limit
- Protocol type
- Checksums
- Source and destination addresses

## Features

- Parse IPv4 packet headers
- Parse IPv6 packet headers
- Identify and display transport layer protocols
- Process multiple packet files in a single run
- Generate random IPv4 and IPv6 packets for testing

## Compilation

The project can be compiled using the provided Makefile:

```bash
# Compile both the parser and packet generator
make

# Compile only the parser
make ip_packet_parser

# Compile only the packet generator
make packet_generator

# Clean up compiled files
make clean
```

Alternatively, you can compile manually using GCC:

```bash
# Compile the parser
gcc -o ip_packet_parser IP\ Packet\ Reader/main.c IP\ Packet\ Reader/IPv4.c IP\ Packet\ Reader/IPv6.c IP\ Packet\ Reader/protocol.c

# Compile the packet generator
gcc -o packet_generator IP\ Packet\ Reader/packet_generator.c
```

## Usage

### Packet Parser

```bash
./ip_packet_parser [packet_file1] [packet_file2] ...
```

### Packet Generator

```bash
./packet_generator <output_file> <type> [count]
  type: 4 for IPv4, 6 for IPv6
  count: number of packets to generate (default: 1)
```

### Example

```bash
# Generate a sample IPv4 packet
./packet_generator sample_ipv4.bin 4

# Generate 5 IPv6 packets
./packet_generator sample_ipv6.bin 6 5

# Parse the generated packets
./ip_packet_parser sample_ipv4.bin sample_ipv6.bin
```

## IPv4 Header Structure

```
                                 IPv4 Packet Header Design
                                           Bits
       |0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31|
B  0   |-vers-|--IHL--|---------TOS---------|--------------------TLength---------------------|
Y  4   |----------------ID------------------|--Flags-|-----------Fragment-OffSet-------------|
T  8   |------TTL-----|-------Protocol------|------------------Checksum----------------------|
E  12  |------------------------------Source-Address-----------------------------------------|
S  16  |-----------------------------Destination-Address-------------------------------------|
   20  |---------------------------------Options---------------------------------------------|
```

## IPv6 Header Structure

```
                                 IPv6 Packet Header Design
                                           Bits
       |0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31|
   0   |-vers--|---Trafic-Class--|-----------------------Flow-Label--------------------------|
   4   |--------------Payload-Length---------|------Next-Header-----|------Hop-Limit---------|
B  8   |-------------------------------Source-Address----------------------------------------|
Y  12  |-------------------------------------------------------------------------------------|
T  16  |-------------------------------------------------------------------------------------|
E  20  |-------------------------------------------------------------------------------------|
S  24  |-----------------------------Destination-Address-------------------------------------|
   28  |-------------------------------------------------------------------------------------|
   32  |-------------------------------------------------------------------------------------|
   36  |-------------------------------------------------------------------------------------|
```

## Learning Outcomes

This project provided valuable learning experiences in:

- Network protocol analysis
- Bit manipulation in C
- Binary file parsing
- Network address formatting
- Protocol encapsulation

## License

See the [LICENSE](LICENSE) file for details.
