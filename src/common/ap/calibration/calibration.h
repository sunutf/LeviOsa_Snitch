/*
 * calibration.h
 *
 *  Created on: Nov 29, 2018
 *      Author: D.ggavy
 */

#ifndef SRC_COMMON_AP_CALIBRATION_CALIBRATION_H_
#define SRC_COMMON_AP_CALIBRATION_CALIBRATION_H_

#include "test_def.h"
#include "hw.h"

#ifdef __cplusplus
 extern "C" {
#endif

void calibrationInit(void);
bool calibrationMain(uint8_t);

#ifdef __cplusplus
 }
#endif

#endif /* SRC_COMMON_AP_CALIBRATION_CALIBRATION_H_ */
