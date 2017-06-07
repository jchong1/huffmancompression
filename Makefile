CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
ENCODE_OBJECTS = encode.o huffman.o treestack.o queue.o bv.o
DECODE_OBJECTS = decode.o huffman.o treestack.o bv.o

.PHONY : all 
all : encode decode

encode : $(ENCODE_OBJECTS)
	$(CC) $(CFLAGS) $(ENCODE_OBJECTS) $(CFLAGS) -o encode

decode: $(DECODE_OBJECTS)
	$(CC) $(CFLAGS) $(DECODE_OBJECTS) $(CFLAGS) -o decode 

encode.o : encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o : decode.c
	$(CC) $(CFLAGS) -c decode.c

huffman.o : huffman.c
	$(CC) $(CFLAGS) -c huffman.c

treestack.o : treestack.c
	$(CC) $(CFLAGS) -c treestack.c

queue.o : queue.c
	$(CC) $(CFLAGS) -c queue.c

bv.o : bv.c
	$(CC) $(CFLAGS) -c bv.c

.PHONY : clean 
clean :
	rm -f *.o encode decode