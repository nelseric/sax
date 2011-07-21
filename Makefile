CC=gcc
CFLAGS=-Wall -ggdb -std=c99
LDLIBS=-lreadline
LDFLAGS=

SOURCES=main.c sax.c

OBJECTS=$(SOURCES:.c=.o)

TARGET=sax


.PHONY : clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(LDLIBS) $(OBJECTS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

run: all
	./$(TARGET) 
clean:
	rm $(OBJECTS) $(TARGET)

