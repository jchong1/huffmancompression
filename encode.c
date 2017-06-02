# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <getopt.h>
# include <unistd.h>

# include "huffman.h"

# define OPTIONS "i:o:v"

uint32_t *loadHistogram(char *);
char *sFile = NULL,
	 *oFile = NULL;

int main(int argc, char **argv)
{
	// Parse command-line arguments
	int encode;
	bool iflag = false;
	bool oflag = false;
	while ((encode = getopt(argc, argv, OPTIONS)) != -1)
	{
		switch (encode)
		{
			case 'i':
			{
				// Set input file
				iflag = true;
				sFile = optarg;
				break;
			}
			case 'o':
			{
				// Set output file
				oflag = true;
				oFile = optarg;
				break;
			}
			case 'v':
			{
				// Verbose option
				break;
			}
			default:
			{
				return - 1;
				break;
			}
		}
	}

	if (iflag)
	{
		// 1. Compute a histogram of the file (count the number of occurrences of each byte in the file).
		loadHistogram(sFile);
		// 2. Construct Huffman tree that represents the histogram (use a priority queue).

		// 3. Construct code for each symbol (use a stack and perform a traversal of the Huffman tree).

		// 4. Emit encoding of Huffman tree to a file (perform a post-order traversal of the Huffman tree).

		// 5. Emit encoding of original file to the compressed file (use bit vectors with operations append and/or concatenate).

		// 6. Read the tree from the compressed file, in order to do this you will use a stack.

		// 7. Decode the compressed bitstream into an identical copy of the original file. In order to do this, you will use
		//    the bits (0 means left, 1 means right) to guide your traversal of a reconstructed Huffman tree.
	}
	else
	{
		printf("Please specify an input file.\n");
	}
	return 0;
}

// Creates a histogram of char frequencies in file
uint32_t *loadHistogram(char *file)
{
	// Construct histogram and increment the first and last to guarantee at 2 elements
  	uint32_t *histogram = calloc(256, sizeof(uint32_t));
  	histogram[0] += 1;
 	histogram[255] += 1;

 	// Read input file
  	FILE *input = fopen(file, "r");
  	int c = 0;
  	while ((c = fgetc(input))) 
  	{
    	if(c == EOF) 
    	{
    		break;
    	}
    	histogram[c] += 1;
  	}

  	// printing loop to debug
  	for (int i = 0; i < 256; i++) 
  	{
    	if (histogram[i] > 0) 
    	{
      		printf("[%c]: %d times\n", i, histogram[i]);
    	}
  	}
  	fclose(input);
  	return histogram;
}
