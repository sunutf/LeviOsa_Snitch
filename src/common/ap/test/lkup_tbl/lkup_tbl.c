/*
 * lkup.tbl.c
 *
 *  Created on: 2018. 3. 5.
 *      Author: D.ggavy
 */

#include "test_def.h"
#include "hw.h"
#include "lkup_tbl.h"

#define NUM_OF_STEP (((END_POINT-INIT_POINT)/STEP_SIZE)+1)
#define NUM_OF_STEP_FOR_INTERPOLAR 20 // resoluton = STEP_SIZE /NUM_OF_STEP_FOR_INTERPOLAR
#define STEP_SIZE   50 //mm
#define INIT_POINT  200 //mm
#define END_POINT   1300 //mm

#define RESOLUTION ((float)STEP_SIZE/(float)NUM_OF_STEP_FOR_INTERPOLAR) //mm

float lkup_tbl_t[NUM_OF_STEP]=
		{
				2538.14,
				1507,
				1019,
				727.69,
				553.17,
				415.4275,
				337.0015,
				276.58,
				221.7115,
				190.683,
				162.04,
				140.4635,
				118.8781,
				104.3456,
				89.0505,
				80.05,
				73.7564,
				66.7083,
				60.4152,
				53.3667,
				50.2195,
				47.0744,
				43.1741,
		};


uint32_t lkup_tblSearch(float lux_value)
{
	uint32_t i = 0;

	if(lux_value>=lkup_tbl_t[(NUM_OF_STEP-1)])
	{
		while(lux_value < lkup_tbl_t[i])
		{
			i++;
		}
		return i;
	}
	else if(lux_value>=0) return (NUM_OF_STEP-1);
	else return -1;
}


uint8_t lkup_tblInterpolation(float lux_value, uint32_t order_of_step)
{
	float high;
	float low;
	float range;
	float step_size;
	float huddle;
	uint8_t internal_step = 0;

	uint32_t order = order_of_step;

	if(order)
	{
		high 	 = lkup_tbl_t[order-1];
		low		 = lkup_tbl_t[order];

		range = high - low;
		step_size = range/NUM_OF_STEP_FOR_INTERPOLAR;

		huddle = low;
		while(lux_value > huddle)
		{
			huddle += step_size;
			internal_step++;
		}
		return internal_step;
	}
	else return 0;
}


uint32_t lkup_tblGetDist(const float lux_value)
{
	uint32_t order_of_step;
	uint32_t internal_step;
	uint32_t distance;

	order_of_step = lkup_tblSearch(lux_value); //Big Step
	internal_step = lkup_tblInterpolation(lux_value, order_of_step); //Small Step

	distance = INIT_POINT + (order_of_step*STEP_SIZE) - (uint32_t)(internal_step*RESOLUTION);//Big Step(cm) - Small Step(mm)
	return	distance;
}

