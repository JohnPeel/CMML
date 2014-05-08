.PHONY: clean build strip

CC = gcc
CFLAGS = -Wall -fexceptions -g -fPIC -Iinclude
LD = $(CC)
LDFLAGS = --shared $(CFLAGS)
STRIP = strip

EXEC = lib$(notdir $(shell pwd)).so
SOURCES = $(shell find src -type f -iname '*.c')
OBJECTS = $(patsubst src/%.c,lib/%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)

build: bin/$(EXEC)

bin/$(EXEC): $(OBJECTS)
	$(LD) $(LDFLAGS) -o bin/$(EXEC) $(OBJECTS)

lib/%.o: src/%.c
	$(CC) -MMD -c $(CFLAGS) $< -o $@

-include $(DEPENDS)

clean:
	rm -rf bin/$(EXEC) $(OBJECTS) $(DEPENDS)

strip: build
	$(STRIP) -s bin/$(EXEC)
