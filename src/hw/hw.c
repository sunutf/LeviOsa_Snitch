/*
 * hw.c
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */



#include "hw.h"





//-- Internal Variables
//
static hw_t hw_def;

hw_t *p_hw = &hw_def;

TIM_HandleTypeDef  TimHandle2;



//-- External Variables
//


//-- Internal Functions
//
void microsInit(void);
uint32_t microsGetMicros(void);


//-- External Functions
//





void hwInit(void)
{
  cmdifInit();

  qbufferInit();
  swtimerInit();
  timerInit();
  microsInit();

  ledInit();
 // buttonInit();
  muxInit();

  bspInitUSB();

  uartInit();
//  logInit();
//  eepromInit();
//  flashInit();
//  resetInit();
  i2cInit();
  tcs34725Init();
  tca9548aInit();
}


void delay(uint32_t delay_ms)
{
#ifdef _USE_HW_RTOS
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
    osDelay(delay_ms);
  }
  else
  {
    HAL_Delay(delay_ms);
  }
#else
  HAL_Delay(delay_ms);
#endif
}

void delayMillis(uint32_t delay_ms)
{
  HAL_Delay(delay_ms);
}

void delayMicros(uint32_t delay_us)
{
  uint32_t tickstart = 0;


  tickstart = micros();
  while((micros() - tickstart) < delay_us)
  {
  }
}

void delaySeconds(uint32_t delay_sec)
{

}

uint32_t millis(void)
{
  return HAL_GetTick();
}

uint32_t micros(void)
{
  return microsGetMicros();
}


void hwInitDef(void)
{

}





void microsInit(void)
{
  __HAL_RCC_TIM2_CLK_ENABLE();


  /* Set TIMx instance */
  TimHandle2.Instance = TIM2;

  /* Initialize TIM3 peripheral as follow:
         + Period = 10000 - 1
         + Prescaler = ((SystemCoreClock/2)/10000) - 1
         + ClockDivision = 0
         + Counter direction = Up
   */
  TimHandle2.Init.Period         = 0xFFFFFFFF;;
  TimHandle2.Init.Prescaler      = (SystemCoreClock/2/1000000)-1;
  TimHandle2.Init.ClockDivision  = 0;
  TimHandle2.Init.CounterMode    = TIM_COUNTERMODE_UP;

  HAL_TIM_Base_Init(&TimHandle2);
  HAL_TIM_Base_Start_IT(&TimHandle2);
}

uint32_t microsGetMicros(void)
{
  return TimHandle2.Instance->CNT;
}




