# include <stdint.h>
# include <stdbool.h>

# include "queue.h"
# include "huffman.h"

queue *newQueue(uint32_t size)
{
	struct queue *q = malloc(sizeof(queue));
	q->size = size;

	// Allocate enough memory for the number of items you want
	q->Q = (item *) calloc(size, sizeof(item));

	// Nothing in the queue yet
	q->head = 0;
	q->tail = 0;

	return q;
}

void delQueue(queue *q)
{
	free(q->Q);
	free(q);
	return;
}

// Return whether the queue is empty or full
bool empty(queue *q)
{
	return (q->head == 0 && q->tail == 0);
}

bool full(queue *q)
{
	return (q->head == q->size - 1);
}


bool enqueue(queue *q, item i)
{

}

bool dequeue(queue *q, item *i)
{

}