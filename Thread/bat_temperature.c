/**
 * @file bat_temperature.c
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
#include "bat_temperature.h"
#include "temperature.h"
#include "rtthread.h"
#include "Misaka_LTC6811.h"
#include "ltc6811_thread.h"
#include "Misaka_FSC_Station.h"

static char bat_temperature_thread_stack[256];
static struct rt_thread bat_temperature_thread;

void bat_temperature_thread_entry(void* parameter)
{
    while (1)
    {
        rt_uint32_t e;
        if (rt_event_recv(&ltc6811_event, EVENT_LTC6811_READ_AUXILIARY_VOLTAGE,
                          RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                          RT_WAITING_FOREVER, &e) == RT_EOK)
        {
            for (uint8_t i = 1; i <= 8; i++)
            {
                // Read_STM32_ADC_Group_Voltage(i);
            }

            // for (uint8_t i = 0; i < 5; i++)
            // {
            //     Temperature[i].voltage = Misaka_LTC6811_Device_Object[0].GPIOVolt[i] * 10000;
            // }

            // for (uint8_t i = 0; i < 45; i++)
            // {
            //     Get_Temperature(EKX_NTC_Voltage_Table_100K_4150, &Temperature[i]);
            // }

            // Misaka_FSC_Station_BMS_Min_Bat_Temperature_Send();
        }
    }
}

/**
 * @brief            bat_temperature线程初始化函数
 * @return int @c
 */
static int bat_temperature_thread_setup(void)
{
    rt_thread_init(&bat_temperature_thread,
                   "bat_temperature_thread",
                   bat_temperature_thread_entry,
                   RT_NULL,
                   &bat_temperature_thread_stack[0],
                   sizeof(bat_temperature_thread_stack),
                   15, 100);
    rt_thread_startup(&bat_temperature_thread);
    return 0;
}

INIT_APP_EXPORT(bat_temperature_thread_setup);






