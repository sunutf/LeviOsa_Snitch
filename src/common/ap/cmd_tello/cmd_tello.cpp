/*
 * cmd_tello.cpp
 *
 *  Created on: 2018. 8. 20.
 *      Author: D.ggavy
 */

#include <string>
#include "cmd_tello\cmd_tello.h"
#include "hw.h"
#include "hw_def.h"
#include "leviosa_board\leviosa_board.h"

#define START_COND 70
#define TARGET_DIST 300
#define TARGET_OFFSET 50
#define NUM_SEN_PART 6

using namespace std;

bool  standby = false;
bool	flying = false;

// 1. UART port open
// 2. send command
bool tello_begin_state = false;

uint8_t findMinIndex(uint32_t*);


void cmdTelloBegin(long baud)
{
	uartOpen(TELLO_SERIAL, baud);
	uartPrintf(TELLO_SERIAL, "command,");
	tello_begin_state = true;
}

void cmdTelloSend(cmd_tello_type command, int cmd_value)
{
	if(!tello_begin_state) cmdTelloBegin(115200);

	switch(command)
	{
		case COMMAND :
			uartPrintf(TELLO_SERIAL, "command,");
			break;

		case TAKEOFF :
			uartPrintf(TELLO_SERIAL, "takeoff,");
			break;

		case LAND :
			uartPrintf(TELLO_SERIAL, "land,");
			break;

		case GO_UP :
			uartPrintf(TELLO_SERIAL, "up %d,", cmd_value);
			break;

		case GO_DOWN :
			uartPrintf(TELLO_SERIAL, "down %d,", cmd_value);
			break;

		case GO_LEFT :
				uartPrintf(TELLO_SERIAL, "left %d,", cmd_value);
				break;

		case GO_RIGHT :
				uartPrintf(TELLO_SERIAL, "right %d,", cmd_value);
				break;

		case GO_FORWARD :
				uartPrintf(TELLO_SERIAL, "forward %d,", cmd_value);
				break;

		case GO_BACK :
				uartPrintf(TELLO_SERIAL, "back %d,", cmd_value);
				break;

		case CW :
				uartPrintf(TELLO_SERIAL, "cw %d,", cmd_value);
				break;

		case CCW :
				uartPrintf(TELLO_SERIAL, "ccw %d,", cmd_value);
				break;

		case FLIP :
				uartPrintf(TELLO_SERIAL, "flip %d,", cmd_value);
				break;

		case SPEED :
				uartPrintf(TELLO_SERIAL, "speed %d,", cmd_value);
				break;
  }
}


//dir : ccw[front, left1, left2, back, right 2, right 1]
void telloLeviosaCmdTest(uint8_t output)
{
	uint32_t   t_micros;
	uint32_t   t_millis;
	uint32_t*  distance_lux;
	float*		 source_lux;
	uint8_t    max_index;
	int value ;

	leviosa_boardReady();
	leviosa_boardSetCmd();
	cmdTelloBegin(115200);

	while(cmdifRxAvailable() == 0)
	{
		t_micros = micros();

		leviosa_boardGetCmd();
		leviosa_boardCalcSource();
		leviosa_boardConvDistance();
		leviosa_boardCalcCoord();

		source_lux = leviosa_boardGetLuxBuf(0);
		distance_lux = leviosa_boardGetDistance();
		t_micros = micros() - t_micros;
		cmdifPrintf("Time : %d  \n", t_micros);

		if(output == 2)
		{
			for(int ch = 0; ch < NUM_SEN_PART; ch++)
			{
				cmdifPrintf("%d: %d mm\n", ch+1, distance_lux[ch]);
			}
		}


		max_index = findMinIndex(distance_lux); //MAX_LUX
		cmdifPrintf("1st : %d\n", max_index);


		//1. takeoff (condition : )
		//2. land (condition : no signal detect during 10s) << already done by esp32
		//3. front/ back (condition : target distance - measuring distance < 50mm stable)
		//4. cw/ ccw(condition : left > target (ccw), right (cw))

		//standby
		if(!flying)
		{
			ledOn(0);
			uartPrintf(TELLO_SERIAL, "command,");
			uartPrintf(TELLO_SERIAL, "land,");
			cmdifPrintf("standby takeoff signal\n");

			if(source_lux[max_index] > START_COND)
			{
				if(!standby)
				{
					t_millis = millis();
					standby = true;
				}
				else
				{
					if((millis() - t_millis) > 3000)
					{
						uartPrintf(TELLO_SERIAL, "up %d,",300);
//						uartPrintf(TELLO_SERIAL, "takeoff,down %d,",300);
						cmdifPrintf("send flying\n");

						flying = true;
						standby = false;
					}
				}
			}
			else
			{
				standby = false;
				cmdifPrintf("standby again\n");
			}
		}

		//takeoff
		else
		{
			//land condition
			ledOff(0);
			ledOn(1);

			uartPrintf(TELLO_SERIAL, "command,");
			cmdifPrintf("flying\n");
			if(source_lux[max_index] < START_COND)
			{
				cmdifPrintf("standby during flying\n");
				if(!standby)
				{
					t_millis = millis();
					standby = true;
				}
				else
				{
					if((millis() - t_millis) > 4000)
					{
						uartPrintf(TELLO_SERIAL, "land,");
						flying = false;
						standby = false;
						cmdifPrintf("landing\n");
						ledOff(1);
						ledOn(0);
					}
				}
			}
			else
			{
				standby = false;

				//go/back
				if(0 == max_index)
				{
					int diff_dist = (int)TARGET_DIST - (int)distance_lux[max_index];

					value = 60;
					//FASTER
//					if(abs(diff_dist) > 200)
//					{
//						value = 40;
//					}

					cmdifPrintf("diff_dist : %d\n", diff_dist);
					//back
					if(diff_dist > TARGET_OFFSET)
					{
						uartPrintf(TELLO_SERIAL, "back %d,", value);
						cmdifPrintf("back : %d\n", value);
					}

					//go
					else if(diff_dist < -(TARGET_OFFSET))
					{
						uartPrintf(TELLO_SERIAL, "forward %d,", value);
						cmdifPrintf("go : %d \n ", value);

					}

					//stay
					else
					{

					}
				}

				//ccw/cw
				else
				{
					value = 60;

					//cw or flip L
					if(max_index >= 3)
					{

						if(0 == output)
						{
							for(uint8_t cnt=0; cnt < (NUM_SEN_PART-max_index); cnt++)
							{
								uartPrintf(TELLO_SERIAL, "cw %d,", value);

		//							delay(100);
							}
						}
						else if(1 == output)
						{
							uartPrintf(TELLO_SERIAL, "flip r,");
							cmdifPrintf("flip Right\n");
						}

					}

					//ccw or flip R
					else
					{
						if(0 == output)
						{
							for(uint8_t cnt=0; cnt < max_index; cnt++)
							{
								uartPrintf(TELLO_SERIAL, "ccw %d,", value);
								cmdifPrintf("ccw : %d\n", value);
	//							delay(500);
							}
						}
						else if(1 == output)
						{
							uartPrintf(TELLO_SERIAL, "flip l,");
							cmdifPrintf("flip Left\n");
						}
					}
				}
			}
		}



		///////////////////////////////////////
		cmdifPrintf("\n");
		cmdifPrintf("\n");


	}

}

