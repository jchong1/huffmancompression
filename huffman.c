# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"
# include "code.h"

// New node, with symbols, leaf or not, a count associated with it
treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	// allocate space for a treeNode
	struct treeNode *node = (listNode *) malloc(sizeof(listNode));
	// set members of struct treeNode
	node -> symbol = s;
	node -> leaf = l;
	node -> count = c;
	node -> *right = NULL;
	node -> *left = NULL;
	return node;
}

// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, int file)
{
	
}

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	// Make a new stack
	stack *s = newStack();
	// Iterate over contents of savedTree from 0 to treeSize.
	for (uint16_t i = 0; i < treeBytes; i++)
	{
		// If the element of the array is an L, then the next element will be the symbol for the leaf node. Use that
		// symbol to create a node using newNode. Then push this new node back onto the stack.
		if (savedTree[i] == 'L')
		{
			treeNode *leafNode = newNode(savedTree[i], true, 0);
			push(s, leafNode);
		}
		// If the element of the array is an I, then you have encountered an interior node. 
		// Pop once to get the right child of the interior child and then pop again to acquire the left child. 
		// Then create the interior node using join and then push the interior node back into the stack.
		if (savedTree[i] == 'I')
		{
			treeNode *right = pop(s);
			treeNode *left = pop(s);
			treeNode *interior = join(left, right);
		}
	}
	// After you finish iterating the loop, pop one last time. 
	// This should give you back the root of your Huffman tree.
	treeNode *root = pop(s);
	return root;
}

// Step through a tree following the code
int32_t *stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	// If you are at a leaf node, return the symbol for that leaf node and reset state to be back at the root.
	if (root->leaf) 
	{
		return root->symbol;
	}
	// If you are at an interior node, return −1, signifying that a leaf node has not yet been reached.
	else if (root->symbol == '$')
	{
		return -1;
	}
	// Else, begin at the root of Huffman tree.
	else
	{	 
		*t = root;
		// If a bit of value 0 is read, move into the left child of the tree.
		if (code == 0)
		{
			stepTree(t->left, t, code);
		}
		// If a bit of 1 is read, then move into the right child of the tree.
		if (code == 1)
		{
			stepTree(t->right, t, code);
		}
	} 
}

// Parse a Huffman tree to build codes
void buildCode(treeNode *t, code s, code table[256])
{
	static uint32_t index = 0; 
	if (node->leaf) // if node is a leaf (base case)
	{
		// record current stack in code table
		table[index++]->bits = s;
	}
	else
	{
		pushCode(s, 0);
		buildCode(node->left);
		popCode(s, table);
		pushCode(s, 1);
		buildCode(node->right);
		popCode(s, table);
	}
	return;
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

int main() // main to test huffman code
{
    treeNode *root 			= newNode(1); 
    root -> left            = newNode(2);
    root -> right          	= newNode(3);
    root -> left -> left    = newNode(4);
    root -> left -> right   = newNode(5); 
   
    deleteTree(root);  
    root = NULL;
 
    printf("\n Tree deleted ");
    return 0;
}
