# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"

typedef uint32_t item; // treeNode defined in huffman.h 

typedef struct queue
{
	queue *next;	 // Pointer to next node	
	item item; 		 // Array to hold items (via calloc)
} queue;

queue *newQueue(uint32_t); 		// Constructor
void delQueue(queue *); 		// Deconstructor

bool empty(queue **);	// Is it empty?
bool full (queue **);	// Is it full?

bool enqueue(queue **, item ); // Add an item
bool dequeue(queue **, item *); // Remove from the rear 

# endif