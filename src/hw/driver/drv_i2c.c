/*
 * drv_i2c.c
 *
 *  Created on: 2017. 4. 10.
 *      Author: D.ggavy
 */

#include <stdarg.h>
#include <stdbool.h>

#include "hw.h"
#include "drv_i2c.h"
#include "drv_timer.h"



typedef struct
{


  GPIO_TypeDef *portSDA;
  uint16_t      pinSDA;
  GPIO_TypeDef *portSCL;
  uint16_t      pinSCL;
}drv_i2c_pin_t;

typedef struct
{
  uint32_t      speed;
  uint32_t      mode;
  drv_i2c_pin_t gpio;
}drv_i2c_t;



//-- Internal Variables
//
drv_i2c_t drv_i2c_tbl[I2C_MAX_CH];
static I2C_HandleTypeDef I2cHandle[I2C_MAX_CH];


//-- External Variables
//


//-- Internal Functions
//

uint8_t drvAddrWrite(uint8_t addr);
uint8_t drvAddrRead(uint8_t addr);
void drvI2CReset(uint8_t ch);
bool drvI2CBegin(uint8_t ch, uint32_t freq);
void drvI2CRecovery(uint8_t ch);

//-- External Functions
//


bool drvI2CInit(void)
{
  drvI2CReset(0);
  drvI2CBegin(0, 400);

  return true;
}

bool drvI2CBegin(uint8_t ch, uint32_t freq)
{
  __HAL_RCC_I2C3_FORCE_RESET();
  __HAL_RCC_I2C3_RELEASE_RESET();


  I2cHandle[0].Instance             = I2C3;
  I2cHandle[0].Init.ClockSpeed      = 100000;
  I2cHandle[0].Init.DutyCycle       = I2C_DUTYCYCLE_2;
  I2cHandle[0].Init.OwnAddress1     = 0x00;
  I2cHandle[0].Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle[0].Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle[0].Init.OwnAddress2     = 0xFF;
  I2cHandle[0].Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle[0].Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

  HAL_I2C_DeInit(&I2cHandle[0]);
  HAL_I2C_Init(&I2cHandle[0]);

  return true;
}

uint8_t drvAddrWrite(uint8_t addr)
{
  return addr<<=1;
}

uint8_t drvAddrRead(uint8_t addr)
{
  addr <<= 1;
  return addr += 1;
}

err_code_t drvI2CTransmit(uint8_t ch, uint8_t addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  err_code_t errcode = OK;
  HAL_StatusTypeDef ret;
  uint32_t i;


  for (i=0; i<3; i++)
  {
    ret = HAL_I2C_Master_Transmit(&I2cHandle[ch], (uint16_t)(addr << 1), p_data, length, timeout);

    if( ret == HAL_OK )
    {
      break;
    }
    else
    {
      drvI2CRecovery(ch);
    }
  }

  if (i == 3)
  {
    errcode = ERR_I2C_WRITE;
  }
  return errcode;
}



err_code_t drvI2CWrites(uint8_t ch, uint8_t addr, uint8_t reg_addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  err_code_t errcode = OK;
  HAL_StatusTypeDef ret;
  uint32_t i;


  for (i=0; i<3; i++)
  {
    ret = HAL_I2C_Mem_Write(&I2cHandle[ch], (uint16_t)(addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, p_data, length, timeout);

    if( ret == HAL_OK )
    {
      break;
    }
    else
    {
      drvI2CRecovery(ch);
    }
  }

  if (i == 3)
  {
    errcode = ERR_I2C_WRITE;
  }
  return errcode;
}

err_code_t drvI2CReads(uint8_t ch, uint8_t addr, uint8_t reg_addr, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  err_code_t errcode = OK;
  HAL_StatusTypeDef ret;
  uint32_t i;


  for (i=0; i<3; i++)
  {
    ret = HAL_I2C_Mem_Read(&I2cHandle[ch], (uint16_t)(addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)p_data, length, timeout);

    if( ret == HAL_OK )
    {
      break;
    }
    else
    {
      drvI2CRecovery(ch);
    }
  }

  if (i == 3)
  {
    errcode = ERR_I2C_READ;
  }

  return errcode;
}

void drvI2CReset(uint8_t ch)
{
  GPIO_InitTypeDef  GPIO_InitStruct;


  GPIO_InitStruct.Pin       = GPIO_PIN_8;
  GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin       = GPIO_PIN_9;
  GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  for (uint8_t i=0; i<9; i++)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
  }
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  */

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
  delayMicros(5);

  for (int i = 0; i < 9; i++)
  {

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    delayMicros(5);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    delayMicros(5);
  }

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
  delayMicros(5);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
  delayMicros(5);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  delayMicros(5);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
}

void drvI2CRecovery(uint8_t ch)
{
  //CLEAR_BIT(I2cHandle[ch].Instance->CR1,I2C_CR1_PE);

  drvI2CReset(ch);

  //SET_BIT(I2cHandle[ch].Instance->CR1,I2C_CR1_SWRST);
  //asm("nop");
  //CLEAR_BIT(I2cHandle[ch].Instance->CR1, I2C_CR1_SWRST);
  //asm("nop");
  //SET_BIT(I2cHandle[ch].Instance->CR1, I2C_CR1_PE);
  drvI2CBegin(ch, 400);
}


/**
  * @brief I2C MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - DMA configuration for transmission request by peripheral
  *           - NVIC configuration for DMA interrupt request enable
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef  GPIO_InitStruct;


  if (hi2c->Instance == I2C3)
  {
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /* Enable I2Cx clock */
    __HAL_RCC_I2C3_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/
    /* I2C TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_8;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* I2C RX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_9;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  }
}

/**
  * @brief I2C MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO, DMA and NVIC configuration to their default state
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{

  if (hi2c->Instance == I2C3)
  {
    /*##-1- Reset peripherals ##################################################*/
    __HAL_RCC_I2C3_FORCE_RESET();
    __HAL_RCC_I2C3_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks #################################*/
    /* Configure I2C Tx as alternate function  */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);
    /* Configure I2C Rx as alternate function  */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);
  }
}

