# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"

typedef treeNode item; // treeNode defined in huffman.h 
typedef struct queue
{
	uint32_t size; 		 // How big is it?
	uint32_t head, tail; // Front and rear locations
	item *Q; 			 // Array to hold it (via calloc)
} queue;

queue *newQueue(uint32_t); 		// Constructor
void delQueue(queue *); 		// Deconstructor

bool empty(queue *);	// Is it empty?
bool full (queue *);	// Is it full?

bool enqueue(queue *, item ); // Add an item
bool dequeue(queue *, item *); // Remove from the rear 

# endif