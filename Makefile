CC=gcc
CFLAGS=-fPIC -Wall -Wextra -O2 -g
LDFLAGS=-shared
TARGET=libautoclte2.so
SRCS=libautoclte2.c

all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
