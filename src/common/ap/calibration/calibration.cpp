/*
 * calibration.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: D.ggavy
 */

#include "ap.h"
#include "hw.h"
#include "leviosa_board.h"
#include "tca9548a.h"

//processing step//
//1. cmdif -> leviosa cali start
//2. [get] init_packet
//3. [sorting] -> init_ang, end_ang, iter_cnt, resolution
//4. [get] tcs34725 raw data -> sum (iter_cnt)
//5. [store] aver_raw_data -> cali_lookup_tbl
//6. [send] done_packet

//repeat//
//7. [get] ack_packet
//3 ~ 6 again.

//cali_lookup_tbl

//tbl[12][4]   [surface][sensor], each sensor has own eeprom address
//- update(address, value)
// -- eeprom
//- get(address)
// -- eeprom
#define CALI_SERIAL 2
#define NUM_SENSOR_IN_SURFACE 3

uint32_t init_angle  = 0;
uint32_t final_angle = 0;
uint32_t resolution  = 0;
uint8_t	 iter_cnt		 = 0;

uint32_t total_cnt	 = 0;
uint32_t curr_cnt		 = 0;
uint32_t curr_angle	 = 0;
uint32_t cnt				 = 0;

uint8_t i2c_ch = 0;

uint16_t cali_tbl[12][4][1800] = 0;
char ack_packet[4] = {'#', 0, 0,'@'};

char command_packet[7];
tcs34725_t tcs34725_list[NUM_SENSOR_IN_SURFACE];

bool ret					= true;
bool cali_start 	= false;
bool parse_start	= false;

void calibrationParseInitCommand(char* buf)
{
  init_angle 	= (buf[0]) << 8 + buf[1];
  final_angle = (buf[2]) << 8 + buf[3];
  resolution	= (buf[4]) << 8 + buf[5];
  iter_cnt		= buf[6];
}

uint32_t calibrationParseCommand(char* buf)
{
  uint32_t angle 	= (buf[0]) << 8 + buf[1];
  return angle;
}

uint16_t calibrationLuxSingleGet(uint8_t id, uint8_t ch_in_id, uint32_t curr_angle)
{
	///////////////////////////////////////
		/* Set a delay for the integration time */
		tcs34725WaitForIntegration(&tcs34725);
		delay(5);
		///////////////////////////////////////

		muxSetIdnCh(0,id);
		ret  = tcaSelect(i2c_ch, id, ch_in_id);
		if (ret == false)
		{
			cmdifPrintf("%d ", ch_in_id);
			cmdifPrintf("fail : tca9548a num error\n");
			break;
		}

		tcs34725GetRGBCnDelay(&tcs34725_list[ch_in_id]);
		return tcs34725CalculateNewLux(&tcs34725_list[ch_in_id]);

}

void calibrationLuxStore(uint8_t id, uint32_t curr_angle, uint8_t iter_cnt)
{
	uint32_t sum[NUM_SENSOR_IN_SURFACE] = 0;
	for(uint8_t i = 0; i<iter_cnt; i++)
	{
		for(uint8_t ch_in_id =0; ch_in_id<NUM_SENSOR_IN_SURFACE; ch_in_id++)
		{
			sum[ch_in_id] += calibrationLuxSingleGet(id, ch_in_id, curr_angle);
		}
	}

	for(uint8_t ch_in_id =0; ch_in_id<NUM_SENSOR_IN_SURFACE; ch_in_id++)
	{
		cali_tbl[id][ch_in_id][curr_angle] = sum[ch_in_id]/iter_cnt;
	}



	tcaDeSelect(i2c_ch, id);
}

void calibrationInit(void)
{
	uartOpen(CALI_SERIAL, 9600);
}

 void calibrationMain(uint8_t id)
{
	if (uartAvailable(CALI_SERIAL) > 0)
	{
		char c = uartRead(CALI_SERIAL);

		if(!cali_start)
		{
			if(c == '@')
			{
				if(cnt == 7)
				{
					parse_start = false;
					cali_start	= true;

					calibrationParseInitCommand(command_packet);
				}
			}

			if(parse_start)
			{
				command_packet[cnt] = c;
				cnt++;
			}
			if(c == '#') parse_start = true;
		}

		else
		{
			if(c == '@')
			{
				if(cnt == 2)
				{
					parse_start = false;
					cali_start	= true;

					curr_angle = calibrationParseCommand(command_packet);

					calibrationLuxStore(id, curr_angle, iter_cnt);

					ack_packet[1] = (curr_angle >> 8 | 0);
					ack_packet[2] = (curr_angle | 0);
					ret = uartWrite(CALI_SERIAL, (uint8_t *)ack_packet, 4);


				}
			}

			if(parse_start)
			{
				command_packet[cnt] = c;
				cnt++;
			}
			if(c == '#') parse_start = true;
		}
	}

	 //get
	 //sorting -> value

	 //send - done
	 //read - next
	 //get - lux
	 //store - avr_lux/ eeprom
	 //send - done
}

