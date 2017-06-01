# ifndef _HUFFMAN_H
# define _HUFFMAN_H
# include <stdint.h>
# include <stdbool.h>

# include "code.h"

# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct DAH treeNode; 

struct DAH
{
	uint8_t  symbol;
	uint64_t count;
	bool     leaf;
	treeNode *left, *right;
}; 

typedef struct BUFFER buf;

struct BUFFER
{
	char *arr;
	int pos;
};

// New node, with symbols, leaf or not, a count associated with it
treeNode *newNode(uint8_t , bool , uint64_t);

// New buffer
buf *newBuffer();

// Dump a Huffman tree onto a file
void dumpTree(treeNode *, int);

// Helper function for dumpTree (pseudocode given by Arjun)
int dumpTreeHelp(buf *, treeNode *);

// Build a tree from the saved tree
treeNode *loadTree(uint8_t *, uint16_t);

// Step through a tree following the code
uint8_t stepTree(treeNode *, treeNode **, uint32_t);

// Parse a Huffman tree to build codes
void buildCode(treeNode *, code, code *);

// Delete a tree
treeNode *delTree(treeNode *);

static inline void spaces(int c) { for (int i = 0; i < c; i += 1) { putchar(' '); } return; }

static inline void delNode(treeNode *h) { free(h); return; }

static inline bool compare(treeNode *l, treeNode *r)
{
	return l->count - r->count; // l < r if negative, l = r if 0, ...
}

treeNode *join(treeNode *, treeNode *); // Join two subtrees

# endif
