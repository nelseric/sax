CC=gcc
CFLAGS=-Wall -std=c99 -ggdb -DDEBUG
LDLIBS=
LDFLAGS=

SOURCES=ppxml.c sax.c sax_parser.c

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
	./$(TARGET) 
clean:
	rm $(OBJECTS) $(TARGET) 

