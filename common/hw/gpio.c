/*
 * gpio.c
 *
 *  Created on: 2017. 8. 11.
 *      Author: baram
 */

#include <stdarg.h>
#include <stdbool.h>

#include "gpio.h"

#ifdef _USE_HW_GPIO
#include "driver/drv_gpio.h"
#include "hw.h"


//-- Internal Variables
//

//-- External Variables
//

//-- Internal Functions
//
#ifdef _USE_HW_CMDIF_GPIO
void gpioCmdifInit(void);
int gpioCmdif(int argc, char **argv);
#endif

//-- External Functions
//

bool gpioInit(void)
{
  drvGpioInit();

#ifdef _USE_HW_CMDIF_GPIO
  gpioCmdifInit();
#endif

  return true;
}

void gpioPinMode(uint8_t ch, uint8_t mode)
{
  drvGpioPinMode(ch, mode);
}

void gpioPinWrite(uint8_t ch, uint8_t value)
{
  drvGpioPinWrite(ch, value);
}

int gpioPinRead(uint8_t ch)
{
  return drvGpioPinRead(ch);
}

#ifdef _USE_HW_CMDIF_GPIO
void gpioCmdifInit(void)
{
  cmdifAdd("gpio", gpioCmdif);
}

int gpioCmdif(int argc, char **argv)
{
  bool ret = true;
  uint8_t number = 0;
  uint32_t option = 0;

  if (argc < 4)
  {
    ret = false;
  }
  else
  {
    number = (uint8_t) strtoul((const char *) argv[2], (char **) NULL, (int) 0);
    option = (uint32_t) strtoul((const char *) argv[3], (char **) NULL, (int) 0);

    if (strcmp("mode", argv[1]) == 0)
    {
      gpioPinMode(number, option);
    }
    else if (strcmp("get", argv[1]) == 0)
    {
      while (cmdifRxAvailable() == 0)
      {
        cmdifPrintf("Pin %d : %d, delay : %d\r\n", number, gpioPinRead(number), option);
        delay(option);
      }
    }
    else if (strcmp("set", argv[1]) == 0)
    {
      gpioPinWrite(number, option);
    }
    else
    {
      ret = false;
    }
  }

  if (ret == false)
  {
    cmdifPrintf("\n");
    cmdifPrintf("gpio get  number [interval (ms)]\n");
    cmdifPrintf("gpio set  number [bit]\n");
    cmdifPrintf("gpio mode number [mode]\n");
    cmdifPrintf("                    0 : INPUT, 1 : INPUT_PULLUP, 2 : INPUT_PULLDOWN\n");
    cmdifPrintf("                    3 : OUTPUT, 4 : OUTPUT_PULLUP, 5 : OUTPUT_PULLDOWN\n");
  }
  return 0;
}
#endif

#endif
