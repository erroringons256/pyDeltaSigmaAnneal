#ifndef DELTASIGMAENCODER_H
#define DELTASIGMAENCODER_H
#include "circBuf.h"

typedef struct struct_filter
{
	double* xFilter;
	double* yFilter;
	circBuf* xState;
	circBuf* yState;
} filter;

typedef struct struct_stream
{
	filter* filterList;
	size_t filterNum;
} stream;

#endif