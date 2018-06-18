/*
 * leviosa_board.c
 *
 *  Created on: 2018. 3. 8.
 *      Author: D.ggavy
 */

#include "test_def.h"

#include "hw.h"
#include "leviosa_board.h"
#include "matrix.h"
#include "tca9548a.h"
#include "range_lux/range_lux.h"
#include "lkup_tbl/lkup_tbl.h"



#ifdef _USE_HW_CMDIF_LEVIOSA
void leviosaCmdifInit(void);
int  leviosaCmdif(int argc, char **argv);
#endif

#define MAX_CH_PER_MUX 6
#define NUM_MUX        6
#define NUM_SENSOR   (NUM_MUX*MAX_CH_PER_MUX)

#define ALL_CH   8

float   	 source_lux[((NUM_SENSOR-1)/3)+1];
float  		 nature_lux[((NUM_SENSOR-1)/3)+1];
uint32_t   distance_lux[((NUM_SENSOR-1)/3)+1];
uint16_t   lux_buf[((NUM_SENSOR-1)/3)+1][3];

tcs34725_t tcs34725;
tcs34725_t tcs34725_list[NUM_SENSOR];

static bool ret = TRUE;
static uint8_t    i2c_ch = 0;
static uint8_t    id     = 0;
static uint8_t    ch     = 0;

void leviosa_boardInit(void)
{
	#ifdef _USE_HW_CMDIF_LEVIOSA
		leviosaCmdifInit();
	#endif
}

void leviosa_boardReady(void)
{
	for(id = 0; id < NUM_MUX; id++)
	{
		muxSetIdnCh(0,id);
		tcaDeSelect(i2c_ch, id);
	}
}

void leviosa_boardSetCmd(void)
{
	///////////////////////////////////////
	/*Write command to all id + channel*/
	for(id = 0; id < NUM_MUX; id++)
	{
		muxSetIdnCh(0,id);
		for(ch = 0; ch < MAX_CH_PER_MUX ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_50MS, 2);

			tcs34725_list[id*MAX_CH_PER_MUX+ch].ch = tcs34725.ch;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[id*MAX_CH_PER_MUX+ch].init = tcs34725.init;
		}
		tcaDeSelect(i2c_ch, id);
	}
}

void leviosa_boardGetCmd(void)
{
	///////////////////////////////////////
	/* Set a delay for the integration time */
	tcs34725WaitForIntegration(&tcs34725);
	delay(5);
	///////////////////////////////////////


	///////////////////////////////////////
	/* READ*/
	id = 0;
	for(ch = 0; ch < NUM_SENSOR ; ch++)
	{
		if(0==(ch%MAX_CH_PER_MUX))
		{
			tcaDeSelect(i2c_ch, id);
			if(0!=ch)			id++;
			muxSetIdnCh(0,id);
			tcaDeSelect(i2c_ch, id);
		}

		ret  = tcaSelect(i2c_ch, id, (ch%MAX_CH_PER_MUX));
		if (ret == false)
		{
			cmdifPrintf("%d ", ch);
			cmdifPrintf("fail : tca9548a num error\n");
			break;
		}
		tcs34725GetRGBCnDelay(&tcs34725_list[ch]);
		lux_buf[(ch/3)][(ch%3)] = tcs34725CalculateNewLux(&tcs34725_list[ch]);
	}
	///////////////////////////////////////

	///////////////////////////////////////
}

void leviosa_boardCalcSource(void)
{
	/*LeviOsa processing : convert to distance*/
	for(uint8_t lux_buf_index = 0; lux_buf_index < (NUM_SENSOR/3); lux_buf_index++)
	{
		rangeLuxCalculate(&lux_buf[lux_buf_index], &source_lux[lux_buf_index], &nature_lux[lux_buf_index]);
	}
}

float* leviosa_boardGetLuxBuf(uint8_t output)
{
	if(0 == output)		return source_lux;
	else 						  return nature_lux;
}

void leviosa_boardConvDistance(void)
{
	uint8_t i;

	for(i=0; i<((NUM_SENSOR-1)/3)+1;i++)
	{
		distance_lux[i] = lkup_tblGetDist(source_lux[i]);
	}
}

