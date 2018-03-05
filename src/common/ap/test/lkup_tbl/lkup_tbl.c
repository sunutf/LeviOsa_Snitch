/*
 * lkup.tbl.c
 *
 *  Created on: 2018. 3. 5.
 *      Author: D.ggavy
 */

#include "test_def.h"
#include "hw.h"
#include "lkup_tbl.h"

#define NUM_OF_STEP 60
#define NUM_OF_STEP_FOR_INTERPOLAR 10 // resoluton = STEP_SIZE /NUM_OF_STEP_FOR_INTERPOLAR
#define STEP_SIZE   5 //cm

#define RESOLUTION (STEP_SIZE*10/NUM_OF_STEP_FOR_INTERPOLAR) //mm

float lkup_tbl_t[NUM_OF_STEP]=
		{
				8000,
				6000,
				2000,
				500,
				300,
				200,
				54,
				53,
				52,
				51,
				50,
				49,
				48,
				47,
				46,
				45,
				44,
				43,
				42,
				41,
				40,
				39,
				38,
				37,
				36,
				35,
				34,
				33,
				32,
				31,
				30,
				29,
				28,
				27,
				26,
				25,
				24,
				23,
				22,
				21,
				20,
				19,
				18,
				17,
				16,
				15,
				14,
				13,
				12,
				11,
				10,
				9,
				8,
				7,
				6,
				5,
				4,
				3,
				2,
				1
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

	distance = (order_of_step*STEP_SIZE)*10 - internal_step*RESOLUTION;//Big Step(cm) - Small Step(mm)
	return	distance;
}

