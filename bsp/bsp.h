/*
 * bsp.h
 *
 *  Created on: Feb 10, 2017
 *      Author: baram
 */

#ifndef BSP_H_
#define BSP_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "hw_def.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"

#include "rtos.h"

void bspInit();
void bspInitUSB(void);


#ifdef __cplusplus
 }
#endif

#endif /* BSP_H_ */