void leviosa_boardCalcCoord(void)
{
	float largest_value[3];
	uint8_t largest_index[3];

	// DR: Below is horribly ugly.
	//     Is there any constraint because of embedded system?
	largest_value[0] = largest_value[1] = largest_value[2] = 0;
	for(uint8_t i = 0; i < 3; i++)
	{
		float max = 0;
		uint8_t index = 0;
		for(ch = 0; ch < (NUM_SENSOR/3); ch++)
		{
			float cur_source = source_lux[ch];
			if(max < cur_source && cur_source != largest_value[0] && cur_source != largest_value[1] && cur_source != largest_value[2])
			{
				max = cur_source;
				index = ch;
			}
		}
		largest_value[i] = max;
		largest_index[i] = index;
#if 1
		cmdifPrintf("%d: %f %d\n", i, largest_value[i], largest_index[i]);
#endif
	}

	float mat_A[3][3];
	float vec_B[3];
	for (uint8_t i = 0; i < 3; i++){
		mat_A[0][i] = ETA[largest_index[0]][i];
		mat_A[1][i] = ETA[largest_index[1]][i];
		mat_A[2][i] = ETA[largest_index[2]][i];
	}

	vec_B[0] = norm(ETA[largest_index[0]]) * distance_lux[largest_index[0]] + innerProduct(ETA[largest_index[0]], S[largest_index[0]]);
	vec_B[1] = norm(ETA[largest_index[1]]) * distance_lux[largest_index[1]] + innerProduct(ETA[largest_index[1]], S[largest_index[1]]);
	vec_B[2] = norm(ETA[largest_index[2]]) * distance_lux[largest_index[2]] + innerProduct(ETA[largest_index[2]], S[largest_index[2]]);

	float res[3];
	float inv_mat_A[3][3];
	matrixInverse(mat_A, &inv_mat_A);
	matrixMul(inv_mat_A, vec_B, &res);
}

uint32_t* leviosa_boardGetDistance(void)
{
	return distance_lux;
}

void leviosa_boardLuxTest(uint8_t output)
{
	uint32_t   t_micros;
	uint32_t*   output_lux;

	leviosa_boardReady();
	leviosa_boardSetCmd();

	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

		leviosa_boardGetCmd();
		leviosa_boardCalcSource();
		leviosa_boardConvDistance();
		leviosa_boardCalcCoord();

		output_lux = leviosa_boardGetDistance();
		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		if(output == 1)
		{
			for(ch = 0; ch < (NUM_SENSOR/3); ch++)
			{
				cmdifPrintf("src : %04.04f, ", source_lux[ch]);
			}
		}
		else if(output == 2)
		{
			for(ch = 0; ch < (NUM_SENSOR/3); ch++)
			{
				cmdifPrintf("distance : %d mm/ ", output_lux[ch]);
			}
		}
		else if(output == 3)
		{
			for(ch = 0; ch < (NUM_SENSOR/3); ch++)
			{
				cmdifPrintf("src : %04.04f, ", source_lux[ch]);
			}
		}
		///////////////////////////////////////
		cmdifPrintf("\n");

	}

}

#ifdef _USE_HW_CMDIF_LEVIOSA
void leviosaCmdifInit(void)
{
  cmdifAdd("leviosa", leviosaCmdif);
}

int leviosaCmdif(int argc, char **argv)
{
  bool ret = true;

  if(argc == 2 && strcmp("source", argv[1]) == 0)
  {
  	leviosa_boardLuxTest(1);
  }
  else if(argc == 2 && strcmp("distance", argv[1]) == 0)
  {
  	leviosa_boardLuxTest(2);
  }
  else if(argc == 2 && strcmp("ap", argv[1]) == 0)
  {
  	leviosa_boardLuxTest(2);
  } else if(argc == 2 && strcmp("coord", argv[1]) == 0)
  {
	leviosa_boardLuxTest(3);
  }
  else
  {
  	ret = false;
  }

  if (ret == false)
  {
    cmdifPrintf( "wrong command\n choose : leviosa [source/distance/ap]");
  }

  return 0;
}
#endif
