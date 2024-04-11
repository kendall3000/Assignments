CC = gcc
CFLAGS = -pthread
TARGET = scheduler
SRC = scheduler.c
RM = rm -f

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	$(RM) $(TARGET)
