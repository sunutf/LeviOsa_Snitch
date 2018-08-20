/*
 * ap.cpp
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */





#include "ap.h"
#include "hw.h"




//-- Internal Variables
//
const volatile  __attribute__((section(".version"))) uint8_t fw_version_str[32] = "V171012R4";

#define DEBUG
static ap_t ap_control;

ap_t *p_ap = &ap_control;










//-- External Variables
//


//-- Internal Functions



//-- External Functions





void apInit(void)
{
//  p_ap->err_code = OK;
//
//
//  p_ap->counter.down_1ms  = 0;
//  p_ap->counter.down_128ms= 0;
//
//  p_ap->power.valid   = false;
//  p_ap->power.update  = false;
//  p_ap->power.voltage = 0;
//  p_ap->power.voltage_warning_ref = 1000; // 11.00V
  telloInit();

}

void apMain(void)
{

#ifdef DEBUG
   cmdifBegin(_DEF_UART1, 115200);

  while(1)
  {
    cmdifMain();
  }
#else
  testMain();
#endif
}



