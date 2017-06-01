CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
OBJECTS = huffman.o treestack.o

.PHONY: all 
all: test

test: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o test

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

treestack.o: treestack.c
	$(CC) $(CFLAGS) -c treestack.c
	
.PHONY: clean 
clean:
	rm -f $(OBJECTS) test