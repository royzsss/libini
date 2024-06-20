CC = gcc
CFLAGS = -g -O2 -fPIC
LDFLAGS = -shared

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

TARGET = libini.so

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm $(OBJS) $(TARGET)
