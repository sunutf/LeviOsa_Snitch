/*
 * test_uart.c
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#include "test_def.h"


#if _TEST_ENABLE_UART == 1


#include "hw.h"
#include "test_uart.h"



//-- Internal Variables
//
qbuffer_node_t led_buffer;


//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//





void trigger_tick_uart(void *arg)
{
  static uint8_t data = 0;

  qbufferWriteByte(&led_buffer, data);

  data ^= 1;
}

void led_tick_uart(void *arg)
{
  uint8_t data;


  if (qbufferAvailable(&led_buffer) > 0)
  {
    qbufferReadByte(&led_buffer, &data);

    if (data == 1) ledOn(0);
    else           ledOff(0);
  }
}




void testUartMain(void)
{
  int cnt = 0;
  uint32_t t_time;
  uint32_t t_micros;
  uint32_t t_tx_count = 0;
  uint32_t uart_tx_bytes = 0;
  uint8_t  uart_ch = _DEF_UART1;


  swtimer_handle_t h_led_timer;
  swtimer_handle_t h_trigger_timer;



  qbufferCreate(&led_buffer, 100);


  h_led_timer     = swtimerGetHandle();
  h_trigger_timer = swtimerGetHandle();

  swtimerSet(h_led_timer,       1, LOOP_TIME, led_tick_uart,     NULL );
  swtimerSet(h_trigger_timer, 500, LOOP_TIME, trigger_tick_uart, NULL );

  swtimerStart(h_led_timer);
  swtimerStart(h_trigger_timer);


  uartOpen(uart_ch, 115200);


  t_time   = millis();
  t_micros = micros();
  while(1)
  {

    if (micros()-t_micros >= 500000 )
    {

      uartPrintf(uart_ch,"test uart %d\t, %d\t, err: %d\t, retry: %d\t bytes: %d\r\n", cnt++, (uint32_t)(micros()-t_micros), uartGetTxErrCount(uart_ch), uartGetTxRetryCount(uart_ch), uart_tx_bytes);
      t_micros = micros();
    }


    if (millis()-t_time >= 1000 )
    {
      uart_tx_bytes = uartGetTxCount(uart_ch)-t_tx_count;
      t_tx_count    = uartGetTxCount(uart_ch);
      t_time   = millis();
    }


    if (uartAvailable(uart_ch) > 0)
    {
      uartPrintf(uart_ch, "Received DMA : %c\r\n", uartRead(uart_ch));
    }
  }
}


#endif

