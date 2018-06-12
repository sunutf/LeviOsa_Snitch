/*
 * CoDrone1.h
 *
 *  Created on: 2018. 5. 30.
 *      Author: D.ggavy
 */

#ifndef SRC_COMMON_AP_CODRONE_CODRONE_H_
#define SRC_COMMON_AP_CODRONE_CODRONE_H_



/*
  CoDrone.h - CoDrone library
  Copyright (C) 2014 RoboLink.  All rights reserved.
  LastUpdate : 2018-01-30
*/

#include "test_def.h"
#include "hw.h"


#ifndef CoDrone_h
#define CoDrone_h


///Snitch V2///
#define DEBUG_SERIAL  _DEF_UART1
#define DRONE_SERIAL  _DEF_UART3
#define BT_SERIAL     _DEF_UART2
/***********************************************************************/

# define JOY_UP_LIMIT          1023 - 100
# define JOY_UP_RETURN_LIMIT   512	+ 100
# define JOY_DOWN_LIMIT        0 	+ 100
# define JOY_DOWN_RETURN_LIMIT 512 	- 100

/***********************************************************************/
//////////////////////////typedef///////////////////////////////////////
/***********************************************************************/

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;
typedef uint32_t u32;
//typedef uint16_t u16;
typedef uint8_t u8;

/***********************************************************************/
////////////////////////Serial Select////////////////////////////////////
/***********************************************************************/
#if defined(UBRRH) || defined(UBRR0H)
#define FIND_HWSERIAL0
#endif

#if defined(UBRR1H)
#define FIND_HWSERIAL1
#endif

#if defined (FIND_HWSERIAL1)	//Serial Other Setting	- two serial
#define DRONE_SERIAL 	Serial1		//drone serial
#define DEBUG_SERIAL    Serial		//debug serial1

//#else							//Serial Smart Setting	- one serial
//#define DRONE_SERIAL 	Serial		//drone serial
//#define DEBUG_SERIAL    Serial1		//debug serial1

#endif

/***********************************************************************/
////////////////////////////HEADER///////////////////////////////////////
/***********************************************************************/
//START CODE
#define START1    			0x0A
#define START2   			0x55

/***********************************************************************/

//serial buffer
#if defined (FIND_HWSERIAL1)	// Atmega128
#define MAX_PACKET_LENGTH 	200

#else							// Smart Setting
#define MAX_PACKET_LENGTH 	40
#endif

/***********************************************************************/

//#define	SEND_CHECK_TIME    	3
#define	SEND_CHECK_TIME    		50

/***********************************************************************/

#define ROLL						CoDrone.roll
#define PITCH						CoDrone.pitch
#define YAW							CoDrone.yaw
#define THROTTLE					CoDrone.throttle

#define STATE						CoDrone.state
#define SEND_INTERVAL				CoDrone.SendInterval
#define ANALOG_OFFSET				CoDrone.analogOffset
#define BATTERY						CoDrone.battery
#define RSSI						CoDrone.rssi

#define AttitudeROLL				CoDrone.attitudeRoll
#define AttitudePITCH				CoDrone.attitudePitch
#define AttitudeYAW					CoDrone.attitudeYaw

/***********************************************************************/

#define DiscoverStop  			cType_LinkDiscoverStop
#define DiscoverStart  			cType_LinkDiscoverStart

#define PollingStop				cType_LinkRssiPollingStop
#define PollingStart			cType_LinkRssiPollingStart

#define	PAIRING					CoDrone.pairing

#define LinkModeMute 			LinkBroadcast_Mute
#define LinkModeActive			LinkBroadcast_Active
#define LinkModePassive 		LinkBroadcast_Passive

#define	NearbyDrone    			1
#define	ConnectedDrone  		2
#define AddressInputDrone 		3

//eeprom address
#define	EEP_AddressCheck   		10
#define	EEP_AddressFirst  		11
#define	EEP_AddressEnd  		15

/////////////////////////////////////////////////////////////////////////

#define FREE_PLAY				0
#define TEAM_RED				1
#define TEAM_BLUE				2
#define TEAM_GREEN				3
#define TEAM_YELLOW				4

#define MAX_ENERGY				8
/**********************	IR DATA****************************************/

#define FREE_MISSILE		0xaa01
#define RED_MISSILE			0xbb01
#define BLUE_MISSILE		0xcc01
#define GREEN_MISSILE		0xdd01
#define YELLOW_MISSILE		0xee01

/***********************************************************************/

#define Flight 					dMode_Flight
#define FlightNoGuard			dMode_FlightNoGuard,
#define FlightFPV				dMode_FlightFPV
#define Drive 				 	dMode_Drive
#define DriveFPV				dMode_DriveFPV

#define Absolute 				cSet_Absolute
#define Relative		 		cSet_Relative

#define TakeOff 				fEvent_TakeOff
#define FlipFront				fEvent_FlipFront
#define FlipRear				fEvent_FlipRear
#define FlipLeft				fEvent_flipLeft
#define FlipRight				fEvent_FlipRight
#define Stop					fEvent_Stop
#define Landing					fEvent_Landing
#define TurnOver				fEvent_TurnOver
#define Shot					fEvent_Shot
#define UnderAttack				fEvent_UnderAttack
#define Square					fEvent_Square
#define CircleLeft				fEvent_CircleLeft
#define CircleRight				fEvent_CircleRight
#define Rotate180				fEvent_Rotate180

#define RollIncrease			trim_RollIncrease
#define RollDecrease			trim_RollDecrease
#define PitchIncrease			trim_PitchIncrease
#define PitchDecrease			trim_PitchDecrease
#define YawIncrease				trim_YawIncrease
#define YawDecrease				trim_YawDecrease
#define ThrottleIncrease		trim_ThrottleIncrease
#define ThrottleDecrease		trim_ThrottleDecrease

// 2018, 1, 22 added
#define LEFT 					direction_left
#define FORWARD 				direction_forward
#define RIGHT 					direction_right
#define BACKWARD				direction_backward
#define UP  					direction_up
#define DOWN 					direction_down

// 2018, 3, 12 added
#define ZIGZAG 					Seq_zigzag
#define SWAY 					Seq_sway
#define SQUARE 					Seq_square
#define CIRCLE 					Seq_circle
#define SPIRAL 					Seq_spiral
#define TRIANGLE 				Seq_triangle
#define HOP 					Seq_hop

