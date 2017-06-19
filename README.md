# huffmancompression
CMPS 12B Assignment 4: Huffman Encoding

encode:
The encoding program reads in a file, and for each character read, increments the 
corresponding histogram index with each characters' ASCII value. From this histogram,
a Huffman tree is built using a priority queue. Codes for each leaf of the tree are 
then built using a stack and appended into a bit vector of codes. The compressed output 
file is constructed by first writing the magic number, the original file length, the size 
of the tree, the tree, and then the encoding of the original file.

decode:
The decoding function works by reading in the first 4 bytes to ensure that the file was
compressed. Then, the next 10 bytes are read to build the huffman tree used to
encode the original text file. The bits are then read in one by one, each one signifying
whehter to to left (a 0 bit) or right (a 1 bit) in the tree. Once a leaf is reached,
a symbol associated with the code is emitted and printed to output designated by -o,
default stdout.

To compile:
	$ make all
To compress a file:
	$ ./encode -i [file you want to compress] -o [file you want to write to]
to decode a file:
	$ ./decode -i [File you want to decode] -o [file you want to write to, default stdout]
