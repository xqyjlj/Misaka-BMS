/**
 * @file bat_voltage.c
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
#include "bat_voltage.h"
#include "Misaka_LTC6811.h"
#include "rtthread.h"
#include "ltc6811_thread.h"
#include "Misaka_FSC_Station.h"
#include "system.h"

#define LOG_NAME "bat_voltage"

static char bat_voltage_thread_stack[512];
static struct rt_thread bat_voltage_thread;

void bat_voltage_thread_entry(void* parameter)
{
    while (1)
    {
        rt_uint32_t e;
        if (rt_event_recv(&ltc6811_event, EVENT_LTC6811_READ_CELL_VOLTAGE,
                          RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        {
            Misaka_FSC_Station_BMS_Min_Bat_Voltage_Send();
        }
    }
}

/**
 * @brief
 * @return int @c
 */
static int bat_voltage_thread_setup(void)
{
    rt_thread_init(&bat_voltage_thread,
                   "bat_voltage_thread",
                   bat_voltage_thread_entry,
                   RT_NULL,
                   &bat_voltage_thread_stack[0],
                   sizeof(bat_voltage_thread_stack),
                   8, 100);
    rt_thread_startup(&bat_voltage_thread);

    return 0;
}

INIT_APP_EXPORT(bat_voltage_thread_setup);

