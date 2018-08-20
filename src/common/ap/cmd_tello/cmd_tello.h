/*
 * cmd_tello.h
 *
 *  Created on: 2018. 8. 20.
 *      Author: D.ggavy
 */
#ifndef SRC_COMMON_AP_CMD_TELLO_CMD_TELLO_H_
#define SRC_COMMON_AP_CMD_TELLO_CMD_TELLO_H_

#include "test_def.h"
#include "hw.h"


#ifndef cmd_tello_h
#define cmd_tello_h

#define TELLO_SERIAL  _DEF_UART3

typedef enum {
	COMMAND=0,
	TAKEOFF,
	LAND,
	GO_UP,
	GO_DOWN,
	GO_LEFT,
	GO_RIGHT,
	GO_FORWARD,
	GO_BACK,
	CW,
	CCW,
	FLIP,
	SPEED,

}cmd_tello_type;

#endif
void telloInit(void);
void cmdTelloBegin(long);
void cmdTelloSend(cmd_tello_type, int);


#endif /* SRC_COMMON_AP_CMD_TELLO_CMD_TELLO_H_ */
