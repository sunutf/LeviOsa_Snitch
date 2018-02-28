// drv_mux.c



#include <stdarg.h>
#include <stdbool.h>

#include "hw.h"
#include "drv_led.h"





//-- Internal Variables
//




//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//

#define LOW 0
#define HIGH 1

typedef struct
{
  GPIO_TypeDef       *port;
  uint16_t            pin;
}drv_mux_gpio_t;


typedef struct
{
  GPIO_PinState       pin_state;
  drv_mux_gpio_t      gpio;
}drv_mux_ch_t;

typedef struct
{
	drv_mux_ch_t				drv_mux_ch_tbl[4]; // {EN,Id0,Id1,Id2}
}drv_mux_id_t;

drv_mux_id_t drv_mux_tbl[_HW_DEF_MUX_CH_MAX];



bool drvMuxInit(void)
{
  uint32_t i, j;
  GPIO_InitTypeDef  GPIO_InitStruct;

  /*For SENSORXEL
  drv_mux_tbl[0].drv_mux_ch_tbl[0].gpio.port = GPIOC;
  drv_mux_tbl[0].drv_mux_ch_tbl[0].gpio.pin  = GPIO_PIN_13;
  drv_mux_tbl[0].drv_mux_ch_tbl[1].gpio.port = GPIOB;
	drv_mux_tbl[0].drv_mux_ch_tbl[1].gpio.pin  = GPIO_PIN_15;
	drv_mux_tbl[0].drv_mux_ch_tbl[2].gpio.port = GPIOA;
	drv_mux_tbl[0].drv_mux_ch_tbl[2].gpio.pin  = GPIO_PIN_11;
	drv_mux_tbl[0].drv_mux_ch_tbl[3].gpio.port = GPIOA;
	drv_mux_tbl[0].drv_mux_ch_tbl[3].gpio.pin  = GPIO_PIN_12;

	drv_mux_tbl[1].drv_mux_ch_tbl[0].gpio.port = GPIOB;
	drv_mux_tbl[1].drv_mux_ch_tbl[0].gpio.pin  = GPIO_PIN_10;
	drv_mux_tbl[1].drv_mux_ch_tbl[1].gpio.port = GPIOA;
	drv_mux_tbl[1].drv_mux_ch_tbl[1].gpio.pin  = GPIO_PIN_15;
	drv_mux_tbl[1].drv_mux_ch_tbl[2].gpio.port = GPIOB;
	drv_mux_tbl[1].drv_mux_ch_tbl[2].gpio.pin  = GPIO_PIN_6;
	drv_mux_tbl[1].drv_mux_ch_tbl[3].gpio.port = GPIOB;
	drv_mux_tbl[1].drv_mux_ch_tbl[3].gpio.pin  = GPIO_PIN_7;

	drv_mux_tbl[2].drv_mux_ch_tbl[0].gpio.port = GPIOB;
	drv_mux_tbl[2].drv_mux_ch_tbl[0].gpio.pin  = GPIO_PIN_11;
	drv_mux_tbl[2].drv_mux_ch_tbl[1].gpio.port = GPIOB;
	drv_mux_tbl[2].drv_mux_ch_tbl[1].gpio.pin  = GPIO_PIN_12;
	drv_mux_tbl[2].drv_mux_ch_tbl[2].gpio.port = GPIOB;
	drv_mux_tbl[2].drv_mux_ch_tbl[2].gpio.pin  = GPIO_PIN_13;
	drv_mux_tbl[2].drv_mux_ch_tbl[3].gpio.port = GPIOB;
	drv_mux_tbl[2].drv_mux_ch_tbl[3].gpio.pin  = GPIO_PIN_14;

	for (i=0; i<_HW_DEF_MUX_CH_MAX; i++)
  {
		for(j=0; j<4; j++)
		{
			if (drv_mux_tbl[i].drv_mux_ch_tbl[j].gpio.port != NULL)
			{
				GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull  = GPIO_PULLUP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
				GPIO_InitStruct.Pin   = drv_mux_tbl[i].drv_mux_ch_tbl[j].gpio.pin;
				HAL_GPIO_Init(drv_mux_tbl[i].drv_mux_ch_tbl[j].gpio.port, &GPIO_InitStruct);
			}
		}
  }
	*/

  drv_mux_tbl[0].drv_mux_ch_tbl[0].gpio.port = GPIOD;
	drv_mux_tbl[0].drv_mux_ch_tbl[0].gpio.pin  = GPIO_PIN_3;
	drv_mux_tbl[0].drv_mux_ch_tbl[1].gpio.port = GPIOD;
	drv_mux_tbl[0].drv_mux_ch_tbl[1].gpio.pin  = GPIO_PIN_4;
	drv_mux_tbl[0].drv_mux_ch_tbl[2].gpio.port = GPIOD;
	drv_mux_tbl[0].drv_mux_ch_tbl[2].gpio.pin  = GPIO_PIN_5;
	drv_mux_tbl[0].drv_mux_ch_tbl[3].gpio.port = GPIOD;
	drv_mux_tbl[0].drv_mux_ch_tbl[3].gpio.pin  = GPIO_PIN_6;

	for (i=0; i<_HW_DEF_MUX_CH_MAX; i++)
	{
		for(j=0; j<4; j++)
		{
			if (drv_mux_tbl[i].drv_mux_ch_tbl[j].gpio.port != NULL)
			{
				GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull  = GPIO_PULLUP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
				GPIO_InitStruct.Pin   = drv_mux_tbl[i].drv_mux_ch_tbl[j].gpio.pin;
				HAL_GPIO_Init(drv_mux_tbl[i].drv_mux_ch_tbl[j].gpio.port, &GPIO_InitStruct);
			}
		}
	}

  return true;
}

