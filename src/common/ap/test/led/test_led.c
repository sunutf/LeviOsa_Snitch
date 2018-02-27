/*
 * test_led.c
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#include "test_def.h"


#if _TEST_ENABLE_LED == 1


#include "hw.h"
#include "test_led.h"



//-- Internal Variables
//



//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//





void testLedMain(void)
{
  while(1)
  {
    ledToggle(0);
    delay(500);
  }
}


#endif

