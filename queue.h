# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"

typedef treeNode item; // treeNode defined in huffman.h 

typedef struct queue
{
	struct queue *next;	 // Pointer to next node	
	item *item; 		 	 // Array to hold items (via calloc)
	// 
} queue;

queue *newLink(item *); 		// Constructor
void delQueue(queue **); 		// Deconstructor

bool empty(queue **);	// Is it empty?

bool enqueue(queue **, item *); // Add an item
bool dequeue(queue **); // Remove from the rear 
void printQueue(queue **);

# endif
