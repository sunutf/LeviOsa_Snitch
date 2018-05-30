/*
 * test_codrone.h
 *
 *  Created on: 2018. 5. 30.
 *      Author: D.ggavy
 */

#ifndef SRC_COMMON_AP_CODRONE_TEST_CODRONE_H_
#define SRC_COMMON_AP_CODRONE_TEST_CODRONE_H_

void codroneFlightStart(void);
void codroneFlightStop(void);


void codronePitchUp(int value);
void codroneRollUp(int value);
void codroneYawUp(int value);
void codroneThrottleUp(int value);



#endif /* SRC_COMMON_AP_CODRONE_TEST_CODRONE_H_ */
