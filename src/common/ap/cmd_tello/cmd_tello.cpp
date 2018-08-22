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

using namespace std;

// 1. UART port open
// 2. send command
bool tello_begin_state = false;

void cmdTelloBegin(long baud)
{
	uartOpen(TELLO_SERIAL, 115200);
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


//[front, left1, left2, back, right 2, right 1]
void telloLeviosaCmdTest(uint8_t output)
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
		cmdifPrintf("Time : %d  \n", t_micros);

		if(output == 1)
		{
			for(int ch = 0; ch < (18/3); ch++)
			{
				cmdifPrintf("%d: %d mm\n", ch+1, output_lux[ch]);
			}
		}

		//1. takeoff (condition : )
		//2. land (condition : no signal detect during 10s) << already done by esp32
		//3. front/ back (condition : target distance - measuring distance < 50mm stable)
		//4. cw/ ccw(condition : left > target (ccw), right (cw))




		///////////////////////////////////////
		cmdifPrintf("\n");
		cmdifPrintf("\n");


	}

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
