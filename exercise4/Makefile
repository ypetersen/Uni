
CC=gcc
CFLAGS=-Wall -g -D__linux__ -D__x86_64__ -lpthread
LDFLAGS=

HEADERS=matrix_data.h

all: sequential

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

sequential: sequential.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o sequential *~

.PHONY: all clean
