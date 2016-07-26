CFLAGS = -g -Wall 
CC = gcc

objects = binPacking.o bin.o

test: $(objects)
	$(CC) -o binPacking $(objects)

binPacking.o: binPacking.c bin.h
bin.o: bin.c bin.h

.PHONY : clean
clean: 
	rm binPacking $(objects)
