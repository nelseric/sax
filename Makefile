CC=gcc
CFLAGS=-Wall -ggdb -std=c99
LDLIBS=-lreadline
LDFLAGS=

SOURCES=ppxml.c sax.c

OBJECTS=$(SOURCES:.c=.o)

TARGET=ppxml


.PHONY : clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(LDLIBS) $(OBJECTS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.depend: depend

depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;
include .depend

run: all
	./$(TARGET) < test.xml
clean:
	rm $(OBJECTS) $(TARGET) 

