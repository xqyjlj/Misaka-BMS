/**
 * @file adc_mux.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-09-01
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-09-01 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#ifndef __ADC_MUX__H
#define __ADC_MUX__H

#include "stdint.h"
#include "analog.h"

typedef struct
{
    Misaka_Filter_NF_LPF_Struct filter;
    uint32_t voltage;
} Adc_Mux_Voltage_Struct;

#endif
