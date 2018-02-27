/*
 * ap.h
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#ifndef AP_H_
#define AP_H_



#include "hw.h"
#include "ap_def.h"
#include "test.h"

#include "qbuffer.h"




typedef struct
{
  uint8_t  ch;
  uint8_t  mode;
  uint32_t on_time;
  uint32_t off_time;
} led_node_t;



typedef struct
{
  uint16_t  down_1ms;
  uint16_t  down_128ms;
} counter_t;




typedef struct
{
  bool     valid;
  bool     update;
  uint16_t voltage;
  uint16_t voltage_warning_ref;
} power_cfg_t;

typedef struct
{
  err_code_t      err_code;
  uint16_t        log_id;
  counter_t       counter;
  power_cfg_t     power;


} ap_t;





extern ap_t *p_ap;




void apInit(void);
void apMain(void);





#endif /* AP_H_ */
