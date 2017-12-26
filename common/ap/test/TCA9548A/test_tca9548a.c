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

#define NUM_CH   6


void testMuxMain(void)
{
	bool ret = TRUE;

	tcs34725_t tcs34725;
	uint8_t    i2c_ch = 0;
    uint8_t    id     = 1;
    uint8_t    ch     = 0;
    uint16_t   lux_buf[NUM_CH];
    uint32_t   t_micros;


	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();
		ret  = tcaSelect(i2c_ch, id, 8);
		tcs34725Begin(&tcs34725, i2c_ch, TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_4X);

		for(ch = 0; ch < NUM_CH ; ch++)
		{
			ret  = tcaSelect(i2c_ch, id, ch);
			//delayMicros(5);
			if (ret == false)
			{
				cmdifPrintf("fail : tca9548a num error\n");
				break;
			}

			tcs34725GetRGBC(&tcs34725);
			lux_buf[ch] = tcs34725CalculateLux(&tcs34725);

		}

		t_micros = micros() - t_micros;

		cmdifPrintf("Time : %d  ", t_micros);
		cmdifPrintf("Result : ");

		for(ch = 0; ch < NUM_CH; ch++)
		{
			cmdifPrintf("%d, ", lux_buf[ch]);
			if(ch == (NUM_CH-1)) cmdifPrintf("\n");

		}


	}
}




