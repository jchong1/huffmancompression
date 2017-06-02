# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <getopt.h>
# include <unistd.h>

# include "huffman.h"
# include "queue.h"

# define OPTIONS "i:o:v"
# define MAGIC_NUM 0xdeadd00d

uint32_t *loadHistogram(char *);
treeNode *enqueueNodes(uint32_t *);

bool iFlag = false,
	 oFlag = false;
char *sFile = NULL,
	 *oFile = NULL;

int main(int argc, char **argv)
{
	// Parse command-line arguments
	int encode;
	while ((encode = getopt(argc, argv, OPTIONS)) != -1)
	{
		switch (encode)
		{
			case 'i': // Set input file
			{
				iFlag = true;
				sFile = optarg;
				break;
			}
			case 'o': // Set output file
			{
				oFlag = true;
				oFile = optarg;
				break;
			}
			case 'v': // Verbose option
			{
				break;
			}
			default:
			{
				return - 1;
				break;
			}
		}
	}
	// Makes histogram of the file then constructs a Huffman tree that represents it.
	uint32_t *histogram = loadHistogram(sFile);
	treeNode *head = enqueueNodes(histogram);
	printf("printing tree!\n");
	printTree(head, 0);
	// Perform a post-order traversal of the Huffmantree (buildCode)		
	// Write out uint32_t magic number
	// Write length of the original file (in bytes) to oFile as a uint64_t
	// Write out the size of your tree (inbytes) to oFile as a uint16_t
	// Perform a post-order traversal of the Huffman tree to write the tree to the oFile (dumpTree)
	// and for each symbol copy the bits of the code for that symbol to the oFile.
	return 0;
}

// Creates a histogram of char frequencies in file
uint32_t *loadHistogram(char *file)
{
	// Construct histogram and increment the first and last to guarantee at 2 elements
  	uint32_t *histogram = calloc(256, sizeof(uint32_t));
  	histogram[0] += 1;
 	histogram[255] += 1;

 	// Set input file
 	FILE *input;
 	if (iFlag)
 	{
  	 	input = fopen(file, "r");
 	}
 	else
 	{
 		input = stdin;
 	}

  	int c = 0;
  	while ((c = fgetc(input))) 
  	{
    	if(c == EOF) 
    	{
    		break;
    	}
    	histogram[c] += 1;
  	}
  	fclose(input);
  	return histogram;
}

treeNode *enqueueNodes(uint32_t *histogram)
{
	queue **head = calloc(1, sizeof(queue *));
	for (int i = 0; i < 256; i++) 
  	{
    	if (histogram[i] > 0) 
    	{
      		treeNode *temp = newNode(i, true, histogram[i]);
      		enqueue(head, temp);
    	}
  	}
  	while ((*head)->next != NULL)
  	{
	  	treeNode *parent = join((*head)->item, (*head)->next->item);
	  	dequeue(head);
	  	dequeue(head);
	  	enqueue(head, parent);
	}
  	return (*head)->item;
}
