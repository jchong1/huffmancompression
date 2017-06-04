# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

// # include "queue.h"
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
				sFile = fopen(strdup(optarg), "r");
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
	printf("File size: %llu\n", oFileSize);

	// Read next 2 bytes of sFile and call it treeSize
	fread(&treeSize, sizeof(uint8_t), 2, sFile);
	printf("Tree Size: %d\n", treeSize);

	// Allocate an array(savedTree) of uint8_t’s which is treeSize long
	uint8_t *savedTree = (uint8_t *) calloc(treeSize, sizeof(uint8_t));

	// Read in the sFile for treeSize bytes into savedTree
	for (uint16_t i = 0; i < treeSize; i++)
	{
		fread(&savedTree[i], sizeof(uint8_t), 1, sFile);
	}
	for (uint16_t i = 0; i < treeSize; i++)
	{
		printf("%d ", savedTree[i]);
	}

	// use previously mentioned array to reconstruct your Huffman tree using loadTree (use a stack)
	treeNode *tree = loadTree(savedTree, treeSize);

	// printTree(tree, 0);	
	printf("%c\n", (*tree).symbol);

	// fseek(sFile, SEEK_CUR, SEEK_END);

	for (uint64_t i = 0; i < oFileSize * 8; i++)
	{
		printf("%d", getBit(sFile));
	}
	
	return 0;
}

