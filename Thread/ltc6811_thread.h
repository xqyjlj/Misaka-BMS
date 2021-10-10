/**
 * @file ltc6811_thread.h
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
#ifndef __LTC6811_THREAD_H__
#define __LTC6811_THREAD_H__

#include "rtthread.h"

extern struct rt_event ltc6811_event;

#define EVENT_LTC6811_READ_CELL_VOLTAGE                 (1 << 0)
#define EVENT_LTC6811_READ_AUXILIARY_VOLTAGE            (1 << 1)
#define EVENT_LTC6811_READ_STATUS                       (1 << 2)
#define EVENT_LTC6811_NEED_BALANCE                      (1 << 3)




#endif
