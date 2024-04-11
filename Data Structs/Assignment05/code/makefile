# Makefile comments
PROGRAMS = driver
CC = gcc
CFLAGS = -Wall -g
all: $(PROGRAMS)
clean:
	rm -f *.o
# C compilations
color.o: color.c color.h
	$(CC) $(CFLAGS) -c color.c
	
point2D.o: point2D.c point2D.h
	$(CC) $(CFLAGS) -c point2D.c

array2D.o: array2D.c array2D.h color.h
	$(CC) $(CFLAGS) -c array2D.c
	
hashTable.o: hashTable.c hashTable.h
	$(CC) $(CFLAGS) -c hashTable.c

queuePoint2D.o: queuePoint2D.c queuePoint2D.h point2D.h
	$(CC) $(CFLAGS) -c queuePoint2D.c
stackPoint2D.o: stackPoint2D.c stackPoint2D.h point2D.h
	$(CC) $(CFLAGS) -c stackPoint2D.c
priorityQueuePoint2D.o: priorityQueuePoint2D.c priorityQueuePoint2D.h point2D.h
	$(CC) $(CFLAGS) -c priorityQueuePoint2D.c
	
graph.o: graph.c graph.h point2D.h hashTable.h array2D.h priorityQueuePoint2D.h 
	$(CC) $(CFLAGS) -c graph.c
graphPathAlg.o: graphPathAlg.c graphPathAlg.h graph.h point2D.h queuePoint2D.h stackPoint2D.h priorityQueuePoint2D.h array2D.h
	$(CC) $(CFLAGS) -c graphPathAlg.c
driver.o: driver.c graphPathAlg.h graph.h point2D.h queuePoint2D.h array2D.h color.h
	$(CC) $(CFLAGS) -c driver.c

# Executable programs
driver: driver.o graphPathAlg.o graph.o point2D.o hashTable.o queuePoint2D.o stackPoint2D.o priorityQueuePoint2D.o color.o point2D.o array2D.o
	$(CC) $(CFLAGS) -o driver driver.o graphPathAlg.o graph.o point2D.o hashTable.o queuePoint2D.o stackPoint2D.o priorityQueuePoint2D.o color.o array2D.o

