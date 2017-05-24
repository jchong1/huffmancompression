# include <stdio.h>

int main()
{
	printf("encode the darrell long dong");
	return 0;
}

uint32_t *makeHistogram(char *file)
{
	FILE *fp = fopen(file, "r");
	char c;
	uint32_t *hist = calloc(256, sizeof(uint32_t));
	hist[0]++;
	hist[255]++;

	if (fp == NULL)
	{
		perror("Couldn't open file");
		return -1;
	}
	while (!feof(fp))
	{
		c = fgetc(fp);

	}
}
