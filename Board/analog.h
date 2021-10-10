/**
 * @file analog.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-03
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-03 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#ifndef __ANALOG_H__
#define __ANALOG_H__

#include "stdint.h"
#include "Misaka_Filter.h"

uint16_t analog_get_adc(uint32_t ch);
// float Get_5_Voltage(uint32_t ch, uint8_t times);
// uint32_t Get_5_Voltage_NF(uint32_t ch, uint8_t times);
// uint32_t Get_3_3_Voltage_NF(uint32_t ch, uint8_t times);
// uint32_t Get_5_Voltage_NF_LPF(uint32_t ch, uint8_t times, Misaka_Filter_NF_LPF_Struct* obj);
// uint32_t Get_3_3_Voltage_NF_LPF(uint32_t ch, uint8_t times, Misaka_Filter_NF_LPF_Struct* obj);
// float Get_5_Voltage_LPF(uint32_t ch, uint8_t times, Misaka_Filter_LPF_Struct* obj);
#endif
