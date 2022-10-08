#include <stdio.h>
#include <stdlib.h>
#include "circBuf.h"
#include "deltaSigmaEncoder.h"

char encoder_init(encoder* self, size_t xFilterLength, size_t yFilterLength, double* xFilter, double* yFilter)
{
	self->xFilterLength = xFilterLength;
	self->yFilterLength = yFilterLength;
	self->xFilter = xFilter;
	self->yFilter = yFilter;
	if (circBuf_init(&self->xState, xFilterLength) || circBuf_init(&self->yState, yFilterLength))
	{
		return 1;
	}
	return 0;
}

void encoder_encode(encoder* self, unsigned int n, double* inSignal, double* outSignal)
{
}

static void cDemoCircBuf(unsigned char maskLen)
{
	circBuf buf;
	circBuf_init(&buf, maskLen);
	circBuf_set(&buf, 0, 1.0);
	for (unsigned int i = 0; i < 16; i++)
	{
		printf("[");
		for (unsigned int j = 0; j < 8; j++)
		{
			printf(" %lf", circBuf_get(&buf, j));
		}
		printf(" ]\n");
		circBuf_roll(&buf, 1);
	}
}