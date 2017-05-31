CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
OBJECTS = stack.o 

.PHONY: all 
all: stack

stack: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o stack

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

.PHONY: clean 
clean:
	rm -f $(OBJECTS) stack