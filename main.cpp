/*
 * main.cpp
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */


#include "main.h"
//#include "rtos.h"


//-- Internal Variables
//



//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//




#ifndef _USE_HW_RTOS
int main(void)
{
	bspInit();
	hwInit();
	apInit();
	apMain();

	return 0;
}
#else
static void threadMain(void const *argument);



int main(void)
{
  bspInit();
  hwInit();
  apInit();

  osThreadDef(threadMain, threadMain, osPriorityNormal, 0, _HW_DEF_RTOS_MEM_SIZE(6*1024));
  osThreadCreate(osThread(threadMain), NULL);


  osKernelStart();

  return 0;
}

static void threadMain(void const *argument)
{
  (void) argument;


  apMain();
}
#endif

