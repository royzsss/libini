SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = ini-test

CFLAGS = -O2 -I..
LDFLAGS = -L.. -Wl,-rpath=..
LDADD = -lini

$(TARGET): $(OBJS)
	gcc $^ -o $@ $(LDFLAGS) $(LDADD)

%.o: %.c
	gcc -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm $(OBJS) $(TARGET)
