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
#include "lkup_tbl/lkup_tbl.h"

#define MAX_CH_PER_MUX 6
#define NUM_MUX        6

#define NUM_SENSOR   (NUM_MUX*MAX_CH_PER_MUX)

#define ALL_CH   8



float   source_lux[((NUM_SENSOR-1)/3)+1];
float   nature_lux[((NUM_SENSOR-1)/3)+1];


uint16_t   lux_buf[((NUM_SENSOR-1)/3)+1][3];



void testMuxMain0(uint8_t gain)
{
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	bool ret = TRUE;
	tcs34725_t tcs34725;
	tcs34725_t tcs34725_list[NUM_SENSOR];

	uint32_t   t_micros;


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

		/*Write command to all channel*/
		ret  = tcaSelect(i2c_ch, id, ALL_CH);
		tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_154MS, gain);
		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			tcs34725_list[ch].ch = tcs34725.ch;
			tcs34725_list[ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[ch].init = tcs34725.init;
		}

	 /* Set a delay for the integration time */
		switch(tcs34725._tcs34725IntegrationTime)
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

		delay(5);

		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			if (ret == false)
			{
				cmdifPrintf("fail : tca9548a num error\n");
				break;
			}
			tcs34725GetRGBCnDelay(&tcs34725_list[ch]);
			lux_buf[(ch/3)][(ch%3)] = tcs34725CalculateLux(&tcs34725_list[ch]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		cmdifPrintf("Result : ");
		for(ch = 0; ch < NUM_SENSOR; ch++)
		{
			cmdifPrintf("%d, ", lux_buf[(ch/3)][(ch%3)]);
		}
		cmdifPrintf("\n");


		tcaDeSelect(i2c_ch, id);
	}
}


void testMuxMain1(uint8_t gain)
{
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	bool ret = TRUE;
	tcs34725_t tcs34725;
	tcs34725_t tcs34725_list[NUM_SENSOR];

	uint32_t   t_micros;


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

		/*Write command to all channel*/
		ret  = tcaSelect(i2c_ch, id, ALL_CH);
		tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_154MS, gain);
		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			tcs34725_list[ch].ch = tcs34725.ch;
			tcs34725_list[ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[ch].init = tcs34725.init;
		}

	 /* Set a delay for the integration time */
		switch(tcs34725._tcs34725IntegrationTime)
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

		delay(5);

		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			if (ret == false)
			{
				cmdifPrintf("fail : tca9548a num error\n");
				break;
			}
			tcs34725GetRGBCnDelay(&tcs34725_list[ch]);
			lux_buf[(ch/3)][(ch%3)] = tcs34725CalculateNewLux(&tcs34725_list[ch]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		cmdifPrintf("Result");
		for(ch = 0; ch < NUM_SENSOR; ch++)
		{
			cmdifPrintf("%d, ", lux_buf[(ch/3)][(ch%3)]);
		}
		cmdifPrintf("\n");


		tcaDeSelect(i2c_ch, id);
	}

}




void testMuxMain2(uint8_t gain)
{
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	bool ret = TRUE;
	tcs34725_t tcs34725;
	tcs34725_t tcs34725_list[NUM_SENSOR];

	uint32_t   t_micros;


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

		/*Write command to all channel*/

		ret  = tcaSelect(i2c_ch, id, ALL_CH);
		tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_154MS, gain);
		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			tcs34725_list[ch].ch = tcs34725.ch;
			tcs34725_list[ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[ch].init = tcs34725.init;
		}

	 /* Set a delay for the integration time */
		switch(tcs34725._tcs34725IntegrationTime)
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

		delay(5);

		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			if (ret == false)
			{
				cmdifPrintf("fail : tca9548a num error\n");
				break;
			}
			tcs34725GetRGBCnDelay(&tcs34725_list[ch]);
			lux_buf[(ch/3)][(ch%3)] = tcs34725CalculateLux(&tcs34725_list[ch]);
		}

		for(uint8_t lux_buf_index = 0; lux_buf_index< (NUM_SENSOR/3); lux_buf_index++)
		{
			rangeLuxCalculate(&lux_buf[lux_buf_index], &source_lux[lux_buf_index], &nature_lux[lux_buf_index]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		for(ch = 0; ch < (NUM_SENSOR/3); ch++)
		{
			cmdifPrintf("src : %04.04f, cons : %04.04f", source_lux[ch], nature_lux[ch]);
		}
		cmdifPrintf("\n");
		tcaDeSelect(i2c_ch, id);
	}



}