//LOW ACTIVE
void drvMuxEnId(uint8_t id, bool state)
{
	if(state) 	HAL_GPIO_WritePin(drv_mux_tbl[id].drv_mux_ch_tbl[0].gpio.port, drv_mux_tbl[id].drv_mux_ch_tbl[0].gpio.pin, GPIO_PIN_RESET);
	else				HAL_GPIO_WritePin(drv_mux_tbl[id].drv_mux_ch_tbl[0].gpio.port, drv_mux_tbl[id].drv_mux_ch_tbl[0].gpio.pin, GPIO_PIN_SET);

	drv_mux_tbl[id].drv_mux_ch_tbl[0].pin_state = HAL_GPIO_ReadPin(drv_mux_tbl[id].drv_mux_ch_tbl[0].gpio.port, drv_mux_tbl[id].drv_mux_ch_tbl[0].gpio.pin);
}

bool drvMuxSetChtoId(uint8_t id, uint8_t ch)
{
	uint8_t i;
	uint8_t ret;
	uint8_t mux_state;

	mux_state = drv_mux_tbl[id].drv_mux_ch_tbl[0].pin_state;

	if(LOW == mux_state)
	{
		if(ch<8)
		{
			for(i=1; i<4; i++)
			{
				ret = (ch>>(i-1))&0x01;
				if(ret) HAL_GPIO_WritePin(drv_mux_tbl[id].drv_mux_ch_tbl[i].gpio.port, drv_mux_tbl[id].drv_mux_ch_tbl[i].gpio.pin, GPIO_PIN_SET);
				else		HAL_GPIO_WritePin(drv_mux_tbl[id].drv_mux_ch_tbl[i].gpio.port, drv_mux_tbl[id].drv_mux_ch_tbl[i].gpio.pin, GPIO_PIN_RESET);
			}
			return true;
		}
	}
	else return false; // over the max num of ch or didn't turn on the mux before setting id&ch value.
}

uint8_t drvMuxGetChfromId(uint8_t id)
{
	uint8_t ret_ch = 0;
	uint8_t i;
	uint8_t mux_state;

	mux_state = drv_mux_tbl[id].drv_mux_ch_tbl[0].pin_state;

	if(LOW == mux_state)
	{
		for(i=1; i<4;i++)
		{
			ret_ch += (HAL_GPIO_ReadPin(drv_mux_tbl[id].drv_mux_ch_tbl[i].gpio.port, drv_mux_tbl[id].drv_mux_ch_tbl[i].gpio.pin)<<(i-1));
		}
		return ret_ch;
	}
	else	return -1; //didn't turn on the mux before getting id&ch value.
}
