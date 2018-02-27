/*
 * vcp.h
 *
 *  Created on: 2017. 2. 13.
 *      Author: baram
 */

#ifndef VCP_H_
#define VCP_H_



#ifdef __cplusplus
 extern "C" {
#endif


#include "hw_def.h"

#ifdef _USE_HW_VCP

#include "bsp.h"

bool     vcpInit(void);
bool     vcpFlush(void);
uint32_t vcpAvailable(void);
void     vcpPutch(uint8_t ch);
uint8_t  vcpGetch(void);
int32_t  vcpWrite(uint8_t *p_data, uint32_t length);
uint8_t  vcpRead(void);
uint32_t vcpGetTxErrCount(void);
uint32_t vcpGetTxCount(void);
uint32_t vcpGetTxRetryCount(void);
bool     vcpIsConnected(void);

int32_t  vcpPrintf( const char *fmt, ...);

#endif

#ifdef __cplusplus
}
#endif

#endif /* PRJ_SDK_HAL_LED_H_ */
