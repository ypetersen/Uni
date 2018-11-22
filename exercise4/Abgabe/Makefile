
CC=gcc
CFLAGS=-Wall -g -D__linux__ -D__x86_64__ -pthread
LDFLAGS=

HEADERS=matrix_data.h

all: parallel

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

parallel: parallel.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o parallel *~

.PHONY: all clean
