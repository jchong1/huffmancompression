# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include "stack.h"

# define INVALID 0xDeadD00d
# define STACK_SIZE 10

// Code given by DDELL

// Constructor
stack *newStack()
{
	stack *s = (stack *) calloc(STACK_SIZE, sizeof(stack));
    s -> size = STACK_SIZE;
    s -> top  = 0;
    s -> entries = (item *) calloc(STACK_SIZE, sizeof(item));
    return s;
}	

// Deconstructor		
voic delStack(stack *)
{
	free(s -> entries); 
	free(s);
	return; 
}	

// Return the top item
item pop (stack *)
{
	if (s -> top > 0)
    {
        s -> top -= 1;
        return s -> entries[s -> top];
    }
    else
    {
        return INVALID;
    }
}	

// Add an item to the top	
void push(stack *, item)
{
	if (s -> top == s -> size)
    {
        s -> size *= 2;
        s -> entries = (item *) realloc(s -> entries, s -> size * sizeof(item));
    }
    s -> entries[s->top] = i;
    s -> top += 1;
    return;
}	

// Is it empty?
bool empty(stack *)
{
	return s -> top == 0;
}

// It it full?	
bool full(stack *)
{
	return s -> top == STACK_SIZE;
}	

int main(void) // to test stack functions
{
    uint32_t toPush;
    stack *s = newStack();
    do
    {
        printf("How many? "); scanf("%u", &toPush);
        for (uint32_t i = 0; i < toPush; i += 1)
        {
            push(s, i);
        }
        while (!empty(s))
        {
            printf("%lu\n", (uint32_t) pop(s));
        }
    } while (toPush != 0);
    return 0;
}