enum Direction
{
	direction_none = 0,
	direction_left,
	direction_forward,
	direction_right,
	direction_backward,
	direction_up,
	direction_down,
	direction_EndOfType
};

enum Sequence
{
	Seq_none = 0,
	Seq_zigzag,
	Seq_sway,
	Seq_square,
	Seq_circle,
	Seq_spiral,
	Seq_triangle,
	Seq_hop,
	Seq_EndOfType,
};
enum Angle
{
	ANGLE_30 = 30,
	ANGLE_45 = 45,
	ANGLE_60 = 60,
	ANGLE_90 = 90,
	ANGLE_120 = 120,
	ANGLE_135 = 135,
	ANGLE_150 = 150,
	ANGLE_180 = 180,
	ANGLE_210 = 210,
	ANGLE_225 = 225,
	ANGLE_240 = 240,
	ANGLE_270 = 270,
	ANGLE_300 = 300,
	ANGLE_315 = 315,
	ANGLE_330 = 330
};
//
typedef struct gyrodata
{
	int roll;
	int pitch;
	int yaw;
}gyrodata;

typedef struct acceldata
{
	int x;
	int y;
	int z;
}acceldata;

//angle
typedef struct angledata
{
	int roll;
	int pitch;
	int yaw;
}angledata;

typedef struct trimdata
{
	int roll;
	int pitch;
	int yaw;
	int throttle;
}trimdata;

typedef struct optdata
{
	int x;
	int y;
}optdata;







/***********************************************************************/
/////////////////////////LINK MODULE/////////////////////////////////////
/***********************************************************************/
enum ModeLink
{
	linkMode_None = 0,	 	 	///< 쩐첩�쩍
	linkMode_Boot,	 	 	 	///< 쨘횓횈횄
	linkMode_Ready,	 		 	///< 쨈챘짹창(쩔짭째찼 �체)
	linkMode_Connecting,	 	///< �책횆징 쩔짭째찼 횁횩
	linkMode_Connected,	 	 	///< �책횆징 쩔짭째찼 쩔횕쨌찼
	linkMode_Disconnecting,		///< �책횆징 쩔짭째찼 횉횠횁짝 횁횩
	linkMode_ReadyToReset,		///< 쨍짰쩌횂 쨈챘짹창(1횄횎 쨉횣쩔징 �책횆징 쨍짰쩌횂)
	linkMode_EndOfType
};

enum ModeLinkBroadcast
{
	LinkBroadcast_None = 0, 	///< 쩐첩�쩍
	LinkBroadcast_Mute, 		///< LINK 쨍챨쨉창 쨉짜�횑횇횒 쩌횤쩍횇 횁횩쨈횥 . 쩐횈쨉횓�횑쨀챘 횈횩쩔첸쩐챤 쨈횢쩔챤쨌횓쨉책
	LinkBroadcast_Active, 		///< 횈채횈짰쨌횖 쩔짭째찼 쨍챨쨉책 . 쨍챨쨉책 �체횊짱 쨍횧쩌쩌횁철 �체쩌횤
	LinkBroadcast_Passive, 		///< 횈채횈짰쨌횖 쩔짭째찼 쨍챨쨉책 . 쨍챨쨉책 �체횊짱 쨍횧쩌쩌횁철 �체쩌횤횉횕횁철 쩐횎�쩍
	LinkBroadcast_EndOfType
};

enum EventLink
{
	linkEvent_None = 0,								///< 쩐첩�쩍

	linkEvent_SystemReset,							///< 쩍횄쩍쨘횇횤 쨍짰쩌횂

	linkEvent_Initialized,							///< �책횆징 횄횎짹창횊짯 쩔횕쨌찼

	linkEvent_Scanning,								///< �책횆징 째횏쨩철 쩍횄�횤
	linkEvent_ScanStop,								///< �책횆징 째횏쨩철 횁횩쨈횥

	linkEvent_FoundDroneService,					///< 쨉책쨌횖 쩌짯쨘챰쩍쨘 째횏쨩철 쩔횕쨌찼

	linkEvent_Connecting,							///< �책횆징 쩔짭째찼 쩍횄�횤
	linkEvent_Connected,							///< �책횆징 쩔짭째찼

	linkEvent_ConnectionFaild,						///< 쩔짭째찼 쩍횉횈횖
	linkEvent_ConnectionFaildNoDevices,				///< 쩔짭째찼 쩍횉횈횖 - �책횆징째징 쩐첩�쩍
	linkEvent_ConnectionFaildNotReady,				///< 쩔짭째찼 쩍횉횈횖 - 쨈챘짹창 쨩처횇횂째징 쩐횈쨈횚

	linkEvent_PairingStart,							///< 횈채쩐챤쨍쨉 쩍횄�횤
	linkEvent_PairingSuccess,						///< 횈채쩐챤쨍쨉 쩌쨘째첩
	linkEvent_PairingFaild,							///< 횈채쩐챤쨍쨉 쩍횉횈횖

	linkEvent_BondingSuccess,						///< Bonding 쩌쨘째첩

	linkEvent_LookupAttribute,						///< �책횆징 쩌짯쨘챰쩍쨘 쨔횞 쩌횙쩌쨘 째횏쨩철(GATT Event 쩍횉횉횪)

	linkEvent_RssiPollingStart,						///< RSSI 횉짰쨍쨉 쩍횄�횤
	linkEvent_RssiPollingStop,						///< RSSI 횉짰쨍쨉 횁횩횁철

	linkEvent_DiscoverService,						///< 쩌짯쨘챰쩍쨘 째횏쨩철
	linkEvent_DiscoverCharacteristic,				///< 쩌횙쩌쨘 째횏쨩철
	linkEvent_DiscoverCharacteristicDroneData,		///< 쩌횙쩌쨘 째횏쨩철
	linkEvent_DiscoverCharacteristicDroneConfig,	///< 쩌횙쩌쨘 째횏쨩철
	linkEvent_DiscoverCharacteristicUnknown,		///< 쩌횙쩌쨘 째횏쨩철
	linkEvent_DiscoverCCCD,							///< CCCD 째횏쨩철

	linkEvent_ReadyToControl,						///< 횁짝쩐챤 횁횠쨘챰 쩔횕쨌찼

