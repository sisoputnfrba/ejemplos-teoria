CC = gcc
CFLAGS = -Wall -Wextra -O2 -Wno-unused-variable -Wno-unused-but-set-variable

# Default targets
all: 64 32

32: main.c
	$(CC) $(CFLAGS) -m32 -o $@ $<

64: main.c
	$(CC) $(CFLAGS) -m64 -o $@ $<

clean:
	rm -f 32 64

