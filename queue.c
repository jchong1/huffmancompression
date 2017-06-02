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

queue *newLink(item item)
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
	// Never full because linked lists are unbounded
	return false;
}

// Enqueue should put the items from smallest -> biggest, head points at smallest element
bool enqueue(queue **head, item item)
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
		// If item trying to insert greater than the current node
		if (item->count >= current->item->count)
		{
			// Insert the item
			current->next = newLink(item);
			// Link the inserted item to the next node in the list
			current->next->next = nextNode;
		}
		else if (nextNode == NULL)
		{
			current->next = newLink(item);
			current->next->next = NULL;
		}
		current = nextNode;
	}
	return true;
}

// Dequeue should return the SMALLEST item
bool dequeue(queue **head, item *item)
{
	if (empty(q))
	{
		return false;
	}
	else
	{
		*item = *head->item;
		*head = *head->next;
		return true;
	}
}

int main(void)
{
	queue **head = malloc(sizeof(queue *));


	return 0;
}

