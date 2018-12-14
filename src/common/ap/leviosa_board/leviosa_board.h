/*
 * leviosa_board.h
 *
 *  Created on: 2018. 3. 8.
 *      Author: D.ggavy
 */

#ifndef SRC_COMMON_AP_TEST_LEVIOSA_BOARD_LEVIOSA_BOARD_H_
#define SRC_COMMON_AP_TEST_LEVIOSA_BOARD_LEVIOSA_BOARD_H_

#ifdef __cplusplus
 extern "C" {
#endif
#include "hw.h"
#include "hw_def.h"

#include "bsp.h"

 void leviosa_boardInit(void);
 void leviosa_boardReady(void);
 void leviosa_boardSetCmd(void);
 void leviosa_boardGetCmd(void);
 void leviosa_boardCalcSource(void);
 float* leviosa_boardGetLuxBuf(uint8_t output);
 void leviosa_boardConvDistance(void);
 uint32_t* leviosa_boardGetDistance(void);
 void leviosa_boardLuxTest(uint8_t output);
 void leviosa_boardCalcCoord(void);
 void leviosa_boardCaliTest(uint8_t);


#define MAX_CH_PER_MUX 6
#define NUM_MUX        6
#define NUM_SENSOR   (NUM_MUX*MAX_CH_PER_MUX)

#define ALL_CH   8



#ifdef __cplusplus
 }
#endif
#endif /* SRC_COMMON_AP_TEST_LEVIOSA_BOARD_LEVIOSA_BOARD_H_ */
