CC=gcc
CFLAGS=-I.

mwc: mwc.o
	$(CC) -o mwc mwc.o $(CFLAGS)

clean: 
	rm -f *.o

.PHONY: clean

all: mwc clean