	linkEvent_Disconnecting,						///< �책횆징 쩔짭째찼 횉횠횁짝 쩍횄�횤
	linkEvent_Disconnected,							///< �책횆징 쩔짭째찼 횉횠횁짝 쩔횕쨌찼

	linkEvent_GapLinkParamUpdate,					///< GAP_LINK_PARAM_UPDATE_EVENT

	linkEvent_RspReadError,							///< RSP �횖짹창 쩔�쨌첫
	linkEvent_RspReadSuccess,						///< RSP �횖짹창 쩌쨘째첩

	linkEvent_RspWriteError,						///< RSP 쩐짼짹창 쩔�쨌첫
	linkEvent_RspWriteSuccess,						///< RSP 쩐짼짹창 쩌쨘째첩

	linkEvent_SetNotify,							///< Notify 횊째쩌쨘횊짯

	linkEvent_Write,								///< 쨉짜�횑횇횒 쩐짼짹창 �횑쨘짜횈짰

	EndOfType
};


/***********************************************************************/
//////////////////////////////DRONE/////////////////////////////////////
/***********************************************************************/
enum DataType
{
	dType_None = 0, 				///< 쩐첩�쩍

	// 쩍횄쩍쨘횇횤 횁짚쨘쨍
	dType_Ping, 					///< 횇챘쩍횇 횊짰�횓(reserve)
	dType_Ack, 						///< 쨉짜�횑횇횒 쩌철쩍횇쩔징 쨈챘횉횗 ��쨈채
	dType_Error, 					///< 쩔�쨌첫(reserve, 쨘챰횈짰 횉횄쨌징짹횞쨈횂 횄횩횊횆쩔징 횁철횁짚)
	dType_Request, 					///< 횁철횁짚횉횗 횇쨍�횚�횉 쨉짜�횑횇횒 쩔채횄쨩
	dType_DeviceName, 				///< �책횆징�횉 �횑쨍짠 쨘짱째챈

	// 횁쨋횁쩐, 쨍챠쨌횋
	dType_Control = 0x10, 			///< 횁쨋횁쩐
	dType_Command, 					///< 쨍챠쨌횋
	dType_Command2, 				///< 쨈횢횁횩 쨍챠쨌횋(2째징횁철 쩌쨀횁짚�쨩 쨉쩔쩍횄쩔징 쨘짱째챈)
	DType_Command3, 				///< 쨈횢횁횩 쨍챠쨌횋(3째징횁철 쩌쨀횁짚�쨩 쨉쩔쩍횄쩔징 쨘짱째챈)

	// LED
	dType_LedMode = 0x20, 			///< LED 쨍챨쨉책 횁철횁짚
	dType_LedMode2, 				///< LED 쨍챨쨉책 2째쨀 횁철횁짚
	dType_LedModeCommand, 			///< LED 쨍챨쨉책, 횆쩔쨍횉쨉책
	dType_LedModeCommandIr, 		///< LED 쨍챨쨉책, 횆쩔쨍횉쨉책, IR 쨉짜�횑횇횒 쩌횤쩍횇
	dType_LedModeColor, 			///< LED 쨍챨쨉책 3쨩철 횁첨횁짖 횁철횁짚
	dType_LedModeColor2, 			///< LED 쨍챨쨉책 3쨩철 횁첨횁짖 횁철횁짚 2째쨀
	dType_LedEvent, 				///< LED �횑쨘짜횈짰
	dType_LedEvent2, 				///< LED �횑쨘짜횈짰 2째쨀,
	dType_LedEventCommand, 			///< LED �횑쨘짜횈짰, 횆쩔쨍횉쨉책
	dType_LedEventCommandIr,		///< LED �횑쨘짜횈짰, 횆쩔쨍횉쨉책, IR 쨉짜�횑횇횒 쩌횤쩍횇
	dType_LedEventColor, 			///< LED �횑쨘짜횈짰 3쨩철 횁첨횁짖 횁철횁짚
	dType_LedEventColor2, 			///< LED �횑쨘짜횈짰 3쨩철 횁첨횁짖 횁철횁짚 2째쨀

	//update-170426
	dType_LedDefaultColor,  		// LED 횄횎짹창 쨍챨쨉책 3쨩철 횁첨횁짖 횁철횁짚
    dType_LedDefaultColor2, 		// LED 횄횎짹창 쨍챨쨉책 3쨩철 횁첨횁짖 횁철횁짚 2째쨀

	// 쨩처횇횂
	dType_Address = 0x30, 			///< IEEE address
	dType_State, 					///< 쨉책쨌횖�횉 쨩처횇횂(쨘챰횉횪 쨍챨쨉책, 쨔챈�짠짹창횁횠, 쨔챔횇횒쨍짰쨌짰)
	dType_Attitude, 				///< 쨉책쨌횖�횉 �횣쩌쩌(Vector)
	dType_GyroBias,					///< �횣�횑쨌횓 쨔횢�횑쩐챤쩍쨘 째짧(Vector)
	dType_TrimAll, 					///< �체횄쩌 횈짰쨍짼 (쨘챰횉횪+횁횜횉횪)체
	dType_TrimFlight,				///< 쨘챰횉횪 횈짰쨍짼
	dType_TrimDrive, 				///< 횁횜횉횪 횈짰쨍짼

	//update-170426
	dType_CountFlight,            	// 쨘챰횉횪 째체쨌횄 횆짬쩔챤횈짰
	dType_CountDrive,             	// 횁횜횉횪 째체쨌횄 횆짬쩔챤횈짰

	// 쨉짜�횑횇횒 쩌횤쩌철쩍횇
	dType_IrMessage = 0x40, 		///< IR 쨉짜�횑횇횒 쩌횤쩌철쩍횇

