/**
 * @file bat_current.c
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
#include "bat_current.h"
#include "analog.h"
#include "rtthread.h"
#include "eeprom.h"
#include "adc.h"
#include "main.h"
#include "system.h"
#include "Misaka_FSC_Station.h"

static char bat_current_thread_stack[256];
static struct rt_thread bat_current_thread;

static Misaka_Filter_NF_LPF_Struct bat_current_filter = {0};
static uint32_t bat_current_voltage = 0;//被放大100000000
uint32_t bat_current = 0;//被放大100000000
uint8_t charge_flag = 0;
uint32_t power_2_5_V = 0;

void read_current()
{
//    power_2_5_V = Get_5_Voltage_NF(ADC_CHANNEL_1, 10) / 2;
//    bat_current_voltage = Get_5_Voltage_NF_LPF(ADC_CHANNEL_2, 1, &bat_current_filter);
    if (bat_current_voltage > power_2_5_V)
    {
        charge_flag = 0;
    }
    else
    {
        charge_flag = 1;
    }
    bat_current = ABS(bat_current_voltage - power_2_5_V) / 10000000;
}

void bat_current_thread_entry(void* parameter)
{
    while (1)
    {
        read_current();
        Misaka_FSC_Station_BMS_Min_Bat_Current_Send();
        rt_thread_mdelay(100);
    }
}

static int bat_current_thread_setup(void)
{
    uint32_t LPF_factor = 1;
    if (Eeprom_Read_Uint32(&LPF_factor, EEPROM_TABLE_CURRENT_LPF_FACTOR))
    {
        LPF_factor = DEFAULT_CURRENT_LPF_FACTOR;
    }

    bat_current_filter.factor = LPF_factor;
    bat_current_filter.multiple = 100000;

    rt_thread_init(&bat_current_thread,
                   "bat_current_thread",
                   bat_current_thread_entry,
                   RT_NULL,
                   &bat_current_thread_stack[0],
                   sizeof(bat_current_thread_stack),
                   8, 100);
    rt_thread_startup(&bat_current_thread);
    return 0;
}

INIT_APP_EXPORT(bat_current_thread_setup);





