/*
 * drv_timer.c
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */


#include <stdarg.h>
#include <stdbool.h>

#include "drv_timer.h"



typedef struct
{
  TIM_HandleTypeDef hTIM;
  uint8_t  enable;
  uint32_t freq;
  uint32_t prescaler_value;
  uint32_t prescaler_value_high_res;
  uint32_t prescaler_div;
  uint32_t period;
  voidFuncPtr handler;
} drv_timer_t;



//-- Internal Variables
drv_timer_t drv_timer_tbl[TIMER_MAX_CH];
//



//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//




bool drvTimerInit(void)
{
  uint8_t tim_ch;
  uint8_t i;


  //-- TIM4
  //
  tim_ch = _DEF_TIMER1;
  drv_timer_tbl[tim_ch].hTIM.Instance               = TIM4;
  drv_timer_tbl[tim_ch].prescaler_value             = (uint32_t)((SystemCoreClock / 2) / 10000  ) - 1; // 0.01Mhz
  drv_timer_tbl[tim_ch].prescaler_value_high_res    = (uint32_t)((SystemCoreClock / 2) / 1000000) - 1; // 1.00Mhz
  drv_timer_tbl[tim_ch].prescaler_div               = 100;
  drv_timer_tbl[tim_ch].hTIM.Init.Period            = 10000 - 1;
  drv_timer_tbl[tim_ch].hTIM.Init.Prescaler         = drv_timer_tbl[tim_ch].prescaler_value;
  drv_timer_tbl[tim_ch].hTIM.Init.ClockDivision     = 0;
  drv_timer_tbl[tim_ch].hTIM.Init.CounterMode       = TIM_COUNTERMODE_UP;
  drv_timer_tbl[tim_ch].hTIM.Init.RepetitionCounter = 0;


  //-- TIM7
  //
  tim_ch = _DEF_TIMER2;
  drv_timer_tbl[tim_ch].hTIM.Instance               = TIM7;
  drv_timer_tbl[tim_ch].prescaler_value             = (uint32_t)((SystemCoreClock / 2) / 10000  ) - 1; // 0.01Mhz
  drv_timer_tbl[tim_ch].prescaler_value_high_res    = (uint32_t)((SystemCoreClock / 2) / 1000000) - 1; // 1.00Mhz
  drv_timer_tbl[tim_ch].prescaler_div               = 100;
  drv_timer_tbl[tim_ch].hTIM.Init.Period            = 10000 - 1;
  drv_timer_tbl[tim_ch].hTIM.Init.Prescaler         = drv_timer_tbl[tim_ch].prescaler_value;
  drv_timer_tbl[tim_ch].hTIM.Init.ClockDivision     = 0;
  drv_timer_tbl[tim_ch].hTIM.Init.CounterMode       = TIM_COUNTERMODE_UP;
  drv_timer_tbl[tim_ch].hTIM.Init.RepetitionCounter = 0;


  //-- TIM3
  //
  tim_ch = _DEF_TIMER3;
  drv_timer_tbl[tim_ch].hTIM.Instance               = TIM3;
  drv_timer_tbl[tim_ch].prescaler_value             = (uint32_t)((SystemCoreClock / 2) / 10000  ) - 1; // 0.01Mhz
  drv_timer_tbl[tim_ch].prescaler_value_high_res    = (uint32_t)((SystemCoreClock / 2) / 1000000) - 1; // 1.00Mhz
  drv_timer_tbl[tim_ch].prescaler_div               = 100;
  drv_timer_tbl[tim_ch].hTIM.Init.Period            = 10000 - 1;
  drv_timer_tbl[tim_ch].hTIM.Init.Prescaler         = drv_timer_tbl[tim_ch].prescaler_value;
  drv_timer_tbl[tim_ch].hTIM.Init.ClockDivision     = 0;
  drv_timer_tbl[tim_ch].hTIM.Init.CounterMode       = TIM_COUNTERMODE_UP;
  drv_timer_tbl[tim_ch].hTIM.Init.RepetitionCounter = 0;


  for( i=0; i<TIMER_MAX_CH; i++ )
  {
    drv_timer_tbl[i].handler = NULL;
    drv_timer_tbl[i].enable  = 0;
  }

  return true;
}

