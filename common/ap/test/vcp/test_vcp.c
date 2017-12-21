/*
 * test_vcp.c
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#include "test_def.h"


#if _TEST_ENABLE_VCP == 1


#include "hw.h"
#include "test_vcp.h"



//-- Internal Variables
//
qbuffer_node_t led_buffer;


//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//





void trigger_tick(void *arg)
{
  static uint8_t data = 0;

  qbufferWriteByte(&led_buffer, data);

  data ^= 1;
}

void led_tick(void *arg)
{
  uint8_t data;


  if (qbufferAvailable(&led_buffer) > 0)
  {
    qbufferReadByte(&led_buffer, &data);

    if (data == 1) ledOn(0);
    else           ledOff(0);
  }
}




void testVcpMain(void)
{
  int cnt = 0;
  uint32_t t_time;
  uint32_t t_micros;
  uint32_t t_tx_count;
  uint32_t vcp_tx_bytes;

  swtimer_handle_t h_led_timer;
  swtimer_handle_t h_trigger_timer;



  qbufferCreate(&led_buffer, 100);


  h_led_timer     = swtimerGetHandle();
  h_trigger_timer = swtimerGetHandle();

  swtimerSet(h_led_timer,       1, LOOP_TIME, led_tick,     NULL );
  swtimerSet(h_trigger_timer, 500, LOOP_TIME, trigger_tick, NULL );

  swtimerStart(h_led_timer);
  swtimerStart(h_trigger_timer);



  t_time   = millis();
  t_micros = micros();
  while(1)
  {

    if (micros()-t_micros >= 1000 )
    {
      vcpPrintf("test vcp %d\t, %d\t, err: %d\t, retry: %d\t bytes: %d\r\n", cnt++, (uint32_t)(micros()-t_micros), vcpGetTxErrCount(), vcpGetTxRetryCount(), vcp_tx_bytes);
      t_micros = micros();
    }


    if (millis()-t_time >= 1000 )
    {
      vcp_tx_bytes = vcpGetTxCount()-t_tx_count;
      t_tx_count   = vcpGetTxCount();
      t_time   = millis();
    }


    if (vcpAvailable() > 0)
    {
      printf("Received : %c\r\n", vcpRead());
    }
  }
}


#endif

