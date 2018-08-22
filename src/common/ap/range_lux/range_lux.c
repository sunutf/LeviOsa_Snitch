/*
 * range_lux.c
 *
 *  Created on: 2017. 12. 27.
 *      Author: D.ggavy
 */


#include "test_def.h"

#include "hw.h"
#include "math.h"
#include "range_lux.h"


void rangeLuxCalculate(uint16_t *buf, float *source, float *nature)
{
	int16_t diff_luxA;
	int16_t diff_luxB;
	int16_t diff_luxC;
	float source_lux;
	float nature_lux;

	diff_luxA = buf[0]-buf[1];
	diff_luxB = buf[1]-buf[2];
	diff_luxC = buf[2]-buf[0];

	source_lux =   (float)(diff_luxC * diff_luxC);
	source_lux +=  (float)((diff_luxA-diff_luxB)*(diff_luxA-diff_luxB));
	source_lux =   sqrtf(source_lux);

	nature_lux = ((float)buf[0]+(float)buf[2]-source_lux)/2;

	*source = source_lux;
	*nature = nature_lux;

}
