/*
 * test_codrone.cpp
 *
 *  Created on: 2018. 5. 30.
 *      Author: D.ggavy
 */

#include "codrone/CoDrone.h"

void codroneBegin(void);

void codroneBegin(void)
{
	CoDrone.begin(115200); // sets up the connection to the drone using the bluetooth module at 115200bps (bits per second)

	CoDrone.AutoConnect(NearbyDrone);  // finds and connects to a drone that is near by

	CoDrone.DroneModeChange(Flight);  // Changes the drone so that it is now in flght mode

}

void codronePitchUp(int value)
{
	if (PAIRING != true) codroneBegin();

	// PAIRING is set to true in AutoConnect if they connect together
	if (PAIRING == true) // Check to see that we are paired before trying to fly
	{
		PITCH = value;                         // set PITCH to 100 (tilt forward)
		CoDrone.Control();                   // send the pitch values to the drone
	}
}

void codroneRollUp(int value)
{
	if (PAIRING != true) codroneBegin();

	// PAIRING is set to true in AutoConnect if they connect together
	if (PAIRING == true) // Check to see that we are paired before trying to fly
	{
		ROLL = value;                          // set ROLL to 100 (tilt right)
		CoDrone.Control();                   // send the roll values to the drone
	}
}

void codroneYawUp(int value)
{
	if (PAIRING != true) codroneBegin();

	// PAIRING is set to true in AutoConnect if they connect together
	if (PAIRING == true) // Check to see that we are paired before trying to fly
	{
		YAW = value;                           // set YAW to 100 (turn right)
		CoDrone.Control();                   // send the yaw values to the drone
	}
}

void codroneThrottleUp(int value)
{
	if (PAIRING != true) codroneBegin();

	// PAIRING is set to true in AutoConnect if they connect together
	if (PAIRING == true) // Check to see that we are paired before trying to fly
	{
		THROTTLE  = value;                     // set THROTTLE to 100 (full),
		// note that we do not need to call TakeOff since we are starting the throttle ourselves,
		// but to do so the throttle must be high (recommend 50~75)

		CoDrone.Control();                  // send the throttle values to the drone
	}
}

void codroneFlightStart(void)
{
	if (PAIRING != true) codroneBegin();

	if (PAIRING == true) // Check to see that we are paired before trying to fly
	{
		CoDrone.FlightEvent(TakeOff);        // have the drone take off

		delay(2000);                         // fly for 2 seconds (2000 milliseconds)
	}
}

void codroneFlightStop(void)
{
	if (PAIRING != true) codroneBegin();

	if (PAIRING == true) // Check to see that we are paired before trying to fly
	{
		CoDrone.FlightEvent(Landing);        // have the drone take off

		delay(2000);                         // fly for 2 seconds (2000 milliseconds)
	}
}
