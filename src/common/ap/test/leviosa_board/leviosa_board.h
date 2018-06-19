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

char XYZ[] = {'X', 'Y', 'Z'};

 /*
 S=
    -0.0278   -0.0106   -0.1005   -0.0760   -0.0118    0.0675    0.0932    0.1177    0.0694    0.0052   -0.0503   -0.1145
    -0.0202    0.0327    0.0202    0.0957    0.1018    0.1018    0.0427   -0.0327   -0.0754   -0.1221   -0.0893   -0.0427
    -0.1263    0.1263   -0.0814    0.0470   -0.0814    0.0470   -0.0814    0.0470   -0.0814    0.0470   -0.0814    0.0470

 ETA =
     0.0000         0   -0.1130   -0.0914   -0.0349    0.0349    0.0914    0.1130    0.0914    0.0349   -0.0349   -0.0914
    -0.0000         0    0.0000    0.0664    0.1074    0.1074    0.0664    0.0000   -0.0664   -0.1074   -0.1074   -0.0664
    -0.1263    0.1263   -0.0565    0.0565   -0.0565    0.0565   -0.0565    0.0565   -0.0565    0.0565   -0.0565    0.0565
  */

 float S[][3] = {
{-0.0278, -0.0202, -0.1263},
{-0.0106, 0.0327, 0.1263},
{-0.1005, 0.0202, -0.0814},
{-0.0760, 0.0957, 0.0470},
{-0.0118, 0.1018, -0.0814},
{0.0675, 0.1018, 0.0470},
{0.0932, 0.0427, -0.0814},
{0.1177, -0.0327, 0.0470},
{0.0694, -0.0754, -0.0814},
{0.0052, -0.1221, 0.0470},
{-0.0503, -0.0893, -0.0814},
{-0.1145, -0.0427, 0.0470}
 };

 float ETA[][3] = {
{0.0000, -0.0000, -0.1263},
{0, 0, 0.1263},
{-0.1130, 0.0000, -0.0565},
{-0.0914, 0.0664, 0.0565},
{-0.0349, 0.1074, -0.0565},
{0.0349, 0.1074, 0.0565},
{0.0914, 0.0664, -0.0565},
{0.1130, 0.0000, 0.0565},
{0.0914, -0.0664, -0.0565},
{0.0349, -0.1074, 0.0565},
{-0.0349, -0.1074, -0.0565},
{-0.0914, -0.0664, 0.0565}
 };

#endif /* SRC_COMMON_AP_TEST_LEVIOSA_BOARD_LEVIOSA_BOARD_H_ */
