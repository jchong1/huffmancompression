CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
OBJECTS = encode.o huffman.o treestack.o

.PHONY: all 
all: encode

encode: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o encode

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

treestack.o: treestack.c
	$(CC) $(CFLAGS) -c treestack.c
	
.PHONY: clean 
clean:
	rm -f $(OBJECTS) encode