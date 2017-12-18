/*
 *  drv_reset.h
 *
 *  Created on: 2017. 6. 9.
 *      Author: Baram
 */

#ifndef DRV_RESET_H
#define DRV_RESET_H


#ifdef __cplusplus
 extern "C" {
#endif


#include "def.h"
#include "bsp.h"


bool drvResetInit(void);
uint8_t drvResetGetStatus(void);
void drvResetRunWdgReset(void);

#ifdef __cplusplus
}
#endif


#endif
