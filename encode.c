# include <stdio.h>

uint32_t *loadHistogram(char *);
void constructCode(treeNode *);

int main()
{
	// 1. Compute a histogram of the file (count the number of occurrences of each byte in the file).
	loadHistogram();
	// 2. Construct Huffman tree that represents the histogram (use a priority queue).
	loadTree();
	// 3. Construct code for each symbol (use a stack and perform a traversal of the Huffman tree).

	// 4. Emit encoding of Huffman tree to a file (perform a post-order traversal of the Huffman tree).

	// 5. Emit encoding of original file to the compressed file (use bit vectors with operations append and concatenate).

	// 6. Read the tree from the compressedfile, in order to do this you will use a stack.

	// 7. Decode the compressed bitstream into an identical copy of the original file. In order to do this, you will use
	//    the bits (0 means left, 1 means right) to guide your traversal of a reconstructed Huffman tree.

// Creates a histogram of char frequencies in file
uint32_t *loadHistogram(char *file)
{
	uint8_t c = 0; // keeps track of ascii character index
	uint32_t *hist = calloc(256, sizeof(uint32_t));
	if (hist)
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

void constructCode(treeNode *node)
{
	// below is pseudocode
	// should use a stack somewhere
	if (node->leaf) // if node is a leaf
	{
		record in array
	}
	else
	{
		push 0
		constructCode(node->left);
		push 1
		constructCode(node->right);
	}
	pop
	return;
}
