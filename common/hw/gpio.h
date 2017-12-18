/*
 * gpio.h
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#ifndef GPIO_H_
#define GPIO_H_


#ifdef __cplusplus
 extern "C" {
#endif

#include "hw_def.h"

#ifdef _USE_HW_GPIO
#include "driver/drv_gpio.h"


bool gpioInit(void);

#endif

#ifdef __cplusplus
}
#endif



#endif /* GPIO_H_ */
