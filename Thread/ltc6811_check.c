/**
 * @file ltc6811_check.c
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
#include "ltc6811_check.h"
#include "analog.h"
#include "rtthread.h"
#include "adc.h"
#include "main.h"
#include "system.h"
#include "Misaka_FSC_Station.h"
#include "ltc6811_thread.h"

static char ltc6811_check_thread_stack[256];
static struct rt_thread ltc6811_check_thread;

uint32_t ltc6811_vref2 = 0;
uint32_t ltc6811_vreg = 0;

void ltc6811_check_thread_entry(void* parameter)
{
    while (1)
    {
        rt_uint32_t e;
        if (rt_event_recv(&ltc6811_event, EVENT_LTC6811_READ_STATUS,
                          RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        {
//            ltc6811_vref2 = Get_5_Voltage_NF(ADC_CHANNEL_3, 10);
//            ltc6811_vreg = Get_5_Voltage_NF(ADC_CHANNEL_4, 10);
            Misaka_FSC_Station_BMS_Min_Bat_LTC6811_Status_Send();

            rt_thread_mdelay(200);
        }
    }
}

static int ltc6811_check_thread_setup(void)
{
    rt_thread_init(&ltc6811_check_thread,
                   "ltc6811_check_thread",
                   ltc6811_check_thread_entry,
                   RT_NULL,
                   &ltc6811_check_thread_stack[0],
                   sizeof(ltc6811_check_thread_stack),
                   16, 100);
    rt_thread_startup(&ltc6811_check_thread);
    return 0;
}

INIT_APP_EXPORT(ltc6811_check_thread_setup);
