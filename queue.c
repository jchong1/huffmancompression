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

bool full(queue **q)
{
	// Never full because linked lists are unbounded
	return false;
}

// Enqueue should put the items from smallest -> biggest, head points at smallest element
bool enqueue(queue **head, item *item)
{
	if (full(head))
	{
		return false;
	}
	if (empty(head))
	{
		printf("if empty\n");
		*head = newLink(*item);
		return true;
	}
	queue *current = *head; //make new?
	queue *nextNode;

	if (item->count <= current->item.count)
	{
		printf("inserting at head\n");
		queue *nL = newLink(*item);
		nL->next = current;
		*head = nL;
		return true;
	}

	while (current != NULL)
	{
		printf("current is not null\n");
		nextNode = current->next;

		if (nextNode == NULL)
		{
			printf("inserting biggest element\n");
			current->next = newLink(*item);
			break;
		}

		// If item trying to insert greater than the current node
		else if (item->count >= current->item.count && item->count <= nextNode->item.count)
		{
			printf("item is bigger\n");
			// Insert the item
			current->next = newLink(*item);
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
bool dequeue(queue **head, item *item)
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
		printf("%llu\n", temp->item.count);
		temp = temp->next;
	}
}

int main(void)
{
	srand(1);
	treeNode *firstNode = newNode(1, false, rand() % 100);
	treeNode *secondNode = newNode(1, false, rand() % 100);
	treeNode *thirdNode = newNode(1, false, rand()% 100);
	treeNode *fourthNode = newNode(1, false, rand() % 100);
	treeNode *fifthNode = newNode(1, false, rand() % 100);
	
	treeNode *dequeued = NULL;


	queue **queueHead = calloc(1, sizeof(queue *));

	enqueue(queueHead, firstNode);
	enqueue(queueHead, secondNode);
	enqueue(queueHead, thirdNode);
	enqueue(queueHead, fourthNode);
	enqueue(queueHead, fifthNode);
	dequeue(queueHead, dequeued);
	printQueue(queueHead);
	// printf("%llu", dequeued->count);
	// printQueue(queueHead);

	return 0;
}

