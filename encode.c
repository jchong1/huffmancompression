# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <getopt.h>
# include <ctype.h>

# include "huffman.h"
# include "queue.h" 
# include "bv.h"

# define OPTIONS "i:o:vpf"
# define MAGIC_NUM 0xdeadd00d

// Function prototypes
void loadHistogram(char *, uint32_t *);
void loadOutput(char *);
void loadCodes(code *, char *, char *, treeNode *);
treeNode *loadNodes(uint32_t *);

// Variables
bool verbose = false,
	   iFlag = false,
	    full = false,
	   print = false; 
extern bool oFlag;
char *sFile = NULL,
	 *oFile = NULL;
uint16_t treeSize = 0; 
uint32_t magicNum = MAGIC_NUM;
uint64_t fileLength = 0;

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
				verbose = true;
				break;
			}
			case 'p': // Print tree option
			{
				print = true;
				break;
			}
			case 'f': // Full tree option
			{
				full = true;
				break;
			}
		}
	}

	// Make histogram of the file and construct Huffman tree from the histogram
	uint32_t *histogram = calloc(256, sizeof(uint32_t));
	loadHistogram(sFile, histogram);
	treeNode *head = loadNodes(histogram);
	// Perform a post-order traversal of the Huffman tree (buildCode)	
	code s = newCode();
	code *table = calloc(256, sizeof(code));
	buildCode(head, s, table);
	// Write out magic number, length of original file and size of tree to oFile;
	loadOutput(oFile);
	// Perform a post-order traversal of the Huffman tree to write the tree to the oFile (dumpTree)
	dumpTree(head, oFile);
	// For each symbol copy the bits of the code for that symbol to the oFile.
	loadCodes(table, sFile, oFile, head);
	// Free allocated memory
	free(histogram);
	free(table);
    delTree(head);
	return 0;
}

// Creates a histogram of char frequencies in file
void loadHistogram(char *inFile, uint32_t *histogram)
{
  // Construct histogram and increment the first and last to guarantee at 2 elements
  	int c = 0;
    histogram[0] += 1;
  	histogram[255] += 1;
  	// Set input file
  	FILE *input = NULL;
  	if (iFlag)
  	{
      	input = fopen(inFile, "r");
        if (input == NULL)
        {
            printf("./encode: %s: No such file or directory\n", inFile);
            exit(1);
        }   
  	}
  	else
  	{
    	printf("Please specify an input file.\n");
        exit(1);
  	}
    while ((c = fgetc(input))) 
    {
      	if(c == EOF) 
      	{
        	break;
      	}
      	histogram[c] += 1;
      	fileLength += 1;
    }
    fclose(input);
    return;
}

treeNode *loadNodes(uint32_t *histogram)
{
  	queue **head = calloc(1, sizeof(queue *));
  	for (int i = 0; i < 256; i++) 
    {
      	if (histogram[i] > 0) 
      	{
      	   	treeNode *temp = newNode(i, true, histogram[i]);
         	enqueue(head, temp);
         	treeSize += 1;
      	}
    }
    while ((*head)->next != NULL)
    {
      	treeNode *parent = join((*head)->item, (*head)->next->item);
      	dequeue(head);
      	dequeue(head);
    	enqueue(head, parent);
  	}
  	treeSize = (3 * treeSize) - 1;
    return (*head)->item;
}

void loadOutput(char *outFile)
{
  	FILE *output;
  	if (oFlag)
  	{
     	output = fopen(outFile, "w");
  	}
  	else
  	{
    	output = stdout;
  	}
  	// Write magic number, file length, and tree size to oFile
  	fwrite(&magicNum, sizeof(uint32_t), 1, output);
  	fwrite(&fileLength, sizeof(uint64_t), 1, output);
  	fwrite(&treeSize, sizeof(uint16_t), 1, output);
    if (oFlag)
    {   
        fclose(output);
    }
  	return;
}

void loadCodes(code *table, char *inFile, char *outFile, treeNode *head)
{
  	FILE *input,
     	 *output;
    input = fopen(inFile, "r");
  	if (oFlag)
  	{
      	output = fopen(outFile, "a");
  	}
  	else
  	{
    	output = stdout;
  	}
  	int c = 0;
  	bitV *code = newVec(1);
  	fseek(input, 0, SEEK_SET);
    while((c = getc(input)) != EOF)
    {
      	appendVec(code, table[c]);
    } 
    bitV *trimmedCode = newVec((code->length) - 1);
    for (uint32_t j = 0; j < code->length; j++)
    {
      	if (valBit(code, j + 1))
      	{
      	  	setBit(trimmedCode, j);
      	}
      	else
      	{
        	clrBit(trimmedCode, j);
    	}
    }
    fwrite(trimmedCode->vector, 1, trimmedCode->length/8 + 1, output);
    if (print) 
  	{
    	printTree(head, 0);
  	}
  	if (verbose)
  	{
  		if (full)
  		{
  			treeSize = 767;
  		}
  		float bitPercent = (float)(trimmedCode->length) / (float)(fileLength * 8);
  		printf("Original %lu bits: ", 8 * fileLength);
  		printf("leaves %u (%u bytes) ", treeSize / 3 + 1, treeSize);
  		printf("encoding bits %u (%.4f%%).\n", trimmedCode->length, bitPercent * 100);
  	}
    if (oFlag)
    {
        fclose(output);
    }
    delVec(code);
    delVec(trimmedCode);
    fclose(input);
    return;
}
