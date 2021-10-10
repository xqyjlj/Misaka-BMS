/**
 * @file Misaka_Beep.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-02
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-02 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */

#ifndef __MISAKA_BEEP_H__
#define __MISAKA_BEEP_H__

#include "stdint.h"

typedef struct
{
    uint32_t contiune_time;//鸣叫持续时间
    uint32_t beep_cnt;//颜色1计数器
    uint16_t period_cnt;//颜色2计数器
    uint16_t cnt;//闪烁计数器
    uint8_t endless_flag;//无尽模式
    uint16_t time_base;//时间基数
} Misaka_Beep_Struct;

void Misaka_Set_Beep_GPIO(uint8_t status);

void Misaka_Beep_Init(uint16_t time_base);

void Misaka_Beep_Mode_Set(uint32_t beep_time,
                          uint32_t nbeep_time,
                          uint16_t cnt,
                          uint8_t endless_flag);

void Misaka_Beep_Cycle_Process();

#endif
