# include <stdlib.h>
# include <math.h>
# include "bv.h"

bitV *newVec(uint32_t length)
{
	struct bitV *v;
	v = (bitV *)malloc(sizeof(bitV));
	v->length = length;
	v->vector = malloc(sizeof(uint8_t) * length/8+1);
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
	return (v->vector[index>>3] >> (index&07)) & 01;
}

uint32_t lenVec(bitV * v)
{
	return v->length;
}
