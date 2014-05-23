.PHONY: clean build strip build_shared build_static test-app

CC = gcc
CFLAGS = -Wall -fexceptions -g -fPIC -Iinclude
LD = $(CC)
LDFLAGS = --shared $(CFLAGS) -ldl -lz
AR = ar
STRIP = strip

EXEC = lib$(notdir $(shell pwd))
SOURCES = $(shell find src -type f -iname '*.c')
OBJECTS = $(patsubst src/%.c,obj/%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)

build: build_shared build_static

build_shared: bin/${EXEC}.so

build_static: bin/${EXEC}.a

bin/${EXEC}.so: $(OBJECTS)
	$(LD) $(LDFLAGS) -o "bin/${EXEC}.so" $(OBJECTS)

bin/${EXEC}.a: $(OBJECTS)
	$(AR) -Dcr "bin/${EXEC}.a" $(OBJECTS)

obj/%.o: src/%.c
	$(CC) -MMD -c $(CFLAGS) $< -o $@

-include $(DEPENDS)

clean:
	rm -rf obj bin

strip: build
	$(STRIP) bin/$(EXEC).so

test-app: bin/test

obj/test.o: test-app/test.c
	$(CC) -c $(CFLAGS) test-app/test.c -o obj/test.o
	
bin/test: obj/test.o build_static
	$(CC) $(CFLAGS) -o bin/test obj/test.o bin/${EXEC}.a -ldl
