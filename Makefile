CC = gcc
CFLAGS = -Wall -O2

all: feistel

feistel: feistel.c
	$(CC) $(CFLAGS) feistel.c -o feistel

clean:
	rm -f feistel
