/*
 * test_nfc.c
 *
 *  Created on: 2017. 3. 27.
 *      Author: jhseon
 */

#include "test_def.h"
#include <stdbool.h>
#include <stdarg.h>

#if _TEST_ENABLE_NFC == 1


#include "hw.h"
#include "nfc/nfc.h"
#include "test_nfc.h"



//-- Internal Variables
//


//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//


void testNFCMain(void)
{
  uint8_t    uart_ch = _DEF_UART1;
  uint32_t   nfc_version;
  nfc_card_t nfc_card;
  bool       ret;
  uint8_t    i;

  uartOpen(uart_ch, 115200);
  uartWaitForEnable(uart_ch, 2000);

  nfcBegin(_DEF_UART2, 115200);



  if (nfcFind() == true)
  {
    nfcSetConfig(NFC_NORMAL);

    nfc_version = nfcGetFirmwareVersion();
    uartPrintf(uart_ch, "Found chip PN5 %X\n", (nfc_version>>24) & 0xFF);
    uartPrintf(uart_ch, "Firmware ver.  %X\n", (nfc_version>>16) & 0xFF);
    uartPrintf(uart_ch, ".%X\n",               (nfc_version>> 8) & 0xFF);


    for (i=0; i<10; i++)
    {
      ledToggle(0);
      delay(50);
    }

  }
  else
  {
    uartPrintf(uart_ch, "nfc not found\r\n");
    while(1)
    {
      ledToggle(0);
      delay(100);
    }
  }


  while(1)
  {
    ret = nfcDetectCard(&nfc_card);

    if (ret == true)
    {
      ledToggle(0);

      uartPrintf(uart_ch, "Found a card!\r\n");
      uartPrintf(uart_ch, "UID Length: %d bytes \r\n", nfc_card.uid_length);
      uartPrintf(uart_ch, "UID value: ");

      for (i=0; i < nfc_card.uid_length; i++)
      {
        uartPrintf(uart_ch, " 0x%X", nfc_card.uid[i]);
      }
      uartPrintf(uart_ch, " \n");
    }
  }

}


#endif

