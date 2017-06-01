# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include "stack.h"

# define INVALID 0xDeadD00d
# define STACK_SIZE 256

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
void delStack(stack *s)
{
	free(s -> entries); 
	free(s);
	return; 
}	

// Return the top item
item pop(stack *s)
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
void push(stack *s, item i)
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
bool empty(stack *s)
{
	return s -> top == 0;
}

// It it full?	
bool full(stack *s)
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
            printf("%u\n", (uint32_t) pop(s));
        }
    } while (toPush != 0);
    return 0;
}
