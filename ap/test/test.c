/*
 * test_vcp.c
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#include "ap.h"

#include "test.h"
#include "test_def.h"



//-- Internal Variables
//


//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//







void testMain(void)
{
#if _TEST_ENABLE_VCP == 1
  testVcpMain();
#endif

#if _TEST_ENABLE_LED == 1
  testLedMain();
#endif

#if _TEST_ENABLE_UART == 1
  testUartMain();
#endif

#if _TEST_ENABLE_BUTTON == 1
  testButtonMain();
#endif

#if _TEST_ENABLE_DXL == 1
  testDxlMain();
#endif
}


