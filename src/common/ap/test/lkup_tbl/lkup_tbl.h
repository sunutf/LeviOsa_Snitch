/*
 * lkup_tbl.h
 *
 *  Created on: 2018. 3. 5.
 *      Author: D.ggavy
 */

#ifndef SRC_COMMON_AP_TEST_LKUP_TBL_LKUP_TBL_H_
#define SRC_COMMON_AP_TEST_LKUP_TBL_LKUP_TBL_H_

#ifdef __cplusplus
 extern "C" {
#endif

uint32_t lkup_tblSearch(float lux_value);
uint8_t lkup_tblInterpolation(float lux_value, uint32_t order_of_step);
uint32_t lkup_tblGetDist(float lux_value);


#endif /* SRC_COMMON_AP_TEST_LKUP_TBL_LKUP_TBL_H_ */

