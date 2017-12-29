/*
 * tca9548a.c
 *
 *  Created on: 2017. 12. 12.
 *      Author: D.ggavy
 */

#include <stdarg.h>
#include <stdbool.h>


#include "tca9548a.h"

#ifdef _USE_HW_TCA9548A




#ifdef _USE_HW_CMDIF_TCA9548A
void tca9548aCmdifInit(void);
int  tca9548aCmdif(int argc, char **argv);
#endif

static void writeReg(uint8_t i2c_ch, uint8_t id, uint8_t ch);

bool tca9548aInit(void)
{
#ifdef _USE_HW_CMDIF_TCA9548A
  tca9548aCmdifInit();
#endif
  return true;
}

bool tcaSelect(uint8_t i2c_ch, uint8_t id, uint8_t ch)
{
  if (ch > 8) return false;

  if (ch == 8)  writeReg(i2c_ch, id, 0xFF);
  else          writeReg(i2c_ch, id, 1<<ch);
  return true;

}

void writeReg(uint8_t i2c_ch, uint8_t id,  uint8_t ch)
{
	i2cTransmitByte(i2c_ch, TCAADDR|id, ch);
}

#ifdef _USE_HW_CMDIF_TCA9548A
void tca9548aCmdifInit(void)
{
  cmdifAdd("tca9548a", tca9548aCmdif);
}

int tca9548aCmdif(int argc, char **argv)
{
  bool ret = true;


  if(argc == 5 && strcmp("open", argv[4]) == 0)
  {
	  uint8_t i2c_ch = (uint8_t) strtoul((const char * ) argv[1], (char **)NULL, (int) 0);
	  uint8_t id = (uint8_t) strtoul((const char * ) argv[2], (char **)NULL, (int) 0);
	  uint8_t ch = (uint8_t) strtoul((const char * ) argv[3], (char **)NULL, (int) 0);


    if ((i2c_ch-1) < I2C_MAX_CH)
    {
			if((id*ch == 0))
			{
				cmdifPrintf("fail : id or ch error \n");
				return 0;
			}

			i2c_ch--;
			id--;
			ch--;

      ret = tcaSelect(i2c_ch, id, ch);
      if (ret == false)
      {
        cmdifPrintf("fail : tca9548a num error\n");
        return 0;
      }
    }
    else
    {
      cmdifPrintf("channel range over \n");
      return -1;
    }

    cmdifPrintf("Open ID : %d, Ch : %d \n", id, ch);
  }
  else
  {
    ret = false;
  }

  if(argc == 4 && strcmp("demo", argv[1]) == 0)
  {
  	uint8_t ch = (uint8_t) strtoul((const char * ) argv[2], (char **)NULL, (int) 0);
  	uint8_t gain = (uint8_t) strtoul((const char * ) argv[3], (char **)NULL, (int) 0);

  	switch(ch)
  	{
			case 0:
				testMuxMain0(gain);
				break;

			case 1:
				testMuxMain1(gain);
				break;

			case 2:
				testMuxMain2(gain);
				break;

			case 3:
				testMuxMain3(gain);
				break;
  	}

  }


  if (ret == false)
  {
    cmdifPrintf( "read fail\n");
  }

  return 0;
}
#endif

#endif
