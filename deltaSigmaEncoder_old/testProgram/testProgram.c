#include <stdio.h>
#include "circBuf.h"
#include "iirFilter.h"

int main()
{
	circBuf someBuffer;
	if (circBuf_init(&someBuffer, 8))
		return 1;
	double newContent[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
	return 0;
}