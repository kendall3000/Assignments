CC = gcc
CFLAGS = -Wall
PROGRAMS = sum1 sum2 sum3 sum4 sum5 sum6 sum7 sum8
OUTPUT_FILES = $(PROGRAMS)

all: $(PROGRAMS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OUTPUT_FILES)
