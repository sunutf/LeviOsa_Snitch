/*
 * hw.h
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#ifndef HW_H_
#define HW_H_


#ifdef __cplusplus
 extern "C" {
#endif



#include "hw_def.h"
#include "bsp.h"
#include "swtimer.h"
#include "qbuffer.h"
#include "vcp.h"
#include "led.h"
#include "timer.h"
#include "uart.h"
#include "eeprom.h"
#include "flash.h"

#include "wdg.h"
#include "i2c.h"
#include "mux.h"



void hwInit(void);

void hwPowerOff(void);
void hwPowerOn(void);


void delay(uint32_t delay_ms);
void delayMillis(uint32_t delay_ms);
void delayMicros(uint32_t delay_us);
void delaySeconds(uint32_t delay_sec);

uint32_t millis(void);
uint32_t micros(void);


typedef struct
{
  int16_t   present_load;
  uint32_t  present_velocity;
  uint32_t  present_position;
} __attribute__((packed)) hw_motor_bulkread_t;




typedef struct
{
  flash_attr_t motion;
  flash_attr_t task;
} hw_flash_info_t;


typedef struct
{
  hw_flash_info_t  flash;

} hw_t;



extern hw_t *p_hw;


#ifdef __cplusplus
 }
#endif


#endif /* HW_H_ */