	// 쩌쩐쩌짯
	dType_ImuRawAndAngle = 0x50, 	///< IMU Raw + Angle
	dType_Pressure, 				///< 쩐횖쨌횂 쩌쩐쩌짯 쨉짜�횑횇횒
	dType_ImageFlow, 				///< ImageFlow
	dType_Button, 					///< 쨔철횈째 �횚쨌횂
	dType_Battery, 					///< 쨔챔횇횒쨍짰
	dType_Motor, 					///< 쨍챨횇횒 횁짝쩐챤 쨔횞 횉철�챌 횁짝쩐챤 째짧 횊짰�횓
	dType_Temperature, 				///< 쩔횂쨉쨉
	//update-170426
	dType_Range,					// 째횇쨍짰 쩌쩐쩌짯
	// 쨍쨉횇짤 쨘쨍쨉책
	dType_LinkState = 0xE0,			///< 쨍쨉횇짤 쨍챨쨉창�횉 쨩처횇횂
	dType_LinkEvent,				///< 쨍쨉횇짤 쨍챨쨉창�횉 �횑쨘짜횈짰
	dType_LinkEventAddress,			///< 쨍쨉횇짤 쨍챨쨉창�횉 �횑쨘짜횈짰 + 횁횜쩌횘
	dType_LinkRssi,					///< 쨍쨉횇짤쩔횒 쩔짭째찼쨉횊 �책횆징�횉 RSSI째짧
	dType_LinkDiscoveredDevice,		///< 째횏쨩철쨉횊 �책횆징
	dType_LinkPasscode,          	///< 쩔짭째찼횉횘 쨈챘쨩처 �책횆징�횉 쩐횕횊짙 횁철횁짚
	dType_StringMessage = 0xD0, 	///< 쨔짰�횣쩔짯 쨍횧쩌쩌횁철
	dType_EndOfType
};

/***********************************************************************/
enum CommandType
{
	cType_None = 0, 				///< �횑쨘짜횈짰 쩐첩�쩍

	// 쩌쨀횁짚
	cType_ModeDrone = 0x10, 		///< 쨉책쨌횖 쨉쩔�횤 쨍챨쨉책 �체횊짱

	// 횁짝쩐챤
	cType_Coordinate = 0x20, 		///< 쨔챈�짠 짹창횁횠 쨘짱째챈
	cType_Trim, 										///< 횈짰쨍짼 쨘짱째챈
	cType_FlightEvent, 				///< 쨘챰횉횪 �횑쨘짜횈짰 쩍횉횉횪
	cType_DriveEvent, 				///< 횁횜횉횪 �횑쨘짜횈짰 쩍횉횉횪
	cType_Stop, 					///< 횁짚횁철
	cType_ResetHeading = 0x50, 		///< 쨔챈횉창�쨩 쨍짰쩌횂(쩐횤쩌횜쨌챌횈짰 쨍챨쨉책 �횕 쨋짠 횉철�챌 heading�쨩 0쨉쨉쨌횓 쨘짱째챈)
	cType_ClearGyroBiasAndTrim, 	/// �횣�횑쨌횓 쨔횢�횑쩐챤쩍쨘쩔횒 횈짰쨍짼 쩌쨀횁짚 횄횎짹창횊짯

	//update-170426
	cType_ClearTrim,					// 횈짰쨍짼 횄횎짹창횊짯

	// 횇챘쩍횇
	cType_PairingActivate = 0x80, 	///< 횈채쩐챤쨍쨉 횊째쩌쨘횊짯
	cType_PairingDeactivate, 		///< 횈채쩐챤쨍쨉 쨘챰횊째쩌쨘횊짯
	cType_TerminateConnection, 		///< 쩔짭째찼 횁쩐쨌찼

	// 쩔채횄쨩
	cType_Request = 0x90, 			///< 횁철횁짚횉횗 횇쨍�횚�횉 쨉짜�횑횇횒 쩔채횄쨩

	// 쨍쨉횇짤 쨘쨍쨉책
	cType_LinkModeBroadcast = 0xE0, ///< LINK 쩌횤쩌철쩍횇 쨍챨쨉책 �체횊짱
	cType_LinkSystemReset, 			///< 쩍횄쩍쨘횇횤 �챌쩍횄�횤
	cType_LinkDiscoverStart, 		///< �책횆징 째횏쨩철 쩍횄�횤
	cType_LinkDiscoverStop, 		///< �책횆징 째횏쨩철 횁횩쨈횥
	cType_LinkConnect, 				///< 쩔짭째찼
	cType_LinkDisconnect, 			///< 쩔짭째찼 횉횠횁짝
	cType_LinkRssiPollingStart, 	///< RSSI 쩌철횁첵 쩍횄�횤
	cType_LinkRssiPollingStop, 		///< RSSI 쩌철횁첵 횁횩쨈횥

	cType_EndOfType
};

/***********************************************************************/
enum ModeDrone
{
	dMode_None = 0, 				///< 쩐첩�쩍

	dMode_Flight = 0x10, 			///< 쨘챰횉횪 쨍챨쨉책(째징쨉책 횈첨횉횚)
	dMode_FlightNoGuard, 			///< 쨘챰횉횪 쨍챨쨉책(째징쨉책 쩐첩�쩍)
	dMode_FlightFPV, 				///< 쨘챰횉횪 쨍챨쨉책(FPV)

	dMode_Drive = 0x20, 			///< 횁횜횉횪 쨍챨쨉책
	dMode_DriveFPV, 				///< 횁횜횉횪 쨍챨쨉책(FPV)
	dMode_Test = 0x30, 				///< 횇횞쩍쨘횈짰 쨍챨쨉책
	dMode_EndOfType
};

/***********************************************************************/
enum ModeVehicle
{
	vMode_None = 0,
	vMode_Boot, 					///< 쨘횓횈횄
	vMode_Wait, 					///< 쩔짭째찼 쨈챘짹창 쨩처횇횂
	vMode_Ready, 					///< 쨈챘짹창 쨩처횇횂
	vMode_Running, 					///< 쨍횧�횓 횆횣쨉책 쨉쩔�횤
	vMode_Update, 					///< 횈횩쩔첸쩐챤 쩐첨쨉짜�횑횈짰
	vMode_UpdateComplete,			///< 횈횩쩔첸쩐챤 쩐첨쨉짜�횑횈짰 쩔횕쨌찼
	vMode_Error, 					///< 쩔�쨌첫
	vMode_EndOfType
};

/***********************************************************************/
enum ModeFlight
{
	fMode_None = 0,
	fMode_Ready, 					///< 쨘챰횉횪 횁횠쨘챰
	fMode_TakeOff, 					///< �횑쨌첬 (Flight쨌횓 �횣쨉쩔�체횊짱)
	fMode_Flight, 					///< 쨘챰횉횪
	fMode_Flip, 					///< 횊쨍�체
	fMode_Stop, 					///< 째짯횁짝 횁짚횁철
	fMode_Landing, 					///< 횂첩쨌첬
	fMode_Reverse, 					///< 쨉횣횁첵짹창
	fMode_Accident, 				///< 쨩챌째챠 (Ready쨌횓 �횣쨉쩔�체횊짱)
	fMode_Error, 					///< 쩔�쨌첫
	fMode_EndOfType
};