void testMuxMain3(uint8_t gain)
{
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	bool ret = TRUE;
	tcs34725_t tcs34725;
	tcs34725_t tcs34725_list[NUM_SENSOR];
	uint32_t   t_micros;


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

		/*Write command to all channel*/
		ret  = tcaSelect(i2c_ch, id, ALL_CH);
		tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_50MS, gain);
		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			tcs34725_list[ch].ch = tcs34725.ch;
			tcs34725_list[ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[ch].init = tcs34725.init;
		}

	 /* Set a delay for the integration time */
		switch(tcs34725._tcs34725IntegrationTime)
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

		delay(5);

		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			if (ret == false)
			{
				cmdifPrintf("fail : tca9548a num error\n");
				break;
			}
			tcs34725GetRGBCnDelay(&tcs34725_list[ch]);
			lux_buf[(ch/3)][(ch%3)] = tcs34725CalculateNewLux(&tcs34725_list[ch]);
		}

		for(uint8_t lux_buf_index = 0; lux_buf_index < (NUM_SENSOR/3); lux_buf_index++)
		{
			rangeLuxCalculate(&lux_buf[lux_buf_index], &source_lux[lux_buf_index], &nature_lux[lux_buf_index]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		for(ch = 0; ch < (NUM_SENSOR/3); ch++)
		{
			cmdifPrintf("src : %04.04f, cons : %04.04f", source_lux[ch], nature_lux[ch]);
		}
		cmdifPrintf("\n");

		tcaDeSelect(i2c_ch, id);
	}



}

void testMultiMuxMain(uint8_t gain)
{
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	bool ret = TRUE;
	tcs34725_t tcs34725;
	tcs34725_t tcs34725_list[NUM_SENSOR];

	uint32_t   t_micros;


	for(id = 0; id < NUM_MUX; id++)
	{
		tcaDeSelect(i2c_ch, id);
	}

	/*Write command to all id + channel*/
	for(id = 0; id < NUM_MUX; id++)
	{
		for(ch = 0; ch < MAX_CH_PER_MUX ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_154MS, gain);

			tcs34725_list[id*MAX_CH_PER_MUX+ch].ch = tcs34725.ch;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[id*MAX_CH_PER_MUX+ch].init = tcs34725.init;
		}
		tcaDeSelect(i2c_ch, id);
	}

	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

	 /* Set a delay for the integration time */
		tcs34725WaitForIntegration(&tcs34725);
		delay(5);

		id = 0;
		for(ch = 0; ch < NUM_SENSOR ; ch++)
		{
			if(0==(ch%MAX_CH_PER_MUX))
			{
				tcaDeSelect(i2c_ch, id);
				if(0!=ch)
				{
					id++;
				}

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



		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		cmdifPrintf("Result");
		for(ch = 0; ch < NUM_SENSOR; ch++)
		{
			cmdifPrintf("%d, ", lux_buf[(ch/3)][(ch%3)]);
		}
		cmdifPrintf("\n");


		tcaDeSelect(i2c_ch, id);

	}

}

void testAdcI2CMuxMain(uint8_t gain)
{
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	bool ret = TRUE;
	tcs34725_t tcs34725;
	tcs34725_t tcs34725_list[NUM_SENSOR];

	uint32_t   t_micros;


	for(id = 0; id < NUM_MUX; id++)
	{
		muxSetIdnCh(0,id);
		tcaDeSelect(i2c_ch, id);
	}

	/*Write command to all id + channel*/
	for(id = 0; id < NUM_MUX; id++)
	{
		muxSetIdnCh(0,id);
		ret  = tcaSelect(i2c_ch, id, ALL_CH);
		tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_50MS, gain);
		for(ch = 0; ch < MAX_CH_PER_MUX ; ch++)
		{


			tcs34725_list[id*MAX_CH_PER_MUX+ch].ch = tcs34725.ch;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[id*MAX_CH_PER_MUX+ch].init = tcs34725.init;
		}
		tcaDeSelect(i2c_ch, id);
	}

	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

	 /* Set a delay for the integration time */
		tcs34725WaitForIntegration(&tcs34725);
		delay(5);

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

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		cmdifPrintf("Result");
		for(ch = 0; ch < NUM_SENSOR; ch++)
		{
			cmdifPrintf("%d, ", lux_buf[(ch/3)][(ch%3)]);
		}
		cmdifPrintf("\n");

	}

}

