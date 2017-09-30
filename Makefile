TARGET = passhash
LIBS = $(shell pkg-config --libs gtk+-3.0 libsodium) -lcrypto
CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk+-3.0 libsodium) -Wall
OBJDIR=obj

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(shell find src -type f -name '*.c'))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
