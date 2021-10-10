/**
 * @file Misaka_Filter.h
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
#ifndef __MISAKA_FILTER_H__
#define __MISAKA_FILTER_H__

#include "stdint.h"

typedef struct
{
    float last_data;
    float factor;
} Misaka_Filter_LPF_Struct;

typedef struct
{
    uint32_t last_data;
    uint32_t factor;
    uint32_t multiple;
} Misaka_Filter_NF_LPF_Struct;

uint32_t Misaka_Filter_NF_LPF(Misaka_Filter_NF_LPF_Struct* obj, uint32_t value);
float Misaka_Filter_LPF(Misaka_Filter_LPF_Struct* obj, uint32_t value);

#endif
