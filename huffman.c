# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>

# include "huffman.h"
# include "treestack.h"
# include "code.h"

treeNode *newNode(uint8_t , bool , uint64_t);
treeNode *loadTree(uint8_t *, uint16_t);
uint8_t *stepTree(treeNode *, treeNode **, uint32_t);
void buildCode(treeNode *, code, code *);
treeNode *delTree(treeNode *);

int main() // main to test huffman code
{
	uint8_t tree[4];
	tree[0] = 'L';
	tree[1] = 'H';
	tree[2] = 'L';
	tree[3] = 'i';
    return 0;
}

//------------------------------------------------------------------------------------------//
//-------------------------------------ENCODING FUNCTIONS-----------------------------------//
//------------------------------------------------------------------------------------------//

// New node, with symbols, leaf or not, a count associated with it
treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	// allocate space for a treeNode
	treeNode *node = (treeNode *) malloc(sizeof(treeNode));
	// set members of struct treeNode
	node -> symbol = s;
	node -> leaf = l;
	node -> count = c;
	node -> right = NULL;
	node -> left = NULL;
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
	// static uint32_t index = 0; 
	if (t->leaf) // if node is a leaf (base case)
	{
		// record current stack in code table
		// table[index++].bits = s;
		printf("record current stack in table!");
	}
	else
	{
		uint32_t ret;
		pushCode(&s, 0);
		buildCode(t->left, s, table);
		popCode(&s, &ret);
		pushCode(&s, 1);
		buildCode(t->right, s, table);
		popCode(&s, &ret);
	}
	return;
}

// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, int file)
{
	buf *b = newBuffer();
	int n = dumpTreeHelp(b, t);
	write(file, b, n);
	return;
}

// Helper function for dumpTree (pseudocode given by Arjun)
int dumpTreeHelp(buf *b, treeNode *t)
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
	return b->pos;
}

// Delete a tree
treeNode *delTree(treeNode *t)
{
	// while root of tree hasn't been deleted
	if (t != NULL)
	{
		delTree(t -> left);
		delTree(t -> right);
		free(t);
	}
	return NULL;
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
	treeNode *parentNode = newNode(symbol, leaf, parentCount);
	// return created node
	return parentNode;
}

void printTree(treeNode *t, int depth)
{
	if (t) 
	{
		printTree(t->left, depth + 1);
		if (t->leaf)
		{
			if (t->symbol)
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

//------------------------------------------------------------------------------------------//
//-------------------------------------DECODING FUNCTIONS-----------------------------------//
//------------------------------------------------------------------------------------------//

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	// Make a new stack
	treestack *s = newTreeStack();
	uint16_t i = 0;
	// Iterate over contents of savedTree from 0 to treeSize.
	while (i < treeBytes)
	{
		// If the element of the array is an L, then the next element will be the symbol for the leaf node. Use that
		// symbol to create a node using newNode. Then push this new node back onto the stack.
		if (savedTree[i] == 'L')
		{
			treeNode *leafNode = newNode(savedTree[i+1], true, 0);
			pushTree(s, *leafNode);
		}
		// If the element of the array is an I, then you have encountered an interior node. 
		// Pop once to get the right child of the interior child and then pop again to acquire the left child. 
		// Then create the interior node using join and then push the interior node back into the stack.
		if (savedTree[i] == 'I')
		{
			treeNode right = popTree(s);
			treeNode left = popTree(s);
			treeNode *interior = join(&left, &right);
			pushTree(s, *interior);
		}
		i += 2; // increment by 2
	}
	// After you finish iterating the loop, pop one last time. 
	// This should give you back the root of your Huffman tree.
	treeNode *root = (treeNode *) malloc(sizeof(treeNode));
	*root = popTree(s);
	return root;
}

// // Step through a tree following the code
// uint8_t *stepTree(treeNode *root, treeNode **t, uint32_t code)
// {
// 	// If you are at a leaf node, return the symbol for that leaf node and reset state to be back at the root.
// 	if (root->leaf) 
// 	{
// 		return &root->symbol;
// 	}
// 	// If you are at an interior node, return −1, signifying that a leaf node has not yet been reached.
// 	else if (root->symbol == '$')
// 	{
// 		return (uint8_t *)-1;
// 	}
// 	// Else, begin at the root of Huffman tree.
// 	else
// 	{	 
// 		*t = root;
// 		// If a bit of value 0 is read, move into the left child of the tree.
// 		if (code == 0)
// 		{
// 			t = t->left;
// 		}
// 		// If a bit of 1 is read, then move into the right child of the tree.
// 		if (code == 1)
// 		{
// 			t = t->right;
// 		}
// 	} 
// }