/***********************************************************************/
enum ModeDrive
{
	dvMode_None = 0,
	dvMode_Ready, 					///< 횁횠쨘챰
	dvMode_Start, 					///< 횄창쨔횩
	dvMode_Drive, 					///< 횁횜횉횪
	dvMode_Stop, 					///< 째짯횁짝 횁짚횁철
	dvMode_Accident, 				///< 쨩챌째챠 (Ready쨌횓 �횣쨉쩔�체횊짱)
	dvMode_Error, 					///< 쩔�쨌첫
	dvMode_EndOfType
};

/***********************************************************************/
enum SensorOrientation
{
	senOri_None = 0,
	senOri_Normal, 					///< 횁짚쨩처
	senOri_ReverseStart, 			///< 쨉횣횁첵횊첨짹창 쩍횄�횤
	senOri_Reverse, 				///< 쨉횣횁첵횊청
	senOri_EndOfType
};

/***********************************************************************/
enum Coordinate
{
	cSet_None = 0, 					///< 쩐첩�쩍

	cSet_Absolute, 					///< 째챠횁짚 횁횂횉짜째챔
	cSet_Relative, 					///< 쨩처쨈챘 횁횂횉짜째챔

	cSet_EndOfType
};

/***********************************************************************/

enum Trim
{
	trim_None = 0, 					///< 쩐첩�쩍
	trim_RollIncrease, 				///< Roll 횁천째징
	trim_RollDecrease, 				///< Roll 째짢쩌횘
	trim_PitchIncrease, 			///< Pitch 횁천째징
	trim_PitchDecrease, 			///< Pitch 째짢쩌횘
	trim_YawIncrease, 				///< Yaw 횁천째징
	trim_YawDecrease, 				///< Yaw 째짢쩌횘
	trim_ThrottleIncrease, 			///< Throttle 횁천째징
	trim_ThrottleDecrease, 			///< Throttle 째짢쩌횘
	trim_EndOfType
};

/***********************************************************************/

enum FlightEvent
{
	fEvent_None = 0, 				///< 쩐첩�쩍

	fEvent_TakeOff, 				///< �횑쨌첬

	fEvent_FlipFront, 				///< 횊쨍�체
	fEvent_FlipRear, 				///< 횊쨍�체
	fEvent_flipLeft, 				///< 횊쨍�체
	fEvent_FlipRight, 				///< 횊쨍�체

	fEvent_Stop, 					///< 횁짚횁철
	fEvent_Landing, 				///< 횂첩쨌첬
	fEvent_TurnOver, 				///< 쨉횣횁첵짹창

	fEvent_Shot, 					///< 쨔횑쨩챌�횕�쨩 쩍챵 쨋짠 쩔챵횁첨�횙
	fEvent_UnderAttack, 			///< 쨔횑쨩챌�횕�쨩 쨍횂�쨩 쨋짠 쩔챵횁첨�횙

	fEvent_Square, 					///< 횁짚쨔챈횉창 쨉쨔짹창
	fEvent_CircleLeft, 				///< 쩔횧횂횎�쨍쨌횓 횊쨍�체
	fEvent_CircleRight, 			///< 쩔�쨍짜횂횎�쨍쨌횓 횊쨍�체
	fEvent_Rotate180,				///< 180쨉쨉 횊쨍�체

	fEvent_EndOfType
};

enum DriveEvent
{
	dEvent_None = 0,
	dEvent_Ready, 					///< 횁횠쨘챰
	dEvent_Start, 					///< 횄창쨔횩
	dEvent_Drive, 					///< 횁횜횉횪
	dEvent_Stop, 					///< 째짯횁짝 횁짚횁철
	dEvent_Accident, 				///< 쨩챌째챠 (Ready쨌횓 �횣쨉쩔�체횊짱)
	dEvent_Error, 					///< 쩔�쨌첫
	dEvent_EndOfType
};

/***********************************************************************/
enum Request
{
	// 쨩처횇횂
	Req_Address = 0x30, 			///< IEEE address
	Req_State, 						///< 쨉책쨌횖�횉 쨩처횇횂(쨘챰횉횪 쨍챨쨉책, 쨔챈�짠짹창횁횠, 쨔챔횇횒쨍짰쨌짰)
	Req_Attitude, 					///< 쨉책쨌횖�횉 �횣쩌쩌(Vector)
	Req_GyroBias, 					///< �횣�횑쨌횓 쨔횢�횑쩐챤쩍쨘 째짧(Vector)
	Req_TrimAll, 					///< �체횄쩌 횈짰쨍짼
	Req_TrimFlight, 				///< 쨘챰횉횪 횈짰쨍짼
	Req_TrimDrive, 					///< 횁횜횉횪 횈짰쨍짼

	//update-170426
	Req_CountFlight,            	// 쨘챰횉횪 째체쨌횄 횆짬쩔챤횈짰
	Req_CountDrive,             	// 횁횜횉횪 째체쨌횄 횆짬쩔챤횈짰

	// 쩌쩐쩌짯
	Req_ImuRawAndAngle = 0x50, 		///< IMU Raw + Angle
	Req_Pressure, 					///< 쩐횖쨌횂 쩌쩐쩌짯 쨉짜�횑횇횒
	Req_ImageFlow, 					///< ImageFlow
	Req_Button, 					///< 쨔철횈째 �횚쨌횂
	Req_Battery, 					///< 쨔챔횇횒쨍짰
	Req_Motor, 						///< 쨍챨횇횒 횁짝쩐챤 쨔횞 횉철�챌 횁짝쩐챤 째짧 횊짰�횓
	Req_Temperature, 				///< 쩔횂쨉쨉
		//update-170426				// 째횇쨍짰 쩌쩐쩌짯
	Req_Range,
	Req_EndOfType
};

/***********************************************************************/
enum ModeLight
{
  Light_None,
  WaitingForConnect, 				///< 쩔짭째찼 쨈챘짹창 쨩처횇횂
  Connected,

