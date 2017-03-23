CC = gcc -std=c99
CFLAGS  = -Wall -g
HEADERS = max_finder.h barrier.h
OFILES = barrier.o max_finder.o main.o
CFILES = main.c barrier.c max_finder.c

program: $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o max_finder

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

barrier.o: barrier.c barrier.h
	$(CC) $(CFLAGS) -c barrier.c

max_finder.o: max_finder.c max_finder.h
	$(CC) $(CFLAGS) -c max_finder.c