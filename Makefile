################################################################################
# Makefile for the datagram stub
################################################################################

CC=gcc
CFLAGS=-g -Wall -O2
LDFLAGS=-ldl

# include folder
INC = -I./include

all: bin/server bin/client


bin/server: src/server.c src/datagram_service.c
	mkdir -p bin
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC) $< src/datagram_service.c -o $@

bin/client: src/client.c src/datagram_service.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC) $< src/datagram_service.c -o $@

doc:
	rm -rf doc
	doxygen doxygen.conf

clean:
	rm -rf bin/*

veryclean:
	make clean
	rm -rf doc