void testRangeAdcI2CMuxMain(uint8_t gain)
{
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	bool ret = TRUE;
	uint32_t   t_micros;

	tcs34725_t tcs34725;
	tcs34725_t tcs34725_list[NUM_SENSOR];

	for(id = 0; id < NUM_MUX; id++)
	{
		muxSetIdnCh(0,id);
		tcaDeSelect(i2c_ch, id);
	}

	///////////////////////////////////////
	/*Write command to all id + channel*/
	for(id = 0; id < NUM_MUX; id++)
	{
		muxSetIdnCh(0,id);
		for(ch = 0; ch < MAX_CH_PER_MUX ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_50MS, gain);

			tcs34725_list[id*MAX_CH_PER_MUX+ch].ch = tcs34725.ch;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[id*MAX_CH_PER_MUX+ch].init = tcs34725.init;
		}
		tcaDeSelect(i2c_ch, id);
	}
  ///////////////////////////////////////


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

		///////////////////////////////////////
	 /* Set a delay for the integration time */
		tcs34725WaitForIntegration(&tcs34725);
		delay(5);
		///////////////////////////////////////

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

		for(uint8_t lux_buf_index = 0; lux_buf_index < (NUM_SENSOR/3); lux_buf_index++)
		{
			rangeLuxCalculate(&lux_buf[lux_buf_index], &source_lux[lux_buf_index], &nature_lux[lux_buf_index]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		for(ch = 0; ch < (NUM_SENSOR/3); ch++)
		{
			cmdifPrintf("src : %04.04f, cons : %04.04f", source_lux[ch], nature_lux[ch]);
		}
		cmdifPrintf("\n");

	}

}

void testAdcI2cMuxConvDist(uint8_t gain)
{
	uint8_t    i2c_ch = 0;
	uint8_t    id     = 0;
	uint8_t    ch     = 0;
	bool ret = TRUE;
	tcs34725_t tcs34725;
	tcs34725_t tcs34725_list[NUM_SENSOR];

	uint32_t   t_micros;


	for(id = 0; id < NUM_MUX; id++)
	{
		muxSetIdnCh(0,id);
		tcaDeSelect(i2c_ch, id);
	}

	///////////////////////////////////////
	/*Write command to all id + channel*/
	for(id = 0; id < NUM_MUX; id++)
	{
		muxSetIdnCh(0,id);
		for(ch = 0; ch < MAX_CH_PER_MUX ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_50MS, gain);

			tcs34725_list[id*MAX_CH_PER_MUX+ch].ch = tcs34725.ch;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725IntegrationTime = tcs34725._tcs34725IntegrationTime;
			tcs34725_list[id*MAX_CH_PER_MUX+ch]._tcs34725Gain = tcs34725._tcs34725Gain;
			tcs34725_list[id*MAX_CH_PER_MUX+ch].init = tcs34725.init;
		}
		tcaDeSelect(i2c_ch, id);
	}
  ///////////////////////////////////////


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

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
		/*LeviOsa processing : convert to distance*/
		for(uint8_t lux_buf_index = 0; lux_buf_index < (NUM_SENSOR/3); lux_buf_index++)
		{
			rangeLuxCalculate(&lux_buf[lux_buf_index], &source_lux[lux_buf_index], &nature_lux[lux_buf_index]);
		}

		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  ", t_micros);

		for(ch = 0; ch < (NUM_SENSOR/3); ch++)
		{
			cmdifPrintf("src : %04.04f, f", source_lux[ch]);
			cmdifPrintf(" distance : %d mm/ ", lkup_tblGetDist(source_lux[ch]));
		}
		///////////////////////////////////////
		cmdifPrintf("\n");

	}

}


