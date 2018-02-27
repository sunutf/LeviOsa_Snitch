/*
 * drv_i2c.c
 *
 *  Created on: 2017. 4. 10.
 *      Author: D.ggavy
 */

#ifndef SRC_HW_DRIVER_DRV_I2C_C_
#define SRC_HW_DRIVER_DRV_I2C_C_


#ifdef __cplusplus
 extern "C" {
#endif


#include "hw_def.h"
#include "bsp.h"
#define I2C_MAX_CH      _HW_DEF_I2C_MAX_CH





bool drvI2CInit(void);


err_code_t drvI2CTransmit(uint8_t ch, uint8_t addr, uint8_t *p_data, uint32_t length, uint32_t timeout);

err_code_t drvI2CWrites(uint8_t ch, uint8_t addr, uint8_t reg_addr, uint8_t *p_data, uint32_t length, uint32_t timeout);
err_code_t drvI2CReads(uint8_t ch, uint8_t addr, uint8_t reg_addr, uint8_t *p_data, uint32_t length, uint32_t timeout);


#ifdef __cplusplus
 }
#endif

#endif