void drvTimerStop(uint8_t channel)
{
  if( channel >= TIMER_MAX_CH ) return;

  drv_timer_tbl[channel].enable = 0;
  HAL_TIM_Base_DeInit(&drv_timer_tbl[channel].hTIM);
}

void drvTimerSetPeriod(uint8_t channel, uint32_t period_data)
{
  if( channel >= TIMER_MAX_CH ) return;

  if( period_data > 0xFFFF )
  {
    drv_timer_tbl[channel].hTIM.Init.Prescaler = drv_timer_tbl[channel].prescaler_value;
    drv_timer_tbl[channel].hTIM.Init.Period    = (period_data/drv_timer_tbl[channel].prescaler_div) - 1;
  }
  else
  {
    if( period_data > 0 )
    {
      drv_timer_tbl[channel].hTIM.Init.Prescaler = drv_timer_tbl[channel].prescaler_value_high_res;
      drv_timer_tbl[channel].hTIM.Init.Period    = period_data - 1;
    }
  }
}

void drvTimerAttachInterrupt(uint8_t channel, voidFuncPtr handler)
{
  if( channel >= TIMER_MAX_CH ) return;

  drvTimerStop(channel);

  drv_timer_tbl[channel].handler = handler;

}


void drvTimerDetachInterrupt(uint8_t channel)
{
  if( channel >= TIMER_MAX_CH ) return;


  drv_timer_tbl[channel].handler = NULL;
}

void drvTimerStart(uint8_t channel)
{
  if( channel >= TIMER_MAX_CH ) return;

  HAL_TIM_Base_Init(&drv_timer_tbl[channel].hTIM);
  HAL_TIM_Base_Start_IT(&drv_timer_tbl[channel].hTIM);

  drv_timer_tbl[channel].enable = 1;
}










void drvTimerCallback(TIM_HandleTypeDef *htim)
{
  uint8_t i;


  for( i=0; i<_HW_DEF_TIMER_CH_MAX; i++ )
  {
    if( htim->Instance == drv_timer_tbl[i].hTIM.Instance )
    {
      if( drv_timer_tbl[i].handler != NULL )
      {
        (*drv_timer_tbl[i].handler)();
      }
    }
  }
}


void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&drv_timer_tbl[_DEF_TIMER1].hTIM);
}

void TIM7_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&drv_timer_tbl[_DEF_TIMER2].hTIM);
}

void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&drv_timer_tbl[_DEF_TIMER3].hTIM);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if( htim->Instance == TIM4 )                  // _DEF_TIMER1
  {
    __HAL_RCC_TIM4_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM4_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  }

  if( htim->Instance == TIM7 )                  // _DEF_TIMER2
  {
    __HAL_RCC_TIM7_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM7_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
  }

  if( htim->Instance == TIM3 )                  // _DEF_TIMER3
  {
    __HAL_RCC_TIM3_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM3_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }

  if( htim->Instance == TIM6 )
  {
    __HAL_RCC_TIM6_CLK_ENABLE();
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
  if( htim->Instance == TIM4 )
  {
    HAL_NVIC_DisableIRQ(TIM4_IRQn);
  }

  if( htim->Instance == TIM7 )
  {
    HAL_NVIC_DisableIRQ(TIM7_IRQn);
  }

  if( htim->Instance == TIM3 )
  {
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  }

  if( htim->Instance == TIM6 )
  {
    __HAL_RCC_TIM6_FORCE_RESET();
    __HAL_RCC_TIM6_RELEASE_RESET();
  }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  else
  {
    drvTimerCallback(htim);
  }
}
