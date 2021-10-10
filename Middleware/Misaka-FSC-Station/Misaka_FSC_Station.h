/**
 * @file Misaka_FSC_Station.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-04
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-04 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#ifndef __MISAKA_FSC_STATION_H__
#define __MISAKA_FSC_STATION_H__

#include "stdint.h"

#define MISAKA_FSC_STATION_FUNCTION_BMS_MIN_VOLTAGE                 ((uint16_t) 1)
#define MISAKA_FSC_STATION_FUNCTION_BMS_MIN_TEMPERATURE             ((uint16_t) 2)
#define MISAKA_FSC_STATION_FUNCTION_BMS_MIN_CURRENT                 ((uint16_t) 3)
#define MISAKA_FSC_STATION_FUNCTION_BMS_MIN_LTC6811_STATUS          ((uint16_t) 4)
#define MISAKA_FSC_STATION_FUNCTION_BMS_MIN_CPU_STATUS              ((uint16_t) 5)



#define MISAKA_FSC_STATION_HEAD1    0xFF
#define MISAKA_FSC_STATION_HEAD2    0xFE

#define MISAKA_FSC_STATION_END1     0xEF
#define MISAKA_FSC_STATION_END2     0xEE

#define BYTE0(data)  (*((uint8_t *)(&data)))
#define BYTE1(data)  (*((uint8_t *)(&data)+1))
#define BYTE2(data)  (*((uint8_t *)(&data)+2))
#define BYTE3(data)  (*((uint8_t *)(&data)+3))

extern uint8_t misaka_fsc_station_data_buf[100];

void Misaka_FSC_Station_Data_Send(uint8_t* buf, uint32_t cnt);

void Misaka_FSC_Station_BMS_Min_Bat_Voltage_Send();

void Misaka_FSC_Station_BMS_Min_Bat_Temperature_Send();

void Misaka_FSC_Station_BMS_Min_Bat_Current_Send();

void Misaka_FSC_Station_BMS_Min_Bat_LTC6811_Status_Send();

void Misaka_FSC_Station_BMS_Min_Bat_CPU_Status_Send();
#endif
