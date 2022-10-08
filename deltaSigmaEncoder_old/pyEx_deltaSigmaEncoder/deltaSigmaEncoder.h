#ifndef DELTASIGMAENCODER_H
#define DELTASIGMAENCODER_H
#include "circBuf.h"

typedef struct struct_encoder
{
	double* xFilter;
	double* yFilter;
	circBuf xState;
	circBuf yState;
	unsigned int fSize;
} encoder;

char encoder_init(encoder*, unsigned int, unsigned int, double*, double*, circBuf*, circBuf*);
void encoder_encode(encoder*, unsigned int, double*, double*);


#endif