  EyeNone = 0x10,
  EyeHold, 							///< 횁철횁짚횉횗 쨩철쨩처�쨩 째챔쩌횙 횆횚
  EyeMix, 							///< 쩌첩횂첨�청�쨍쨌횓 LED 쨩철 쨘짱째챈
  EyeFlicker, 						///< 짹척쨘첵�횙
  EyeFlickerDouble, 				///< 짹척쨘첵�횙(쨉횓 쨔첩 짹척쨘첵�횑째챠 짹척쨘첵�횓 쩍횄째짙쨍쨍횇짯 짼짢횁체)
  EyeDimming, 						///< 쨔횪짹창 횁짝쩐챤횉횕쩔짤 횄쨉횄쨉횊첨 짹척쨘첵�횙

  ArmNone = 0x40,
  ArmHold, 							///< 횁철횁짚횉횗 쨩철쨩처�쨩 째챔쩌횙 횆횚
  ArmMix, 							///< 쩌첩횂첨�청�쨍쨌횓 LED 쨩철 쨘짱째챈
  ArmFlicker, 						///< 짹척쨘첵�횙
  ArmFlickerDouble, 				///< 짹척쨘첵�횙(쨉횓 쨔첩 짹척쨘첵�횑째챠 짹척쨘첵�횓 쩍횄째짙쨍쨍횇짯 짼짢횁체)
  ArmDimming, 						///< 쨔횪짹창 횁짝쩐챤횉횕쩔짤 횄쨉횄쨉횊첨 짹척쨘첵�횙
  ArmFlow, 							///< 쩐횛쩔징쩌짯 쨉횣쨌횓 횊책쨍짠
  ArmFlowReverse, 					///< 쨉횣쩔징쩌짯 쩐횛�쨍쨌횓 횊책쨍짠
  EndOfLedMode
};

enum LED
{
  LED_NONE = 0x10,
  LED_HOLD,
  LED_MIX,
  LED_FLICKER,
  LED_FLICKERDOUBLE,
  LED_DIMMING,
  LED_FLOW,
  LED_FLOWREVERSE,
  LED_EndOfType
};

/***********************************************************************/
enum Colors
{
	AliceBlue, AntiqueWhite, Aqua,
	Aquamarine, Azure, Beige,
	Bisque, Black, BlanchedAlmond,
	Blue, BlueViolet, Brown,
	BurlyWood, CadetBlue, Chartreuse,
	Chocolate, Coral, CornflowerBlue,
	Cornsilk, Crimson, Cyan,
	DarkBlue, DarkCyan, DarkGoldenRod,
	DarkGray, DarkGreen, DarkKhaki,
	DarkMagenta, DarkOliveGreen, DarkOrange,
	DarkOrchid, DarkRed, DarkSalmon,
	DarkSeaGreen, DarkSlateBlue, DarkSlateGray,
	DarkTurquoise, DarkViolet, DeepPink,
	DeepSkyBlue, DimGray, DodgerBlue,
	FireBrick, FloralWhite, ForestGreen,
	Fuchsia, Gainsboro, GhostWhite,
	Gold, GoldenRod, Gray,
	Green, GreenYellow, HoneyDew,
	HotPink, IndianRed, Indigo,
	Ivory, Khaki, Lavender,
	LavenderBlush, LawnGreen, LemonChiffon,
	LightBlue, LightCoral, LightCyan,
	LightGoldenRodYellow, LightGray, LightGreen,
	LightPink, LightSalmon, LightSeaGreen,
	LightSkyBlue, LightSlateGray, LightSteelBlue,
	LightYellow, Lime, LimeGreen,
	Linen, Magenta, Maroon,
	MediumAquaMarine, MediumBlue, MediumOrchid,
	MediumPurple, MediumSeaGreen, MediumSlateBlue,
	MediumSpringGreen, MediumTurquoise, MediumVioletRed,
	MidnightBlue, MintCream, MistyRose,
	Moccasin, NavajoWhite, Navy,
	OldLace, Olive, OliveDrab,
	Orange, OrangeRed, Orchid,
	PaleGoldenRod, PaleGreen, PaleTurquoise,
	PaleVioletRed, PapayaWhip, PeachPuff,
	Peru, Pink, Plum,
	PowderBlue, Purple, RebeccaPurple,
	Red, RosyBrown, RoyalBlue,
	SaddleBrown, Salmon, SandyBrown,
	SeaGreen, SeaShell, Sienna,
	Silver, SkyBlue, SlateBlue,
	SlateGray, Snow, SpringGreen,
	SteelBlue, Tan, Teal,
	Thistle, Tomato, Turquoise,
	Violet, Wheat, White,
	WhiteSmoke, Yellow, YellowGreen,
	EndOfColor
};

/***********************************************************************/

class CoDroneClass
{
public:

/////////////////////////////////////////////////////////////////////////

	void begin(long baud);

	void Receive(void);

	void Control();
	void Control(int interval);

	void Send_Command(int sendCommand, int sendOption);
	void Send_Processing(uint8_t _data[], uint8_t _length, uint8_t _crc[]);

/////////////////////////////////////////////////////////////////////////

	void LinkReset();
	void Send_LinkState();
	void Send_LinkModeBroadcast(uint8_t mode);

/////////////////////////////////////////////////////////////////////////

	void AutoConnect(uint8_t mode);
  void AutoConnect(uint8_t mode, uint8_t address[]);
	void Send_ConnectAddressInputDrone(uint8_t address[]);
	void Send_ConnectConnectedDrone();
	void Send_ConnectNearbyDrone();
	void Send_Connect(uint8_t index);
	void Send_Disconnect();
	void Send_Discover(uint8_t action);
	void Send_Check(uint8_t _data[], uint8_t _length, uint8_t _crc[]);

/////////////////////////////////////////////////////////////////////////

	void Send_Ping();
	void Send_ResetHeading();
	void Send_RSSI_Polling(uint8_t action);
	void Send_DroneMode(uint8_t event);
	void Send_Coordinate(uint8_t mode);
	void Send_ClearGyroBiasAndTrim();
	void DroneModeChange(uint8_t event);
	void FlightEvent(uint8_t event);
	void DriveEvent(uint8_t event);

/////////////////////////////////////////////////////////////////////////

