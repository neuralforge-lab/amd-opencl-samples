CC = gcc
CFLAGS = -O2 -I/usr/include
LDFLAGS = -lOpenCL

all: main

main: main.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f main
