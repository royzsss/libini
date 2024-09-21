SUBDIRS = test

.PHONY: all clean $(SUBDIRS)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = libini.so

CFLAGS = -O2 -fPIC
LDFLAGS = -shared

all: $(TARGET) $(SUBDIRS)

$(TARGET): $(OBJS)
	gcc $^ -o $@ $(LDFLAGS)

%.o: %.c
	gcc -c $< $(CFLAGS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	rm $(OBJS) $(TARGET)
	$(MAKE) -C $(SUBDIRS) clean
