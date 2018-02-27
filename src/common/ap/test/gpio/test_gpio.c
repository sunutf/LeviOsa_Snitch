/*
 * test_gpio.c
 *
 *  Created on: 2017. 10. 30.
 *      Author: opus
 */

#include "test_def.h"

#if _TEST_ENABLE_GPIO == 1

#include "hw.h"
#include "test_gpio.h"

//-- Internal Variables
//
static void testGpioUserInit(void);


//-- External Variables
//


//-- Internal Functions
//


//-- External Functions
//


void testGpioMain(void)
{
  testGpioUserInit();

  while(1)
  {

  }
}




static void testGpioUserInit(void){
  uint8_t i;

  /* User GPIO Pins */
  for(i = _HW_DEF_PIN_GPIO1_1; i <= _HW_DEF_PIN_GPIO6_2; i++){
    gpioPinMode(i, INPUT_PULLDOWN);
  }

  /* LED */
  for(i = _HW_DEF_PIN_LED_USER1; i <= _HW_DEF_PIN_LED_BLUE; i++){
    gpioPinMode(i, OUTPUT);
    gpioPinWrite(i, _DEF_HIGH);
  }

  /* BUTTON + Joystick Button */
  for(i = _HW_DEF_PIN_BUTTON_LEFT; i <= _HW_DEF_PIN_JOY_BUTTON; i++){
    gpioPinMode(i, INPUT_PULLDOWN);
  }

  /* Switch */
  for(i = _HW_DEF_PIN_SW_USER1; i <= _HW_DEF_PIN_SW_USER2; i++){
    gpioPinMode(i, INPUT_PULLDOWN);
  }

  /* 7 SEGMENT */
  for(i = _HW_DEF_PIN_SEVENSEG1; i <= _HW_DEF_PIN_SEVENSEG7; i++){
    gpioPinMode(i, OUTPUT);
    gpioPinWrite(i, _DEF_LOW);
  }

  /* Microphone */
  gpioPinMode(_HW_DEF_PIN_MIC_SIG, INPUT_PULLDOWN);

  /* Buzzer */
  gpioPinMode(_HW_DEF_PIN_BUZZER_SIG, OUTPUT);
  gpioPinWrite(_HW_DEF_PIN_BUZZER_SIG, _DEF_LOW);
}


#endif