uint8_t findMinIndex(uint32_t* arr)
{
	uint8_t ret = 0;

	for(uint8_t i=1; i < NUM_SEN_PART; i++)
	{
		if(arr[i] < arr[ret])
		{
			ret = i;
		}
	}
	return ret;
}


#ifdef _USE_HW_CMDIF_TELLO
void telloCmdifInit(void);
int  telloCmdif(int argc, char **argv);
#endif



void telloInit(void)
{
	#ifdef _USE_HW_CMDIF_TELLO
		telloCmdifInit();
	#endif
}

#ifdef _USE_HW_CMDIF_TELLO
void telloCmdifInit(void)
{
	cmdifAdd("tello", telloCmdif);
}

int telloCmdif(int argc, char **argv)
{
	bool ret = true;
	int value = 0;

	//recommanded value :100
	value = (uint8_t) strtoul((const char * ) argv[2], (char **)NULL, (int) 0);

	if(argc == 3 && strcmp("takeoff", argv[1]) == 0)
	{
		cmdTelloSend(TAKEOFF, value);
	}

	else if(argc == 3 && strcmp("land", argv[1]) == 0)
	{
		cmdTelloSend(LAND, value);
	}

	else if(argc == 3 && strcmp("up", argv[1]) == 0)
	{
		cmdTelloSend(GO_UP, value);
	}

	else if(argc == 3 && strcmp("down", argv[1]) == 0)
	{
		cmdTelloSend(GO_DOWN, value);
	}

	else if(argc == 3 && strcmp("left", argv[1]) == 0)
	{
		cmdTelloSend(GO_LEFT, value);
	}

	else if(argc == 3 && strcmp("right", argv[1]) == 0)
	{
		cmdTelloSend(GO_RIGHT, value);
	}

	else if(argc == 3 && strcmp("forward", argv[1]) == 0)
	{
		cmdTelloSend(GO_FORWARD, value);
	}

	else if(argc == 3 && strcmp("back", argv[1]) == 0)
	{
		cmdTelloSend(GO_BACK, value);
	}

	else if(argc == 3 && strcmp("cw", argv[1]) == 0)
	{
		cmdTelloSend(CW, value);
	}

	else if(argc == 3 && strcmp("ccw", argv[1]) == 0)
	{
		cmdTelloSend(CCW, value);
	}

	else if(argc == 3 && strcmp("flip", argv[1]) == 0)
	{
		uartPrintf(TELLO_SERIAL, "flip %s,", argv[2]);
	}

	else if(argc == 3 && strcmp("speed", argv[1]) == 0)
	{
		cmdTelloSend(SPEED, value);
	}

	else if(argc == 3 && strcmp("test", argv[1]) == 0)
	{
		telloLeviosaCmdTest(value);
	}

	else
	{
		ret = false;
	}

	if (ret == false)
	{
		cmdifPrintf("wrong command\n choose : tello [takeoff, land, up, down, left, right, forward, back, cw, ccw, flip, speed] [value]");
	}
	else if (ret)
	{
		cmdifPrintf("send command");
	}
	return 0;
}
#endif
