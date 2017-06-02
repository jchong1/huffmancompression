# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <stdbool.h>

# define OPTIONS "i:o:v"
# define MAGIC 0xdeadd00d

int main(int argc, char *argv[])
{
	int d;
	char *sFile = NULL, *oFile = stdout;
	uint32_t magicNum;
	uint64_t oFileSize;
	uint8_t treeSize;

	while (d = getopt(argc, argv, OPTIONS) != -1)
	{
		switch (d)
		{
			case i:
			{
				// file being read from
				sFile = strdup(optarg);
				break;
			}
			case o:
			{
				// file being written to (default stdout)
				oFile = strdup(optarg);
				break;
			}
			case v:
			{
				// verbose option
				break;
			}
		}
	}

	// throw an error, need a file to decode
	if (sFile == NULL)
	{
		printf("Must have an input file.");
		exit(1);
	}

	FILE *sFP = fopen(sFile, "r");
	FILE *oFP = fopen(oFile, "w");

	// Read in magic number
	fread(magicNum, sizeof(magicNum), sFP);

	// If magic number doesn't match 0xdeadd00d, display error message and quit.
	if (magicNum != MAGIC)
	{
		printf("File compressed incorrectly, exiting...");
		exit(1);
	}
	
	// Read next 8 bytes of the sFile to get exact size of oFile
	fread(oFileSize, sizeof(oFileSize), sFP);

	// Read next 2 bytes of sFile and call it treeSize
	fread(treeSize, sizeof(treeSize), sFP);

	// Allocate an array(savedTree) of uint8_t’s which is treeSize long
	uint8_t savedTree = calloc(treeSize, sizeof(uint8_t));

	// Read in the sFile for treeSize bytes into savedTree
	fread(savedTree, treeSize, sFP);

	// use previously mentioned array to reconstruct your Huffman tree using loadTree (use a stack)

	//	a) Iterate contents of savedTree from 0 to treeSize.

	//	b) If the element of the array is an L, then the next element will be the symbol for the leaf node. Use that
	//	   symbol to create a node using newNode. Now, push this new node back onto the stack.

	//	c) If the element of the array is an I, then you have encountered an interior node. 
	//     At this point, you pop once to get the right child of the interior child and then pop again to acquire the left child. 
	//	   Now, create the interior node using join and then push the interior node back into the stack.

	//	d) After you finish iterating the loop, pop one last time. This should give you back the root of your Huffman tree.

	// Read in a bit at a time from the sFile. For each bit, step through the tree using stepTree.

	//	a) Begin at the root of the Huffman tree. If a bit of value 0 is read, move into left child of the tree. 
	//	   If a bit of 1 is read, then move into the right child of the tree.

	//  b) In case after stepping you are at a leaf node, then return the symbol for that leaf node and reset 
	//     your state to be back at the root.  Output this symbol onto the oFile. 
	//     Note: You may buffer these symbols into an array and then write out the entire array once at the end. 
	//     Hint: The size of this array should be known to you because of step 2 (read next 8 bytes of sFile)
	
	//	c) if after stepping you are at an interior node, return −1 to show that a leaf node has not yet been reached.

	//  d) Repeat until all bits in the sFile have been exhausted
	//     (Caution:there may very well be a few extrabits in the last byte, 
	//      and those could make a symbol; emitting that symbol would be wrong).

	// At this point, you should have a fully decompressed oFile which should match the size of the original file.
	
	return 0;
}
