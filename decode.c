# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

# include "huffman.h"
# include "treestack.h"
# include "code.h"
# include "stack.h"
# include "bv.h"

# define OPTIONS "i:o:v"
# define MAGIC 0xdeadd00d

int main(int argc, char *argv[])
{
	int d;
    bool v = false;
	FILE *sFile = NULL, *oFile = NULL;
	uint32_t magicNum = 0;
	uint64_t oFileSize = 0;
	uint16_t treeSize = 0;

	while ((d = getopt(argc, argv, OPTIONS)) != -1)
	{
		switch (d)
		{
			case 'i':
			{
				// file being read from
				sFile = fopen(optarg, "r");
				break;
			}
			case 'o':
			{
				// file being written to (defaults to stdout if no file)
				oFile = fopen(strdup(optarg), "w");
				break;
			}
			case 'v':
			{
				// verbose option
                v = true;
				break;
			}
		}
	}
	// Throw an error if there is not input file
	if (sFile == NULL)
	{
		printf("Error: must have an input file\n");
		exit(1);
	}

	// Default to stdout
	if (oFile == NULL)
	{
		oFile = stdout;
	}

	// Read in magic number
	fread(&magicNum, sizeof(uint8_t), 4, sFile);

	// If magic number doesn't match 0xdeadd00d, display error message and quit.
	if (magicNum != MAGIC)
	{
		printf("Error: file not compressed or compressed incorrectly\n");
		exit(1);
	}
	
	// Read next 8 bytes of the sFile to get exact size of oFile
	fread(&oFileSize, sizeof(uint8_t), 8, sFile);

	// Read next 2 bytes of sFile and call it treeSize
	fread(&treeSize, sizeof(uint8_t), 2, sFile);

	// Allocate an array(savedTree) of uint8_t’s which is treeSize long
	uint8_t *savedTree = (uint8_t *) calloc(treeSize, sizeof(uint8_t));

	// Read in the sFile for treeSize bytes into savedTree
	for (uint16_t i = 0; i < treeSize; i++)
	{
		fread(&savedTree[i], sizeof(uint8_t), 1, sFile);
	}

	// use previously mentioned array to reconstruct your Huffman tree using loadTree (use a stack)
	treeNode *tree = loadTree(savedTree, treeSize);

    // Create a pointer to tree
    treeNode **treeP = calloc(1, sizeof(treeNode *));
    *treeP = tree;

	int32_t symbol;
    uint64_t byteCount = 0; // Number of bytes written
    uint64_t bitCount = 0; // Number of bits read
    char text[oFileSize];
	while(byteCount < oFileSize)
	{
		symbol = stepTree(tree, treeP, getBit(sFile)); 
        bitCount++;
		if (symbol != -1) // Returns -1 when on an internal node
		{
			text[byteCount] = symbol;
            *treeP = tree; // Reset the tree pointer to root once leaf found
            byteCount++; 
		}
	}

    if (v)
    {
        printf("Original %lu bits: tree (%d)\n", bitCount, treeSize);
    }
    for (uint64_t i = 0; i < oFileSize; i++)
    {
        fputc(text[i], oFile);
    }

    free(treeP);
    free(savedTree);
    delTree(tree);
    fclose(sFile);
    fclose(oFile);
	
	return 0;
}

