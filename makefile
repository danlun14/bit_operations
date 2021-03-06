
CC = gcc
CFLAGS = -c –Wall -Werror
EXECUTABLE = coder
SOURCES = src-utf-8/main.c src-utf-8/command.c src-utf-8/coder.c
OBJECTS=$(SOURCES: .c=.o)

all:	$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o bin/$@

.c.o:
	$(CC) $(CFLAGS) $< -o bin/$@

clean:
	rm -rf *.o *.exe