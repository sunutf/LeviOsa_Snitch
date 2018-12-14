/*
 * tca9548a.h
 *
 *  Created on: 2017. 12. 12.
 *      Author: D.ggavy
 */

#ifndef SRC_CMSDK_HW_MODULE_TCA9548A_H_
#define SRC_CMSDK_HW_MODULE_TCA9548A_H_

#ifdef __cplusplus
 extern "C" {
#endif
#include "hw.h"
#include "i2c.h"
#include "math.h"
#include "hw_def.h"
#include "tcs34725.h"
#include "TCA9548A/test_tca9548a.h"
#ifdef _USE_HW_TCA9548A

#include "bsp.h"



#define TCAADDR 0x70

bool tca9548aInit(void);
bool tcaSelect(uint8_t i2c_ch, uint8_t id, uint8_t ch);
void tcaDeSelect(uint8_t i2c_ch, uint8_t id);


err_code_t tcaI2CTransmit(uint8_t ch, uint8_t addr, uint8_t *p_data, uint32_t length, uint32_t timeout);


#ifdef __cplusplus
 }
#endif
#endif
#endif /* SRC_CMSDK_HW_MODULE_TCA9548A_H_ */
