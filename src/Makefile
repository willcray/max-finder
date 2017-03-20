CC = gcc -std=c99
CFLAGS  = -Wall -g
OFILES: barrier.o max_finder.o main.o

all: main

main:   $(OFILES)
        $(CC) -o max_finder main.c barrier.c max_finder.c $(CFLAGS) $(OFILES)

main.o: main.c
        $(CC) $(CFLAGS) main.c
barrier.o: barrier.c
        $(CC) $(CFLAGS) barrier.c

max_finder.o: max_finder.c
        $(CC) $(CFLAGS) max_finder.c