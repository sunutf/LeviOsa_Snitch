/*
 * mux.h
 *
 *  Created on: 2018. 2. 27.
 *      Author: D.ggavy
 */
#ifndef MUX_H_
#define MUX_H_

#ifdef __cplusplus
 extern "C" {
#endif


#include "hw_def.h"

#ifdef _USE_HW_MUX
#define MUX_MAX_CH   _HW_DEF_MUX_CH_MAX

#include "bsp.h"


void muxInit(void);


void muxEnable(uint8_t ch);
void muxDisable(uint8_t ch);
void muxSetIdnCh(uint8_t id, uint8_t ch);
uint8_t muxGetIdnch(uint8_t id);
bool muxScanChtoAllid(uint8_t ch);

#endif

#ifdef __cplusplus
}
#endif

#endif /* PRJ_SDK_HAL_LED_H_ */
