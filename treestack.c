# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include "treestack.h"

# define TREESTACK_SIZE 256

// Code given by DDELL

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
treeitem *popTree(treestack *s)
{
    if (s -> top > 0)
    {
        treeitem *element = calloc(1, sizeof(treeitem));
        *element = s->entries[--s->top];
        return element;
    }
    else
    {
        return NULL;
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
    s->entries[s->top++] = i;
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
