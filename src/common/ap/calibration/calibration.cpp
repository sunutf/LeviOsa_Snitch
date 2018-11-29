/*
 * calibration.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: D.ggavy
 */

//processing step//
//1. cmdif -> leviosa cali start

//2. [get] init_packet
//3. [sorting] -> init_ang, end_ang, iter_cnt, resolution
//4. [get] tcs34725 raw data -> sum (iter_cnt)
//5. [store] aver_raw_data -> cali_lookup_tbl
//6. [send] done_packet

//repeat//
//7. [get] ack_packet
//3 ~ 6 again.

//cali_lookup_tbl

//tbl[12][4]   [surface][sensor], each sensor has own eeprom address
//- update(address, value)
// -- eeprom
//- get(address)
// -- eeprom
