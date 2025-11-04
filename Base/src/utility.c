#include "utility.h"

uint8_t utility_getFirstBitIndex(uint32_t mask)
{
	for(uint8_t indx = 0; indx < 32; indx++)
	{
		if (mask & (1 << indx))
			return indx;
	}
}
