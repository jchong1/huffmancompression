# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "queue.h"
# include "huffman.h"

# ifndef MAX
# define MAX 10
# endif

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
	return ((q -> head + 1) % q -> size) == (q -> tail % q -> size);
}

// Enqueue should put the items from biggest -> smallest, head points at biggest element
bool enqueue(queue *q, item i)
{
	if (full(q))
	{
		return false;
	}
	else if (empty(q))
	{
		q->Q[q->head] = i;
		q->head = 1;
		return true;
	}
	else
	{
		for (uint32_t i = 0; i < sizeof(q->Q); i++)
		{
			treeNode current = q->Q[i];
			// Compare count to see if you want to insert item at the current index
			if (item->count < current->count)
			{
				// shift elements to the right of the index to the right
				for (uint32_t k = i + 1; k < sizeof(q->Q); k++)
				{
					q->Q[k + 1] = q->Q[k];
				}
				// insert the item into the array
				q->Q[i] = i;
				q->head = (q->head + 1) % q->size;
				return true;
			}

		}
	}
}

// Dequeue should return the SMALLEST item
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

int main(void)
{
        uint32_t count = 0;
        queue   *q     = newQueue(2 * MAX);

        srandom((long) time((time_t *) 0));
        do
        {
                uint32_t add = random() % MAX;

                printf("Adding %u elements\n", add);
                for (uint32_t i = 0; i < add; i += 1)
                {
                        if (full(q))
                        {
                                printf("Ouch! Full with only %u!\n", i);
                                break;
                        }
                        else
                        {
                                item x = random() % 1000;
                                printf("\t%4u\n", x);
                                (void) enqueue(q, x);
                                count += 1;
                        }
                }

                uint32_t pop = random() % MAX;

                printf("Popping %u elements\n", pop);
                for (uint32_t i = 0; i < pop; i += 1)
                {
                        if (empty(q))
                        {
                                printf("Woah! Empty after only %u!\n", i);
                                break;
                        }
                        else
                        {
                                item x;
                                (void) dequeue(q, &x);
                                printf("\t%4u\n", x);
                        }
                }
        } while (!empty(q));
}

