/*
 * def.h
 *
 *  Created on: 2017. 2. 14.
 *      Author: HanCheol Cho
 */

#ifndef DEF_H_
#define DEF_H_



#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#include "error_code.h"
#include "cmdif/cmdif.h"



#define _DEF_UART1          0
#define _DEF_UART2          1
#define _DEF_UART3          2
#define _DEF_UART4          3
#define _DEF_UART5          4
#define _DEF_UART6          5

#define _DEF_LEFT           0
#define _DEF_RIGHT          1

#define _DEF_INPUT            0
#define _DEF_INPUT_PULLUP     1
#define _DEF_INPUT_PULLDOWN   2
#define _DEF_OUTPUT           3
#define _DEF_OUTPUT_PULLUP    4
#define _DEF_OUTPUT_PULLDOWN  5

#define _DEF_HIGH           1
#define _DEF_LOW            0


#define _DEF_TIMER1         0
#define _DEF_TIMER2         1
#define _DEF_TIMER3         2
#define _DEF_TIMER4         3


#define _DEF_I2C1           0
#define _DEF_I2C2           1
#define _DEF_I2C3           2
#define _DEF_I2C4           3

#define _DEF_BUTTON1        0


#define _DEF_DXL1           0
#define _DEF_DXL2           1
#define _DEF_DXL3           2
#define _DEF_DXL4           3
#define _DEF_DXL5           4

#define _DEF_BUTTON1        0
#define _DEF_BUTTON2        1
#define _DEF_BUTTON3        2
#define _DEF_BUTTON4        3
#define _DEF_BUTTON5        4

#define _DEF_ADC1           0
#define _DEF_ADC2           1
#define _DEF_ADC3           2
#define _DEF_ADC4           3
#define _DEF_ADC5           4
#define _DEF_ADC6           5
#define _DEF_ADC7           6
#define _DEF_ADC8           7

#define _DEF_PWM1           0
#define _DEF_PWM2           1
#define _DEF_PWM3           2
#define _DEF_PWM4           3
#define _DEF_PWM5           4
#define _DEF_PWM6           5
#define _DEF_PWM7           6
#define _DEF_PWM8           7

#define _DEF_SPI1           0
#define _DEF_SPI2           1
#define _DEF_SPI3           2
#define _DEF_SPI4           3
#define _DEF_SPI5           4
#define _DEF_SPI6           5
#define _DEF_SPI7           6
#define _DEF_SPI8           7

#define _DEF_RESET_POWER    0
#define _DEF_RESET_PIN      1
#define _DEF_RESET_WDG      2
#define _DEF_RESET_SOFT     3


#define _DEF_DXL_BAUD_9600      0
#define _DEF_DXL_BAUD_57600     1
#define _DEF_DXL_BAUD_115200    2
#define _DEF_DXL_BAUD_1000000   3
#define _DEF_DXL_BAUD_2000000   4
#define _DEF_DXL_BAUD_3000000   5
#define _DEF_DXL_BAUD_4000000   6
#define _DEF_DXL_BAUD_4500000   7


#define _DEF_DXL_AX             0
#define _DEF_DXL_RX             1
#define _DEF_DXL_MX             2
#define _DEF_DXL_XL             3



#define _DEF_DXL_MODEL_AX12A        12
#define _DEF_DXL_MODEL_AX18A        18
#define _DEF_DXL_MODEL_AX12W        300
#define _DEF_DXL_MODEL_XL430        1060
#define _DEF_DXL_MODEL_XM430_W210   1030
#define _DEF_DXL_MODEL_XM430_W350   1020
#define _DEF_DXL_MODEL_2XL430       1090




typedef uint32_t  err_code_t;




typedef void (*voidFuncPtr)(void);



typedef union
{
  uint8_t  u8Data[4];
  uint16_t u16Data[2];
  uint32_t u32Data;

  int8_t   s8Data[4];
  int16_t  s16Data[2];
  int32_t  s32Data;

  uint8_t  u8D;
  uint16_t u16D;
  uint32_t u32D;

  int8_t   s8D;
  int16_t  s16D;
  int32_t  s32D;
} data_t;


typedef struct
{
  data_t data;
  bool   ret;
} data_ret_t;


typedef struct
{
  uint32_t  ptr_in;
  uint32_t  ptr_out;
  uint32_t  length;
  uint8_t  *p_buf;
} ring_buf_t;


typedef struct
{
  uint32_t addr;
  uint32_t end;
  uint32_t length;
} flash_attr_t;



#define PI              3.1415926535897932384626433832795
#define HALF_PI         1.5707963267948966192313216916398
#define TWO_PI          6.283185307179586476925286766559
#define DEG_TO_RAD      0.017453292519943295769236907684886
#define RAD_TO_DEG      57.295779513082320876798154814105
#define EULER           2.718281828459045235360287471352

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#ifndef max
#define max(a,b) (((a) (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif


#endif /* DEF_H_ */
