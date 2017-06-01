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
	// use reverse polish notation
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
uint32_t *stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	// code
	for (uint32_t i = 0; i < code->l; i++)
	{
		if (code->bits[i] == 0 && !root->leaf)
		{
			stepTree(root->left, t, code);
		}
		else if (code->bits[i] == 1 && !root->leaf)
		{
			stepTree(root->right, t, code);
		}
	}
	// have to return something
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
