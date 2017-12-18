/*
 * led.c
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */



#include <stdarg.h>
#include <stdbool.h>

#include "led.h"

#ifdef _USE_HW_LED
#include "driver/drv_led.h"
#include "hw.h"




//-- Internal Variables
//
void ledCmdifInit(void);
int  ledCmdif(int argc, char **argv);


//-- External Variables
//


//-- Internal Functions
//



//-- External Functions
//




bool ledInit(void)
{
  uint8_t i;


  drvLedInit();


  for (i=0; i<LED_MAX_CH; i++)
  {
    ledOff(i);
  }

#ifdef _USE_HW_CMDIF_LED
  ledCmdifInit();
#endif

  return true;
}

void ledOn(uint8_t ch)
{
  drvLedSetState(ch, true);
}

void ledOff(uint8_t ch)
{
  drvLedSetState(ch, false);
}

void ledToggle(uint8_t ch)
{
  bool led_state;


  led_state = drvLedGetState(ch);

  drvLedSetState(ch, !led_state);
}

void ledOnAll(void)
{
  uint16_t i;


  for (i=0; i<LED_MAX_CH; i++)
  {
    ledOn(i);
  }
}

void ledOffAll(void)
{
  uint16_t i;


  for (i=0; i<LED_MAX_CH; i++)
  {
    ledOff(i);
  }
}





#ifdef _USE_HW_CMDIF_LED
void ledCmdifInit(void)
{
  if (cmdifIsInit() == false)
  {
    cmdifInit();
  }
  cmdifAdd("led", ledCmdif);
}

int ledCmdif(int argc, char **argv)
{
  bool ret = true;
  uint8_t number;


  if (argc < 3)
  {
    ret = false;
  }
  else
  {
    number = (uint8_t) strtoul((const char * ) argv[2], (char **)NULL, (int) 0);

    if(strcmp("on", argv[1]) == 0)
    {
      ledOn(number);
    }
    else if(strcmp("off", argv[1])==0)
    {
      ledOff(number);
    }
    else if(strcmp("toggle", argv[1])==0)
    {
      ledToggle(number);
    }
    else if(strcmp("demo", argv[1])==0)
    {
      while(cmdifRxAvailable() == 0)
      {
        ledToggle(number);
        delay(200);
        cmdifPrintf("led toggle %d\n", number);
      }
    }
    else
    {
      ret = false;
    }
  }


  if (ret == false)
  {
    cmdifPrintf( "led [cmd] number ...\n");
    cmdifPrintf( "\t on/off/toggle/demo \n");
  }

  return 0;
}
#endif

#endif
