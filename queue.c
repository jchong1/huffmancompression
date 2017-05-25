# include <stdint.h>
# include <stdbool.h>

# include "queue.h"
# include "huffman.h"

// Code given by DDELL

queue *newQueue(uint32_t size)
{
	queue *q = (queue *) malloc(sizeof(queue));
	q -> size = size;
	q -> head = q -> tail = 0;
	q -> Q = (item *) calloc(size, sizeof(item));
	return q;
}

void delQueue(queue *q)
{
	free(q -> Q); 
	free(q); 
	return;
}

// Return whether the queue is empty or full
bool empty(queue *q)
{
	return q -> head == q -> tail;
}

bool full(queue *q)
{
	return (q -> head + 1) % q -> size == q -> tail % q -> size;
}


bool enqueue(queue *q, item i)
{
	if (full(q))
	{
		return false;
	}
	else
	{
		q->Q[q->head] = i;
		q->head = (q->head + 1) % q->size;
		return true;
	}
}

bool dequeue(queue *q, item *i)
{
	if (empty(q))
	{
		return false;
	}
	else
	{
		*i = q->Q[q->tail];
		q->tail = (q->tail + 1) % q->size;
		return true;
	}
}
