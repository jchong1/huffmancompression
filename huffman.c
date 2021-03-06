# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>

# include "huffman.h"
# include "treestack.h"
# include "code.h"

bool oFlag = false;

// New node, with symbols, leaf or not, a count associated with it
treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	// allocate space for a treeNode
	treeNode *node = (treeNode *) malloc(sizeof(treeNode));
	// set members of struct treeNode
	node->symbol = s;
	node->leaf = l;
	node->count = c;
	node->right = NULL;
	node->left = NULL;
	return node;
}

// New buffer
buf *newBuffer()
{
	buf *b = (buf *) malloc(sizeof(buf));
	b->arr = calloc(768, sizeof(char));
	b->pos = 0;
	return b;
}

// Parse a Huffman tree to build codes
void buildCode(treeNode *t, code s, code table[256])
{
	if (t->leaf) // if node is a leaf (base case)
	{
		// record current stack in code table
		table[t->symbol] = s;
	}
	else
	{
		// Boris helped with this code
		uint32_t ret = 0;
		pushCode(&s, ret);
		buildCode(t->left, s, table);
		popCode(&s, &ret);
		ret = 1;
		pushCode(&s, ret);
		buildCode(t->right, s, table);
		popCode(&s, &ret);
	}
	return;
}

// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, char *oFile)
{
	buf *b = newBuffer();
	dumpTreeHelp(b, t);
	FILE *output;
 	if (oFlag)
 	{
 		output = fopen(oFile, "a");
 	}
 	else
 	{
 		output = stdout;
 	}
	fwrite(b->arr, 1, b->pos, output);
    if (oFlag)
    {
        fclose(output);
    }
    free(b->arr);
    free(b);
	return;
}

// Helper function for dumpTree (pseudocode given by Arjun)
void dumpTreeHelp(buf *b, treeNode *t)
{
	if (t->leaf)
	{
		b->arr[b->pos++] = 'L';
		b->arr[b->pos++] = t->symbol;
	}
	else
	{
		dumpTreeHelp(b, t->left);
		dumpTreeHelp(b, t->right);
		b->arr[b->pos++] = 'I';
	}
	return;
}

// Delete a tree
void delTree(treeNode *t)
{
	// while root of tree hasn't been deleted
	if (t != NULL)
	{
		delTree(t -> left);
		delTree(t -> right);
		free(t);
	}
	return;
}

// Join two subtrees
treeNode *join(treeNode *l, treeNode *r)
{
	// get sum of child node counts
	uint64_t parentCount = (l -> count) + (r -> count);
	// internal node symbol is $
	uint8_t symbol = '$';
	// is parent node isn't a leaf
	bool leaf = false;
	// create new node
	treeNode *parent = newNode(symbol, leaf, parentCount);
	parent->left = l;
	parent->right = r;
	// return created node
	return parent;
}

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	// Make a new stack
	treestack *s = newTreeStack();
	uint16_t i = 0;
    treeNode *root = NULL;
	// Iterate over contents of savedTree from 0 to treeSize.
	while (i < treeBytes)
	{
		// If the element of the array is an L, then the next element will be the symbol for the leaf node. Use that
		// symbol to create a node using newNode. Then push this new node back onto the stack.
		if (savedTree[i] == 'L')
		{
			treeNode *leafNode = newNode(savedTree[++i], true, 0);
			pushTree(s, *leafNode);
		}
		// If the element of the array is an I, then you have encountered an interior node. 
		// Pop once to get the right child of the interior child and then pop again to acquire the left child. 
		// Then create the interior node using join and then push the interior node back into the stack.
        else if (savedTree[i] == 'I')
		{
			treeNode *right = popTree(s);
			treeNode *left = popTree(s);
			treeNode *interior = join(left, right); 
			pushTree(s, *interior);
		}
        i++;
	}
	// After you finish iterating the loop, pop one last time. 
	// This should give you back the root of your Huffman tree.
	root = popTree(s);
    delTreeStack(s);
    return root;
}

// Step through a tree following the code
int32_t stepTree(treeNode **t, uint32_t code)
{
	// If a bit of value 0 is read, move into the left child of the tree.
	if (code == 0)
	{
		*t = (*t)->left;
	}
	// If a bit of 1 is read, then move into the right child of the tree.
    else if (code == 1)
	{
		*t = (*t)->right;
	}
	// If at a leaf node, then return the symbol for that leaf node and reset your state to be back at the root.
	if ((*t)->leaf)
	{
		int32_t s = (int32_t) (*t)->symbol;
		return s;
	}
	// Else, you are at an interior node so return −1, to signify that a leaf node has not yet been reached.
	else
	{
		return -1;
	}
}

// Given by DDELL
void printTree(treeNode *t, int depth)
{
	if (t) 
	{
		printTree(t->left, depth + 1);

		if (t->leaf)
		{
			if (isalnum(t->symbol))
			{
				spaces(4 * depth); printf("'%c' (%llu)\n", t->symbol, t->count);
			}
			else
			{
			spaces(4 * depth); printf("0x%X (%llu)\n", t->symbol, t->count);
			}
		}
		else
		{
			spaces(4 * depth); printf("$ (%llu)\n", t->count);
		}
		printTree(t->right, depth + 1); 
	}
	return;
}
