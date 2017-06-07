# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "queue.h"
# include "huffman.h"
// # include "code.h"

# ifndef MAX
# define MAX 10
# endif

// Code given by DDELL

queue *newLink(item *item)
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

// Enqueue should put the items from smallest -> biggest, head points at smallest element
bool enqueue(queue **head, item *item)
{
	if (empty(head))
	{
		*head = newLink(item);
		return true;
	}
	queue *current = *head; //make new?
	queue *nextNode;

	if (item->count <= current->item->count)
	{
		queue *nL = newLink(item);
		nL->next = current;
		*head = nL;
		return true;
	}

	while (current != NULL)
	{
		nextNode = current->next;
		if (nextNode == NULL)
		{
			current->next = newLink(item);
			break;
		}
		// If item trying to insert greater than the current node
		else if (item->count > current->item->count && item->count <= nextNode->item->count)
		{
			// Insert the item
			current->next = newLink(item);
			// Link the inserted item to the next node in the list
			current->next->next = nextNode;
			break;
		}
		// If the item is the largest, make last link		
		current = nextNode;
	}
	return true;
}

// Dequeue should return the SMALLEST item
bool dequeue(queue **head)
{
	if (empty(head))
	{
		return false;
	}
	else
	{
		// *item = (*head)->item;
		*head = (*head)->next;
		return true;
	}
}

void printQueue(queue **head)
{
	queue *temp = *head;
	while (temp != NULL)
	{
		printf("%llu\n", temp->item->count);
		temp = temp->next;
	}
}
