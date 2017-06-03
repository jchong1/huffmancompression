# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# include "bv.h"
# include "code.h"

bitV *newVec(uint32_t length)
{
	struct bitV *v;
	v = (bitV *)malloc(sizeof(bitV));
	v->length = length;
	v->vector = malloc(sizeof(uint8_t) * length/8+1);
	v->position = 0;
	return v;
}

void delVec(bitV * v)
{
	free(v->vector);
	free(v);
	v->vector = NULL;
	v = NULL;
	return;
}

void setBit(bitV * v, uint32_t index)
{
	v->vector[index>>3] |= (01 << (index&07));
	return;
}

void clrBit(bitV * v, uint32_t index)
{
	v->vector[index>>3] &= ~(01 << (index&07));
	return;
}

void oneVec(bitV * v)
{
	for(uint32_t i=0; i<=v->length; i++)
	{
		v->vector[i>>3] |= (01 << (i&07));
	}
	return;
}

uint8_t valBit(bitV * v, uint32_t index)
{
	return (v->vector[index >> 3] >> (index & 07)) & 01;
}

uint32_t lenVec(bitV * v)
{
	return v->length;
}

void appendVec(bitV *v, code t)
{
	// Allocate more memory if there isn't enough space
	if (v->position == (v->length - 1))
	{
		v->length += t.l;
		v->vector = (uint8_t *) realloc(v->vector, v->length / 8 + 1);
	}

	// Loop through the bits of the code
	for (uint32_t i = 0; i < t.l; i++)
	{
		// Check the value of bit in code
		if ((t.bits[i >> 3] >> (i & 07)) & 01)
		{
			// Append the bit
			setBit(v, ++(v->position));
		}

		else
		{
			// Append the bit
			clrBit(v, ++(v->position));
		}
	}
	return;
}

// int main(void)
// {
// 	bitV *v = newVec(sizeof(uint8_t));
// 	code c1 = newCode();
// 	pushCode(&c1, 1);
// 	pushCode(&c1, 1);
// 	pushCode(&c1, 1);
// 	pushCode(&c1, 1);
// 	pushCode(&c1, 1);
// 	appendVec(v, c1);
// 	printf("Bitvector: ");
// 	for (uint32_t i = 0; i < v->length; i++)
// 	{
// 		printf("%u ", valBit(v, i));
// 	}
// 	printf("\nCode: ");
// 	for (uint32_t i = 0; i < c1.l; i++)
// 	{
// 		printf("%d ", c1.bits[i >> 3] >> (i & 07) & 01);
// 	}
// }

