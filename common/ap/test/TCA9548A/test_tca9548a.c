/*
 * test_tca9548a.c
 *
 *  Created on: 2017. 12. 21.
 *      Author: D.ggavy
 */


#include "test_def.h"

#include "hw.h"
#include "test_tca9548a.h"
#include "tca9548a.h"
#include "range_lux/range_lux.h"

#define NUM_CH   6


void testMuxMain0(void)
{
	bool ret = TRUE;

	tcs34725_t tcs34725[NUM_CH];
	float   source_lux[((NUM_CH-1)/3)+1];
	float   nature_lux[((NUM_CH-1)/3)+1];
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	uint16_t   lux_buf[((NUM_CH-1)/3)+1][3];
	uint32_t   t_micros;


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();
		//ret  = tcaSelect(i2c_ch, id, 8);

		for(ch = 0; ch < NUM_CH ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725Begin(&tcs34725[ch], i2c_ch, TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_16X);
			if (ret == false)
			{
				cmdifPrintf("fail : tca9548a num error\n");
				break;
			}
		}

		 /* Set a delay for the integration time */
		switch(tcs34725[0]._tcs34725IntegrationTime)
		{
		case TCS34725_INTEGRATIONTIME_2_4MS:
		  delay(3);
		  break;
		case TCS34725_INTEGRATIONTIME_24MS:
		  delay(24);
		  break;
		case TCS34725_INTEGRATIONTIME_50MS:
		  delay(50);//default 50
		  break;
		case TCS34725_INTEGRATIONTIME_101MS:
		  delay(101);
		  break;
		case TCS34725_INTEGRATIONTIME_154MS:
		  delay(154);
		  break;
		case TCS34725_INTEGRATIONTIME_700MS:
		  delay(700);
		  break;
		}



		for(ch = 0; ch < NUM_CH ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725GetRGBCnDelay(&tcs34725[ch]);
			lux_buf[(ch/3)][(ch%3)] = tcs34725CalculateLux(&tcs34725[ch]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		cmdifPrintf("Result");

		for(ch = 0; ch < (NUM_CH/3); ch++)
		{
			cmdifPrintf("%d, ", lux_buf[(ch/3)][(ch%3)]);
		}
		cmdifPrintf("\n");



	}
}

void testMuxMain1(void)
{
	bool ret = TRUE;

	tcs34725_t tcs34725[NUM_CH];
	float   source_lux[((NUM_CH-1)/3)+1];
	float   nature_lux[((NUM_CH-1)/3)+1];
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	uint16_t   lux_buf[((NUM_CH-1)/3)+1][3];
	uint32_t   t_micros;


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();
		//ret  = tcaSelect(i2c_ch, id, 8);

		for(ch = 0; ch < NUM_CH ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725Begin(&tcs34725[ch], i2c_ch, TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_16X);
			if (ret == false)
			{
				cmdifPrintf("fail : tca9548a num error\n");
				break;
			}
		}

		 /* Set a delay for the integration time */
		switch(tcs34725[0]._tcs34725IntegrationTime)
		{
		case TCS34725_INTEGRATIONTIME_2_4MS:
		  delay(3);
		  break;
		case TCS34725_INTEGRATIONTIME_24MS:
		  delay(24);
		  break;
		case TCS34725_INTEGRATIONTIME_50MS:
		  delay(50);//default 50
		  break;
		case TCS34725_INTEGRATIONTIME_101MS:
		  delay(101);
		  break;
		case TCS34725_INTEGRATIONTIME_154MS:
		  delay(154);
		  break;
		case TCS34725_INTEGRATIONTIME_700MS:
		  delay(700);
		  break;
		}



		for(ch = 0; ch < NUM_CH ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725GetRGBCnDelay(&tcs34725[ch]);
			lux_buf[(ch/3)][(ch%3)] = tcs34725CalculateNewLux(&tcs34725[ch]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		cmdifPrintf("Result");

		for(ch = 0; ch < (NUM_CH/3); ch++)
		{
			cmdifPrintf("%d, ", lux_buf[(ch/3)][(ch%3)]);
		}
		cmdifPrintf("\n");



	}
}




void testMuxMain2(void)
{
	bool ret = TRUE;

	tcs34725_t tcs34725[NUM_CH];
	float   source_lux[((NUM_CH-1)/3)+1];
	float   nature_lux[((NUM_CH-1)/3)+1];
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	uint16_t   lux_buf[((NUM_CH-1)/3)+1][3];
	uint32_t   t_micros;


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();
		//ret  = tcaSelect(i2c_ch, id, 8);

		for(ch = 0; ch < NUM_CH ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725Begin(&tcs34725[ch], i2c_ch, TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_16X);
			if (ret == false)
			{
				cmdifPrintf("fail : tca9548a num error\n");
				break;
			}
		}

		 /* Set a delay for the integration time */
		switch(tcs34725[0]._tcs34725IntegrationTime)
		{
		case TCS34725_INTEGRATIONTIME_2_4MS:
		  delay(3);
		  break;
		case TCS34725_INTEGRATIONTIME_24MS:
		  delay(24);
		  break;
		case TCS34725_INTEGRATIONTIME_50MS:
		  delay(50);//default 50
		  break;
		case TCS34725_INTEGRATIONTIME_101MS:
		  delay(101);
		  break;
		case TCS34725_INTEGRATIONTIME_154MS:
		  delay(154);
		  break;
		case TCS34725_INTEGRATIONTIME_700MS:
		  delay(700);
		  break;
		}



		for(ch = 0; ch < NUM_CH ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725GetRGBCnDelay(&tcs34725[ch]);
			lux_buf[(ch/3)][(ch%3)] = tcs34725CalculateLux(&tcs34725[ch]);
		}

		for(uint8_t lux_buf_index = 0; lux_buf_index< (NUM_CH/3); lux_buf_index++)
		{
			rangeLuxCalculate(&lux_buf[lux_buf_index], &source_lux[lux_buf_index], &nature_lux[lux_buf_index]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);


		for(ch = 0; ch < (NUM_CH/3); ch++)
		{
			cmdifPrintf("src : %04.04f, cons : %04.04f", source_lux[ch], nature_lux[ch]);
		}
		cmdifPrintf("\n");



	}
}




