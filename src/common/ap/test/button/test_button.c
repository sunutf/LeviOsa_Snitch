/*
 * test_button.c
 *
 *  Created on: 2017. 4. 6.
 *      Author: D.ggavy
 */

#include "test_def.h"


#if _TEST_ENABLE_BUTTON == 1


#include "hw.h"
#include "test_button.h"



//-- Internal Variables
//



//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//





void testButtonMain(void)
{

  while(1)
  {
    ledOn(0);
    if(buttonIsPressed(0))
    {
     delay(50);
     if(buttonIsPressed(0)) break;
    }
  }
  while(1)
  {
    ledToggle(0);
    delay(500);
  }
}


#endif



