# Makefile comments
PROGRAMS = driver
CC = gcc
CFLAGS = -Wall -g
all: $(PROGRAMS)
clean:
	rm -f *.o
# C compilations
paintRoom.o: paintRoom.c paintRoom.h
	$(CC) $(CFLAGS) -c paintRoom.c
driver.o: driver.c paintRoom.h
	$(CC) $(CFLAGS) -c driver.c
# Executable programs
driver: driver.o paintRoom.o
	$(CC) $(CFLAGS) -o driver driver.o paintRoom.o