	void BattleShooting();
	void BattleReceive();
	void BattleBegin(uint8_t teamSelect);
	void BattleDamageProcess();

/////////////////////////////////////////////////////////////////////////

	void Request_DroneState();
	void Request_DroneAttitude();
	void Request_DroneGyroBias();

	void Request_TrimAll();
	void Request_TrimFlight();
	void Request_TrimDrive();

	void Request_ImuRawAndAngle();
	void Request_Pressure();
	void Request_ImageFlow();
	void Request_Button();
	void Request_Battery();
	void Request_Motor();
	void Request_Temperature();

	void Request_CountFlight();
	void Request_CountDrive();
	void Request_Range();

/////////////////////////////////////////////////////////////////////////

	void Set_Trim(uint8_t event);
	void Set_TrimReset();
	void Set_TrimAll(int _roll, int _pitch, int _yaw, int _throttle, int _wheel);
	void Set_TrimFlight(int _roll, int _pitch, int _yaw, int _throttle);
	void Set_TrimDrive(int _wheel);

/////////////////////////////////////////////////////////////////////////

	void LedColorProcess(uint8_t _dType, uint8_t sendMode, uint8_t sendColor, uint8_t sendInterval);
	void LedColorProcess(uint8_t _dType, uint8_t sendMode, uint8_t r, uint8_t g, uint8_t b, uint8_t sendInterval);
	void LedColorProcess(uint8_t _dType, uint8_t sendMode, uint8_t sendColor[], uint8_t sendInterval);

	void LedColor(uint8_t sendMode, uint8_t sendColor, uint8_t sendInterval);
	void LedColor(uint8_t sendMode, uint8_t r, uint8_t g, uint8_t b, uint8_t sendInterval);
	void LedColor(uint8_t sendMode, uint8_t sendColor[], uint8_t sendInterval);
	//void LedColorTwo(uint8_t sendMode, uint8_t r, uint8_t g, uint8_t b, uint8_t sendInterval, uint8_t sendMode, uint8_t r, uint8_t g, uint8_t b, uint8_t sendInterval);

	void LedEvent(uint8_t sendMode, uint8_t sendColor, uint8_t sendInterval, uint8_t sendRepeat);
	void LedEvent(uint8_t sendMode, uint8_t r, uint8_t g, uint8_t b, uint8_t sendInterval, uint8_t sendRepeat);
	void LedEvent(uint8_t sendMode, uint8_t sendColor[], uint8_t sendInterval, uint8_t sendRepeat);

	void LedColorDefault(uint8_t sendMode, uint8_t r, uint8_t g, uint8_t b, uint8_t sendInterval);
	void LedColorDefault(uint8_t sendMode, uint8_t sendColor[], uint8_t sendInterval);
	//edit //170821
	void LedColorDefault(uint8_t sendMode, uint8_t sendColor[], uint8_t sendInterval, uint8_t sendMode2, uint8_t sendColor2[], uint8_t sendInterval2);

/////////////////////////////////////////////////////////////////////////

	void LinkStateCheck();
	void ReceiveEventCheck(uint8_t _completeData[]);
	int LowBatteryCheck(uint8_t value);
	void DisplayRSSI();

/////////////////////////////////////////////////////////////////////////

	void LED_PORTC(int value);
	void LED_DDRC(int value);
	void LED_Move_Radar(uint8_t display);
	void LED_Start();
	void LED_Move_Slide();
	void LED_Connect();
	void LED_Standard();
	void LED_Blink(int time, int count);

/////////////////////////////////////////////////////////////////////////

	unsigned short CRC16_Make(unsigned char *buf, int len); //CRC16-CCITT Format
	bool CRC16_Check(unsigned char data[], int len, unsigned char crc[]);

/////////////////////////////////////////////////////////////////////////

	void PrintDroneAddress();
	void DisplayAddress(uint8_t count, uint8_t _devName0[], uint8_t _devName1[],uint8_t _devName2[], uint8_t _devName3[], uint8_t _devName4[]);

/////////////////////////////////////////////////////////////////////////

	void ButtonPreesHoldWait(int button);
	void ButtonPreesHoldWait(int button1, int button2);
	int AnalogScaleChange(int analogValue);

/////////////////////////////////////////////////////////////////////////

	bool TimeCheck(uint16_t interval); 					//milliseconds
	bool TimeOutSendCheck(uint16_t interval); 			//milliseconds
	bool TimeCheckBuzz(uint16_t interval); 				//microseconds

/////////////////////////////////////////////////////////////////////////

	void Buzz(long frequency, int tempo);
	void BeepWarning(int count);

/////////////////////////////////////////////////////////////////////////

	int GestureFuntion(int sen1, bool act1, int sen2, bool act2,void(CoDroneClass::*pf)(uint8_t), uint8_t command);
	int GestureCheckPosition(int sen1, bool act1, int sen2, bool act2);
	int GestureReturnPositon(int sen1, int sen2);

/////////////////////////////////////////////////////////////////////////
	// 2018, 1, 22 added

	//getter and setter
	void setRoll(int _roll);
	int getRoll();

	void setPitch(int _pitch);
	int getPitch();

	void setYaw(int _yaw);
	int getYaw();

	void setThrottle(int _throttle);
	int getThrottle();

	void trim(int _roll, int _pitch, int _yaw, int _throttle);
	void resetTrim();

	//flight command
	void go(int direction);
	void go(int direction, float duration);
	void go(int direction, float duration, int power);


	void move();
	void move(float duration);
	void move(int _roll, int _pitch, int _yaw, int _throttle);
	void move(float duration, int _roll, int _pitch, int _yaw, int _throttle);

	void turn(int direction);
	void turn(int direction, float duration);
	void turn(int direction, float duration, int power);


	void hover(float duration);
	void turnDegree(int direction, int degree);

	//FlightEvnet
	void takeOff();
	void land();
	void emergencyStop();
/////////////////////////////////////////////////////////////////////////

	//2018. 1. 29 added
	int getHeight();
	int getPressure();
	int getDroneTemp();
	gyrodata getAngulerSpeed();
	angledata getGyroAngles();
	acceldata getAceelerometer();
	int getBatteryPercentage();
	int getBatteryVoltage();
	trimdata getTrim();
	// not finalized!!
	int getState();
	optdata getOptFlowPosition();
	void goToHeight(int set);

