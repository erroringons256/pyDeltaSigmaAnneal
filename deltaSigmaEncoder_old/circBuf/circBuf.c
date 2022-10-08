#include <stdlib.h>
#include "circBuf.h"
static size_t smallestPowerOf2GeqThan(size_t);

char circBuf_init(circBuf* self, size_t bufLength)
{
	self->mask = smallestPowerOf2GeqThan(bufLength) - 1;
	self->content = malloc((self->mask + 1) * sizeof(double));
	if (!self->content)
	{
		return 1;
	}
	self->offset = 0;
	return 0;
}

double circBuf_get(circBuf* self, size_t n)
{
	return self->content[(n + self->offset) & self->mask];
}

void circBuf_set(circBuf* self, size_t n, double val)
{
	self->content[(n + self->offset) & self->mask] = val;
}

void circBuf_roll(circBuf* self, size_t n)
{
	self->offset = (self->offset - n) & self->mask;
}

void circBuf_setContent(circBuf* self, double* content)
{
	memcpy(self->content, content, (self->mask + 1) * sizeof(double));
	self->offset = 0;
}

void circBuf_getContent(circBuf* self, double* content)
{
	memcpy(content, self->content + self->offset, (self->mask - self->offset + 1) * sizeof(double));
	memcpy(content + self->mask - self->offset + 1, self->content, self->offset * sizeof(double));
}

static size_t smallestPowerOf2GeqThan(size_t x)
{
	size_t y = 1;
	while (y < x && y != 0) // 0 means an overflow has occured
		y *= 2;
	return y;
}