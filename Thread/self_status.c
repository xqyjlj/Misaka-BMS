/**
 * @file self_status.c
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
#include "self_status.h"
#include "analog.h"
#include "rtthread.h"
#include "adc.h"
#include "main.h"
#include "system.h"
#include "temperature.h"
#include "Misaka_FSC_Station.h"

#define LOG_NAME "self_status"

#define CPU_USAGE_CALC_TICK    1000
#define CPU_USAGE_LOOP        100

uint8_t  cpu_usage_major = 0, cpu_usage_minor = 0;
static uint32_t total_count = 0;

static void cpu_usage_idle_hook()
{
    uint32_t tick;
    uint32_t count;
    volatile uint32_t loop;

    if (total_count == 0)
    {
        /* get total count */
        rt_enter_critical();
        tick = rt_tick_get();
        while (rt_tick_get() - tick < CPU_USAGE_CALC_TICK)
        {
            total_count ++;
            loop = 0;
            while (loop < CPU_USAGE_LOOP) loop ++;
        }
        rt_exit_critical();
    }

    count = 0;
    /* get CPU usage */
    tick = rt_tick_get();
    while (rt_tick_get() - tick < CPU_USAGE_CALC_TICK)
    {
        count ++;
        loop  = 0;
        while (loop < CPU_USAGE_LOOP) loop ++;
    }

    /* calculate major and minor */
    if (count < total_count)
    {
        count = total_count - count;
        cpu_usage_major = (count * 100) / total_count;
        cpu_usage_minor = ((count * 100) % total_count) * 100 / total_count;
    }
    else
    {
        total_count = count;

        /* no CPU usage */
        cpu_usage_major = 0;
        cpu_usage_minor = 0;
    }
}

static char self_status_thread_stack[256];
static struct rt_thread self_status_thread;

uint32_t stm32_temperature = 0;
uint32_t stm32_power_5_V = 0;
void self_status_thread_entry(void* parameter)
{
    while (1)
    {
        // stm32_temperature = Get_STM32_Temperature_NF_LPF();
//        stm32_power_5_V = Get_5_Voltage_NF(ADC_CHANNEL_1, 1);
        Misaka_FSC_Station_BMS_Min_Bat_CPU_Status_Send();
        rt_thread_mdelay(500);
    }
}

static int self_status_thread_setup(void)
{
    rt_thread_idle_sethook(cpu_usage_idle_hook);
    rt_thread_init(&self_status_thread,
                   "self_status_thread",
                   self_status_thread_entry,
                   RT_NULL,
                   &self_status_thread_stack[0],
                   sizeof(self_status_thread_stack),
                   17, 100);
    rt_thread_startup(&self_status_thread);
    return 0;
}

INIT_APP_EXPORT(self_status_thread_setup);


