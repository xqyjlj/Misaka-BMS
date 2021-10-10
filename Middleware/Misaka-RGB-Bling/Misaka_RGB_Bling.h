/**
 * @file Misaka_RGB_Bling.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-01
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-01 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */

#ifndef __MISAKA_RGB_BLING__H__
#define __MISAKA_RGB_BLING__H__

#include "stdint.h"

typedef enum
{
    Misaka_Bling_Color_None = 0,
    Misaka_Bling_Color_Red,
    Misaka_Bling_Color_Green,
    Misaka_Bling_Color_Blue,
    Misaka_Bling_Color_Yellow,
    Misaka_Bling_Color_Cyan,
    Misaka_Bling_Color_White,
    Misaka_Bling_Color_Purple,
} Misaka_Bling_Color_Enum;

typedef struct
{
    Misaka_Bling_Color_Enum color1;
    Misaka_Bling_Color_Enum color2;
    uint32_t contiune_time;//闪烁持续时间
    uint32_t color1_cnt;//颜色1计数器
    uint16_t period_cnt;//颜色2计数器
    uint16_t cnt;//闪烁计数器
    uint8_t endless_flag;//无尽模式
    uint16_t time_base;//时间基数
} Misaka_Bling_Struct;

void Misaka_Set_Bling_GPIO(Misaka_Bling_Color_Enum color);

void Misaka_Bling_Init(uint16_t time_base);

void Misaka_Bling_Mode_Set(Misaka_Bling_Color_Enum color1,
                           Misaka_Bling_Color_Enum color2,
                           uint32_t color1_time,
                           uint32_t color2_time,
                           uint16_t cnt,
                           uint8_t endless_flag);

void Misaka_Bling_Cycle_Process();
#endif
