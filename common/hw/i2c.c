/*
 * I2C.c
 *
 *  Created on: 2017. 4. 10.
 *      Author: D.ggavy
 */

#include <stdarg.h>
#include <stdbool.h>

#include "i2c.h"

#ifdef _USE_HW_I2C
#include "driver/drv_i2c.h"
#include "hw.h"



//-- Internal Variables
//
static uint32_t i2c_timeout[I2C_MAX_CH];
static uint32_t i2c_errcount[I2C_MAX_CH];


//-- External Variables
//


//-- Internal Functions
//
void i2cCmdifInit(void);
int  i2cCmdif(int argc, char **argv);


//-- External Functions
//
bool i2cInit(void)
{
  uint32_t i;


  drvI2CInit();


#ifdef _USE_HW_CMDIF_I2C
  i2cCmdifInit();
#endif

  for (i=0; i<I2C_MAX_CH; i++)
  {
    i2c_timeout[i] = 10;
    i2c_errcount[i] = 0;
  }

  return true;
}

err_code_t i2cTransmitByte(uint8_t ch, uint16_t dev_addr, uint8_t data)
{
	return i2cTransmitBytes(ch, dev_addr, &data, 1);
}

err_code_t i2cTransmitBytes(uint8_t ch, uint16_t dev_addr, uint8_t *p_data, uint32_t length)
{
	return drvI2CTransmit(ch, dev_addr, p_data, length, i2c_timeout[ch]);
}

err_code_t i2cReadByte (uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t *p_data)
{
  return i2cReadBytes(ch, dev_addr, reg_addr, p_data, 1);
}

err_code_t i2cReadBytes(uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t *p_data, uint32_t length)
{
  return drvI2CReads(ch, dev_addr, reg_addr, p_data, length, i2c_timeout[ch]);
}

err_code_t i2cWriteByte (uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t data)
{
  return i2cWriteBytes(ch, dev_addr, reg_addr, &data, 1);
}

err_code_t i2cWriteBytes(uint8_t ch, uint16_t dev_addr, uint16_t reg_addr, uint8_t *p_data, uint32_t length)
{
  return drvI2CWrites(ch, dev_addr, reg_addr, p_data, length, i2c_timeout[ch]);
}

void i2cSetTimeout(uint8_t ch, uint32_t timeout)
{
  i2c_timeout[ch] = timeout;
}
uint32_t i2cGetTimeout(uint8_t ch)
{
  return i2c_timeout[ch];
}

void i2cClearErrCount(uint8_t ch)
{
  i2c_errcount[ch] = 0;
}

uint32_t i2cGetErrCount(uint8_t ch)
{
  return i2c_errcount[ch];
}


#ifdef _USE_HW_CMDIF_I2C
void i2cCmdifInit(void)
{
  if (cmdifIsInit() == false)
  {
    cmdifInit();
  }
  cmdifAdd("i2c", i2cCmdif);
}


int i2cCmdif(int argc, char **argv)
{
  bool ret = true;
  uint16_t number;
  uint16_t dev_addr;
  uint16_t reg_addr;
  uint16_t length;

  uint32_t i;
  uint8_t i2c_data[128];
  err_code_t err_code;


  if (argc < 6)
  {
    ret = false;
  }
  else
  {
    number   = (uint16_t) strtoul((const char * ) argv[2], (char **)NULL, (int) 0);
    dev_addr = (uint16_t) strtoul((const char * ) argv[3], (char **)NULL, (int) 0);
    reg_addr = (uint16_t) strtoul((const char * ) argv[4], (char **)NULL, (int) 0);
    length   = (uint16_t) strtoul((const char * ) argv[5], (char **)NULL, (int) 0);


    if(strcmp("read", argv[1])==0)
    {
      for (i=0; i<length; i++)
      {
        err_code = i2cReadByte(number, dev_addr, reg_addr+i, i2c_data);

        if (err_code == OK)
        {
          cmdifPrintf("0x%02X : 0x%02X\n", reg_addr+i, i2c_data[0]);
        }
        else
        {
          cmdifPrintf("err_code : %d\n", err_code);
          break;
        }
      }
    }
    else
    {
      ret = false;
    }
  }


  if (ret == false)
  {
    cmdifPrintf( "i2c read number dev_addr reg_addr length\n");
  }

  return 0;
}

#endif

#endif
