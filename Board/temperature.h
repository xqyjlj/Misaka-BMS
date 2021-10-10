/**
 * @file temperature.h
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
#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

#include "stdint.h"
#include "analog.h"

#define EKX_NTC_TABLE_100K_4150_COUNT   101

typedef struct
{
    uint8_t temperature;
    uint8_t temperature_f;
} BMS_Temperature_Struct;

uint8_t get_temperature(uint32_t* table, uint32_t voltage, BMS_Temperature_Struct* obj);

extern BMS_Temperature_Struct BMS_Temperature[80];
extern uint32_t EKX_NTC_Voltage_Table_100K_4150[EKX_NTC_TABLE_100K_4150_COUNT];

#endif
