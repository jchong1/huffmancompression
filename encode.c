# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <getopt.h>
# include <unistd.h>
# include <stdbool.h>

# define OPTIONS "i:o:v"

uint32_t *loadHistogram(char *);

int main()
{
	// Parse command-line arguments
	int encode;
	FILE *sFile = NULL,
	 	 *oFile = stdout;
	while (encode = getopt(argc, argv, OPTIONS) != -1)
	{
		switch (encode)
		{
			case i:
			{
				// file being read from
				sFile = optarg;
				break;
			}
			case o:
			{
				// file being written to (default stdout)
				oFile = optarg;
				break;
			}
			case v:
			{
				// verbose option
				break;
			}
			default:
			{
				return - 1;
				break;
			}
		}
	}

	// 1. Compute a histogram of the file (count the number of occurrences of each byte in the file).
	loadHistogram(sFile);
	// 2. Construct Huffman tree that represents the histogram (use a priority queue).
	loadTree();
	// 3. Construct code for each symbol (use a stack and perform a traversal of the Huffman tree).

	// 4. Emit encoding of Huffman tree to a file (perform a post-order traversal of the Huffman tree).

	// 5. Emit encoding of original file to the compressed file (use bit vectors with operations append and concatenate).

	// 6. Read the tree from the compressedfile, in order to do this you will use a stack.

	// 7. Decode the compressed bitstream into an identical copy of the original file. In order to do this, you will use
	//    the bits (0 means left, 1 means right) to guide your traversal of a reconstructed Huffman tree.

// Creates a histogram of char frequencies in file
uint32_t *loadHistogram(FILE *file)
{
	uint8_t c = 0; // keeps track of ascii character index
	uint32_t *hist = calloc(256, sizeof(uint32_t));
	if (hist) // check if calloc allocated space correctly
	{
		FILE *fp = fopen(file, "r"); // open file
		if (fp == NULL)
		{
			perror("Couldn't open file");
			exit(1);
		}

		// Increment first and last to ensure at least 2 elements
		hist[0]++;
		hist[255]++;

		// Read file
		while (feof(fp) != 0)
		{
			fread(fp, &c, 1); // after character is read...
			hist[c]++;		  // increment character frequency
		}
		fclose(fp); // close file
	}
	else
	{
		printf("failure to calloc space for histogram");
	}
	return hist;
}
