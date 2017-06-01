# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "queue.h"
# include "huffman.h"
# include "code.h"

# ifndef MAX
# define MAX 10
# endif

// Code given by DDELL

queue *newNode(item item)
{
	queue *q = (queue *) malloc(sizeof(queue));
	q->next = NULL;
	q->item = item;
	return q;
}

void delQueue(queue **head)
{
	queue *temp = *head;
	queue *nextNode;
	while (temp != NULL)
	{
		nextNode = temp->next;
		free(temp);
		temp = nextNode;
	}
	return;
}

// Return whether the queue is empty or full
bool empty(queue **head)
{
	return (*head == NULL);
}

bool full(queue *q)
{
	return false;
	// return (q->head + 1 == q->size);
}

// Enqueue should put the items from biggest -> smallest, head points at biggest element
bool enqueue(queue **q, item item)
{
	if (full(q))
	{
		return false;
	}
	queue *current = *head;
	queue *nextNode;
	while (current != NULL)
	{
		nextNode = current->next;
		if (item > current->item)
		{
			current->next = newNode(item);
			current->next->next = nextNode;
		}
	}
	return true;
}

// Dequeue should return the SMALLEST item
bool dequeue(queue **head, item *i)
{
	if (empty(q))
	{
		return false;
	}
	else
	{
		*i = *head->item;
		*head = *head->next;
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
		for (item i = q->tail; i < q->size; i++)
        {
        	printf("%d ", q->Q[i]);
        }
        printf("\n");
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
        for (item i = q->tail; i < q->size; i++)
        {
        	printf("%d ", q->Q[i]);
        }
        printf("\n");
    } while (!empty(q));
}

