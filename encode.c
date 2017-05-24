# include <stdio.h>

int main()
{
	printf("encode the darrell long dong");
	return 0;
}

// Create a histogram of char frequencies in file
uint32_t *makeHistogram(char *file)
{
	FILE *fp = fopen(file, "r");
	uint8_t c = 0;

	uint32_t *hist = calloc(256, sizeof(uint32_t));
	// Increment first and last to ensure at least 2 elements
	hist[0]++;
	hist[255]++;

	if (fp == NULL)
	{
		perror("Couldn't open file");
		return -1;
	}
	while (feof(fp) != 0)
	{
		fread(fp, &c, 1);
		hist[c]++;
	}
	fclose(fp);
	return hist;
}
