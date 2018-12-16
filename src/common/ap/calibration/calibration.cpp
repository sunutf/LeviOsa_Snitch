/*
 * calibration.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: D.ggavy
 */

#include "ap.h"
#include "hw.h"
#include "leviosa_board\leviosa_board.h"
#include "module\tca9548a.h"

//processing step//
//1. cmdif -> leviosa cali start
//2. [get] init_packet
//3. [sorting] -> init_ang, end_ang, iter_rx_cnt, resolution
//4. [get] tcs34725 raw data -> sum (iter_rx_cnt)
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


//0~180


uint32_t init_angle  = 0;
uint32_t final_angle = 0;
uint32_t resolution  = 0;
uint8_t	 iter_rx_cnt = 0;

uint32_t step  = 0;

uint32_t total_rx_cnt= 0;
uint32_t curr_rx_cnt = 0;
uint32_t curr_angle	 = 0;
uint32_t rx_cnt			 = 0;

uint8_t i2c_ch = 0;

uint16_t cali_tbl[4][1800] = {0};
char ack_packet[4] = {'#', 0, 0, '@'};

char command_packet[7];
tcs34725_t tcs34725;
tcs34725_t tcs34725_list[NUM_SENSOR_IN_SURFACE];

bool ret					= true;
bool cali_start 	= false;
bool parse_start	= false;

void calibrationParseInitCommand(char* buf)
{
  init_angle 	= ((buf[0]) << 8) | buf[1];
  final_angle 	= ((buf[2]) << 8) | buf[3];
  resolution	= (buf[4]) << 8 | buf[5];
  iter_rx_cnt	= buf[6];

  step = (final_angle - init_angle)/resolution;
}

uint32_t calibrationParseCommand(char* buf)
{
  uint32_t angle = ((buf[0]) << 8) | buf[1];
  return angle;
}

uint16_t calibrationLuxSingleGet(uint8_t id, uint8_t ch_in_id, uint32_t curr_angle)
{
	/////////////////////////////////////
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
	}

	tcs34725GetRGBCnDelay(&tcs34725_list[ch_in_id]);
	return tcs34725CalculateNewLux(&tcs34725_list[ch_in_id]);

}

void calibrationLuxStore(uint8_t id, uint32_t curr_angle, uint8_t iter_rx_cnt)
{
	uint32_t sum[NUM_SENSOR_IN_SURFACE] = {0};

	for(uint8_t i = 0; i<iter_rx_cnt; i++)
	{
		for(uint8_t ch_in_id =0; ch_in_id<NUM_SENSOR_IN_SURFACE; ch_in_id++)
		{
			delay(10);
			sum[ch_in_id] += calibrationLuxSingleGet(id, ch_in_id, curr_angle);
		}
	}

	//average
	for(uint8_t ch_in_id =0; ch_in_id<NUM_SENSOR_IN_SURFACE; ch_in_id++)
	{
		cmdifPrintf("\n id : %d done", ch_in_id);

		cali_tbl[ch_in_id][curr_angle] = sum[ch_in_id]/iter_rx_cnt;
	}

	tcaDeSelect(i2c_ch, id);
}

uint16_t calibrationLuxRead(uint8_t ch_in_id, uint32_t curr_angle)
{
	return cali_tbl[ch_in_id][curr_angle];
}

uint16_t calibrationReadEEPROM(uint8_t id, uint8_t ch_in_id)
{
	uint32_t eeprom_index;

	uint8_t low_data;
	uint8_t high_data;

	eeprom_index = (id*NUM_SENSOR_IN_SURFACE + ch_in_id)*2;

	high_data = eepromReadByte(eeprom_index);
	low_data = eepromReadByte(eeprom_index+1);
	return ((high_data<<8)|low_data);
}

//DR! it's yours!!//
void calibrationFindOffset(uint8_t id)
{
	uint32_t eeprom_index;
	uint16_t offset_angle;

	//In the surface part, there are #NUM_SENSOR_IN_SURFACE sensors
	for(uint8_t ch_in_id =0; ch_in_id<NUM_SENSOR_IN_SURFACE; ch_in_id++)
	{
		//find offset_angle which has highest value in range of 0~1800 angle(/0.1 degree)
		//input : angle = 0~1800 calibrationLuxRead(ch_in_id, angle);
		//output :   offset_angle
		//offset_anlge = findingMax()


		//store in eeprom (ex, 0xABCD -> AB(low addr) CD(high addr))
		eeprom_index = (id*NUM_SENSOR_IN_SURFACE + ch_in_id)*2;
		eepromWriteByte(eeprom_index, (offset_angle>>8 | 0));
		eepromWriteByte(eeprom_index+1, (offset_angle | 0));
	}
}


void calibrationInit()
{
	uartOpen(CALI_SERIAL, 9600);
}

bool calibrationMain(uint8_t id)
{
	if (uartAvailable(CALI_SERIAL) > 0)
	{
		char c = uartRead(CALI_SERIAL);

		if(!cali_start)
		{
			if(c == '@')
			{
				if(rx_cnt == 7)
				{
					parse_start = false;
					cali_start	= true;

					calibrationParseInitCommand(command_packet);
					cmdifPrintf("Cali Init Done\n");

					memset(command_packet, 0, sizeof(command_packet));
				}
			}

			if(parse_start)
			{
				command_packet[rx_cnt] = c;
				rx_cnt++;
			}
			if(c == '#') parse_start = true;
		}

		else
		{
			if(c == '@')
			{
				if(rx_cnt == 2)
				{
					parse_start = false;

					curr_angle += step;

					if(curr_angle != calibrationParseCommand(command_packet)) return 0;
					if(curr_angle > final_angle)
					{
						cmdifPrintf("\n curr angle : %d ", curr_angle);
						cmdifPrintf("FINAL, now calibration end");
						calibrationFindOffset(id);
						///
						return 1;
					}

					cmdifPrintf("\n curr angle : %d ", curr_angle);

					calibrationLuxStore(id, curr_angle, iter_rx_cnt);

					ack_packet[1] = (curr_angle >> 8 | 0);
					ack_packet[2] = (curr_angle | 0);
					ret = uartWrite(CALI_SERIAL, (uint8_t *)ack_packet, 4);
					memset(command_packet, 0, sizeof(command_packet));
					memset(ack_packet, 0, sizeof(ack_packet));

				}
			}

			if(parse_start)
			{
				command_packet[rx_cnt] = c;
				rx_cnt++;
			}
			if(c == '#') parse_start = true;
		}
	}
	return 1;
}



	 //get
	 //sorting -> value

	 //send - done
	 //read - next
	 //get - lux
	 //store - avr_lux/ eeprom
	 //send - done


