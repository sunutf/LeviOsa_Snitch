/*
 *  hw_def.h
 *
 *  Created on: 2016. 5. 14.
 *      Author: Baram
 */





#ifndef HW_DEF_H
#define HW_DEF_H

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#include "def.h"
#include "error_code.h"


#ifndef BOOL
#define BOOL uint8_t
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define LEFT  1
#define RIGHT 0

//
//#define _USE_HW_RTOS
#define _USE_HW_VCP
#define _USE_HW_TIMER
#define _USE_HW_SW_TIMER
#define _USE_HW_LED
//#define _USE_HW_BUTTON
#define _USE_HW_UART
//#define _USE_HW_RESET
//#define _USE_HW_MIC
//#define _USE_HW_ADC
#define _USE_HW_I2C
//#define _USE_HW_IMU
//#define _USE_HW_LOG
//#define _USE_HW_CTABLE
#define _USE_HW_TCS34725
#define _USE_HW_TCA9548A
//
//
#define _USE_HW_CMDIF_LED
//#define _USE_HW_CMDIF_BUTTON
//#define _USE_HW_CMDIF_RESET
//#define _USE_HW_CMDIF_MIC
//#define _USE_HW_CMDIF_ADC
#define _USE_HW_CMDIF_I2C
//#define _USE_HW_CMDIF_IMU
#define _USE_HW_CMDIF_TCS34725
#define _USE_HW_CMDIF_TCA9548A


#define _HW_DEF_BUZZER_TIMER                  _DEF_TIMER1
#define _HW_DEF_SW_TIMER                      _DEF_TIMER3
#define _HW_DEF_POWER_ADC_CH                  _DEF_ADC6



#define _HW_DEF_CMDIF_LIST_MAX                32
#define _HW_DEF_LED_CH_MAX                    4
#define _HW_DEF_BUTTON_CH_MAX                 2
#define _HW_DEF_UART_CH_MAX                   2
#define _HW_DEF_TIMER_CH_MAX                  3
#define _HW_DEF_SW_TIMER_MAX                  8
#define _HW_DEF_DXLPORT_MAX_CH                4
#define _HW_DEF_ADC_MAX_CH                    6
#define _HW_DEF_I2C_MAX_CH      			  1


#define _HW_DEF_LED_MANAGE                    3  // RED
#define _HW_DEF_LED_PLAY                      4  // GREEN
#define _HW_DEF_LED_ARDUINO                   5  // BLUE
#define _HW_DEF_LED_BATTERY                   0  // RED


#define _HW_DEF_BUTTON_MODE                   0
#define _HW_DEF_BUTTON_START                  1

#define _HW_DEF_RTOS_MEM_SIZE(x)              ((x)/4)

#define _HW_DEF_FLASH_ADDR_MOTION_LENGTH      (512*1024)
#define _HW_DEF_FLASH_ADDR_MOTION_START       0x8080000
#define _HW_DEF_FLASH_ADDR_MOTION_END         (_HW_DEF_FLASH_ADDR_MOTION_START + _HW_DEF_FLASH_ADDR_MOTION_LENGTH)

#define _HW_DEF_FLASH_ADDR_TASK_LENGTH        (64*1024)
#define _HW_DEF_FLASH_ADDR_TASK_START         0x8010000
#define _HW_DEF_FLASH_ADDR_TASK_END           (_HW_DEF_FLASH_ADDR_TASK_START + _HW_DEF_FLASH_ADDR_TASK_LENGTH)






#endif

