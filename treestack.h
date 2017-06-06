# ifndef _TREESTACK_H
# define _TREESTACK_H
# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"

typedef treeNode treeitem; // You will need to change this

typedef struct treestack
{
	uint32_t size; // How big?
	uint32_t top;  // Where's the top?
	treeitem *entries; // Array to hold it (via calloc)
} treestack;

treestack *newTreeStack();			// Constructor
void delTreeStack(treestack *);		// Deconstructor

treeitem *popTree (treestack *);			// Returns the top item
void pushTree(treestack *, treeitem);	// Adds an item to the top

bool emptyTree(treestack *);		// Is it empty?
bool fullTree(treestack *);			// It it full?

# endif
