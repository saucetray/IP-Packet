CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = IP\ Packet\ Reader
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/IPv4.c $(SRC_DIR)/IPv6.c $(SRC_DIR)/protocol.c
OBJS = $(SRCS:.c=.o)
TARGET = ip_packet_parser
GEN_SRC = $(SRC_DIR)/packet_generator.c
GEN_TARGET = packet_generator

all: $(TARGET) $(GEN_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(GEN_TARGET): $(GEN_SRC)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(GEN_TARGET)

.PHONY: all clean
