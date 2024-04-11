# Makefile comments
PROGRAMS = driver
CC = gcc
CFLAGS = -Wall -g -std=c89 -pedantic
all: $(PROGRAMS)
clean:
	rm -f *.o
# C compilations
booleanWithError.o: booleanWithError.c booleanWithError.h
	$(CC) $(CFLAGS) -c booleanWithError.c
tokenizeString.o: tokenizeString.c tokenizeString.h
	$(CC) $(CFLAGS) -c tokenizeString.c
stack.o: stack.c stack.h booleanWithError.h
	$(CC) $(CFLAGS) -c stack.c
booleanEvaluation.o: booleanEvaluation.c booleanEvaluation.h booleanWithError.h tokenizeString.h stack.h
	$(CC) $(CFLAGS) -c booleanEvaluation.c
driver.o: driver.c stack.h booleanWithError.h
	$(CC) $(CFLAGS) -c driver.c
# Executable programs
driver: booleanEvaluation.o booleanWithError.o tokenizeString.o stack.o driver.o 
	$(CC) $(CFLAGS) -o driver booleanEvaluation.o booleanWithError.o tokenizeString.o stack.o driver.o
