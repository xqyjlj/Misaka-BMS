/**
 * @file self_status.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-05
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-05 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#ifndef __SELF_STATUS_H__
#define __SELF_STATUS_H__

#include "stdint.h"

#define STM32_VERSION   1

extern uint32_t stm32_temperature;
extern uint8_t  cpu_usage_major;
extern uint8_t  cpu_usage_minor;
extern uint32_t stm32_power_5_V;

#endif


