# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"

treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	// code
}

// Delete a tree
treeNode *delTree(treeNode *t)
{
	
}

// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, int file)
{
	// code
}

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[])
{
	// code
}

// Step through a tree following the code
int32_t *stepTree(treeNode *root, treeNode *t, uint32_t code)
{
	// code
}

// Parse a Huffman tree to build codes
void buildCode(treeNode *t, code s, code table[256])
{
	// code
}

// Join two subtrees
treeNode *join(treeNode *l, treeNode *r)
{
	// code
}