	bool isUpsideDown();
	bool isFlying();
	bool isReadyToFly();


/////////////////////////////////////////////////////////////////////////

	//2018. 2. 12 added
	void setArmRGB(uint8_t r, uint8_t g, uint8_t b);
	void setEyeRGB(uint8_t r, uint8_t g, uint8_t b);
	void setAllRGB(uint8_t r, uint8_t g, uint8_t b);
	void setArmDefaultRGB(uint8_t r, uint8_t g, uint8_t b);
	void setEyeDefaultRGB(uint8_t r, uint8_t g, uint8_t b);
	void setAllDefaultRGB(uint8_t r, uint8_t g, uint8_t b);

	void resetDefaultLED();

	void setArmMode(uint8_t mode);
	void setEyeMode(uint8_t mode);
	void setAllMode(uint8_t mode);
	void setArmDefaultMode(uint8_t mode);
	void setEyeDefaultMode(uint8_t mode);
	void setAllDefaultMode(uint8_t mode);


	//sequence
	void flySequence(int shape);
	void sway();
	void zigzag();
	void square();
	void triangle();
	void hop();
	void circle();
	void spiral();

/////////////////////////////////////////////////////////////////////////

	int TrimAll_Roll;
	int TrimAll_Pitch;
	int TrimAll_Yaw;
	int TrimAll_Throttle;
	int TrimAll_Wheel;

	uint8_t cmdBuff[MAX_PACKET_LENGTH];

	uint8_t checkHeader;
	uint8_t cmdIndex;
	uint8_t receiveDtype;
	uint8_t receiveLength;

	uint8_t receiveLikMode;
	uint8_t receiveLinkState;
	int receiveEventState;
	int receiveComplete;


/////////////////////////////////////////////////////////////////////////

	uint8_t displayMode = 1;	//smar inventor : default 1
	uint8_t debugMode = 0;		//smar inventor : default 0

	uint8_t discoverFlag;
	uint8_t connectFlag;

	bool pairing = 0;

	int SendInterval; //millis seconds
	int analogOffset;

	uint8_t displayLED = 0;

	uint8_t timeOutRetry = 0;

	uint8_t sendCheckCount = 0;
	uint8_t sendCheckFlag = 0;

/////////////////////////////////////////////////////////////////////////////
	uint8_t receiveAttitudeSuccess = 0;
	uint8_t receiveRangeSuccess = 0;
	uint8_t receiveGyroSuccess = 0;
	uint8_t receiveAccelSuccess = 0;
	uint8_t receivePressureSuccess = 0;
	uint8_t receiveTrimSuccess = 0;
	uint8_t receiveStateSuccess = 0;
	uint8_t receiveBatterySuccess = 0;
	uint8_t receiveOptSuccess = 0;


	uint8_t energy = 8;
	uint8_t team = FREE_PLAY;
	unsigned long weapon = FREE_MISSILE;

/////////////////////////////////////////////////////////////////////////

	uint8_t devCount = 0;
	uint8_t devFind[5];

	int devRSSI0 = -1;
	int devRSSI1 = -1;
	int devRSSI2 = -1;
	int devRSSI3 = -1;
	int devRSSI4 = -1;

	uint8_t devAddress0[6];
	uint8_t devAddress1[6];
	uint8_t devAddress2[6];
	uint8_t devAddress3[6];
	uint8_t devAddress4[6];

	uint8_t devAddressBuf[6];
	uint8_t devAddressConnected[6];

/////////////////////////////////////////////////////////////////////////

	uint8_t dataBuff[30];

	int roll = 0;
	int pitch = 0;
	int yaw = 0;
	int throttle = 0;

	int attitudeRoll	= 0;
	int attitudePitch	= 0;
	int attitudeYaw	= 0;
	int yawDegree = 0;

	int GyroBias_Roll	= 0;
	int GyroBias_Pitch	= 0;
	int GyroBias_Yaw	= 0;

	int ImuAccX	= 0;
	int ImuAccY	= 0;
	int ImuAccZ	= 0;

	int ImuGyroRoll		= 0;
	int ImuGyroPitch	= 0;
	int ImuGyroYaw		= 0;

	int ImuAngleRoll	= 0;
	int ImuAnglePitch	= 0;
	int ImuAngleYaw		= 0;

	long d1				= 0;
	long d2				= 0;
	long temperature	= 0;
	long pressure		= 0;

	long fVelocitySumX 	= 0;
	long fVelocitySumY	= 0;

	uint8_t button = 0;

	int Battery_v30			= 0;
	int Battery_v33			= 0;
	int Battery_gradient	= 0;
	int Battery_yIntercept	= 0;
	int flagBatteryCalibration	= 0;
	long Battery_Raw		= 0;
	int Battery_Percent		= 0;
	int Battery_voltage		= 0;

	int countAccident	= 0;
	int countTakeOff	= 0;
	int countLanding	= 0;

	int m1_forward	= 0;
	int m1_reverse	= 0;
	int m2_forward	= 0;
	int m2_reverse	= 0;
	int m3_forward	= 0;
	int m3_reverse	= 0;
	int m4_forward	= 0;
	int m4_reverse	= 0;

	long imu_temp		= 0;
	long pressure_temp	= 0;


/////////////////////////////////////////////////////////////////////////

	uint8_t linkState = 0;;
	int rssi = 0;
	uint8_t battery = 0;
  	unsigned long	irMassageReceive;
	uint8_t droneState[7];
	int sensorRange[6];

	long PreviousMillis;
	long batterytime = -5000;
/////////////////////////////////////////////////////////////////////////

	int prevControl[4];
	void SequenceDelay(int setTime);
//////////////////////////////////////////////////////////////////////////
	uint8_t armred = 255;
	uint8_t armgreen = 0;
	uint8_t armblue = 0;
	uint8_t eyered = 255;
	uint8_t eyegreen = 0;
	uint8_t eyeblue = 0;
	uint8_t armmode = ArmHold;
	uint8_t eyemode = EyeHold;
/////////////////////////////////////////////////////////////////////////

private:
	long PreviousBuzz;
	long timeOutSendPreviousMillis;
};

extern CoDroneClass CoDrone;

#endif


void codroneInit(void);




#endif /* SRC_COMMON_AP_CODRONE_CODRONE_H_ */
