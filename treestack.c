# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include "treestack.h"

# define TREESTACK_SIZE 256

// Code given by DDELL

// // Constructor
// treeNode *newNode(uint8_t s, bool l, uint64_t c)
// {
//     // allocate space for a treeNode
//     treeNode *node = (treeNode *) malloc(sizeof(treeNode));
//     // set members of struct treeNode
//     node -> symbol = s;
//     node -> leaf = l;
//     node -> count = c;
//     node -> right = NULL;
//     node -> left = NULL;
//     return node;
// }

// Constructor
treestack *newTreeStack()
{
	treestack *s = (treestack *) calloc(TREESTACK_SIZE, sizeof(treestack));
    s -> size = TREESTACK_SIZE;
    s -> top  = 0;
    s -> entries = (treeitem *) calloc(TREESTACK_SIZE, sizeof(treeitem));
    return s;
}	

// Deconstructor		
void delTreeStack(treestack *s)
{
	free(s -> entries); 
	free(s);
	return; 
}	

// Return the top treeitem
treeitem popTree(treestack *s)
{
	if (s -> top > 0)
    {
        s -> top -= 1;
        return s -> entries[s -> top];
    }
    else
    {
        return s -> entries[s -> top];
    }
}	

// Add an treeitem to the top	
void pushTree(treestack *s, treeitem i)
{
	if (s -> top == s -> size)
    {
        s -> size *= 2;
        s -> entries = (treeitem *) realloc(s -> entries, s -> size * sizeof(treeitem));
    }
    s -> entries[s->top] = i;
    s -> top += 1;
    return;
}	

// Is it empty?
bool emptyTree(treestack *s)
{
	return s -> top == 0;
}

// It it full?	
bool fullTree(treestack *s)
{
	return s -> top == TREESTACK_SIZE;
}	

// int main(void) // to test treestack functions
// {
//     uint32_t toPush;
//     treestack *s = newTreeStack();
//     do
//     {
//         printf("How many? "); scanf("%u", &toPush);
//         for (uint32_t i = 0; i < toPush; i += 1)
//         {
//             treeNode *testNode = newNode('$', false, i);
//             pushTree(s, *testNode);
//             delNode(testNode);
//         }
//         while (!emptyTree(s))
//         {
//             printf("%llu\n", popTree(s).count);
//         }
//     } while (toPush != 0);
//     delTreeStack(s);
//     return 0;
// }
