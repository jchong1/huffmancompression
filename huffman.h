# ifndef _HUFFMAN_H
# define _HUFFMAN_H
# include <stdint.h>
# include <stdbool.h>

# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct DAH treeNode; 

struct DAH
{
<<<<<<< HEAD
	uint8_t symbol;
	uint64_t count;
	bool leaf;
=======
	uint8_t  symbol;
	uint64_t count;
	bool     leaf;
>>>>>>> d6b389ef141876aed6c8917d41717683fa9586d3
	treeNode *left, *right;
}; 

// New node, with symbols, leaf or not, a count associated with it
treeNode *newNode(uint8_t , bool , uint64_t );

// Delete a single node
treeNode *delNode(treeNode *);

// Delete a tree
treeNode *delTree(treeNode *);

// Dump a Huffman tree onto a file
void dumpTree(treeNode *, int);

// Build a tree from the saved tree
treeNode *loadTree(uint8_t);

// Step through a tree following the code
int32_t *stepTree(treeNode, treeNode, uint32_t);

// Parse a Huffman tree to build codes
void buildCode(treeNode *, code, code);

static inline void delNode(treeNode *h) { free(h); return; }

static inline bool compare(treeNode *l, treeNode *r)
{
	return l->count - r->count; // l < r if negative, l = r if 0, ...
}

treeNode *join(treeNode *, treeNode *); // Join two subtrees

# endif
