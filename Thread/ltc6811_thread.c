/**
 * @file ltc6811_thread.c
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
#include "ltc6811_thread.h"
#include "Misaka_LTC6811.h"
#include "eeprom.h"

static struct rt_mutex ltc6811_mutex;
struct rt_event ltc6811_event;
Misaka_LTC6811_CFGR_Struct  ltc6811_cfgr = {0};

static char ltc6811_thread_stack[512];
static struct rt_thread ltc6811_thread;

void ltc6811_thread_entry(void* parameter)
{
    uint16_t i = 0;
    while (1)
    {
        rt_mutex_take(&ltc6811_mutex, RT_WAITING_FOREVER);

        Misaka_LTC6811_Read_All_Cell_Voltage(LTC6811_MD10, LTC6811_DCP0, LTC6811_CH000);
        Misaka_LTC6811_Read_All_Status(LTC6811_MD10, LTC6811_CHST000);
        rt_event_send(&ltc6811_event, EVENT_LTC6811_READ_CELL_VOLTAGE);
        rt_event_send(&ltc6811_event, EVENT_LTC6811_READ_STATUS);

        if (i >= 500)
        {
            Misaka_LTC6811_Read_All_Auxiliary_Voltage(LTC6811_MD10, LTC6811_CHG000);
            rt_event_send(&ltc6811_event, EVENT_LTC6811_READ_AUXILIARY_VOLTAGE);
            i = 0;
        }
        i++;
        rt_mutex_release(&ltc6811_mutex);
    }
}

static char ltc6811_open_wire_check_thread_stack[512];
static struct rt_thread ltc6811_open_wire_check_thread;

void ltc6811_open_wire_check_thread_entry(void* parameter)
{
    while (1)
    {
        rt_mutex_take(&ltc6811_mutex, RT_WAITING_FOREVER);
        Misaka_LTC6811_Open_Wire_Check(LTC6811_MD10, LTC6811_DCP0, LTC6811_CH000);
        rt_mutex_release(&ltc6811_mutex);
        rt_thread_mdelay(30000);//1000ms * 30 = 30000 = 30s
    }
}

static char ltc6811_self_test_thread_stack[512];
static struct rt_thread ltc6811_self_test_thread;

void ltc6811_self_test_thread_entry(void* parameter)
{
    while (1)
    {
        rt_mutex_take(&ltc6811_mutex, RT_WAITING_FOREVER);
        Misaka_LTC6811_Cell_Voltage_Self_Test(LTC6811_MD10, LTC6811_ST10, LTC6811_ST10_7kHz_STC);
        Misaka_LTC6811_Auxiliary_Voltage_Self_Test(LTC6811_MD10, LTC6811_ST10, LTC6811_ST10_7kHz_STC);
        Misaka_LTC6811_Status_Self_Test(LTC6811_MD10, LTC6811_ST10, LTC6811_ST10_7kHz_STC);
        rt_mutex_release(&ltc6811_mutex);
        rt_thread_mdelay(3600000);//1000ms * 3600 = 3600000 = 1h
    }
}

static char ltc6811_balance_thread_stack[512];
static struct rt_thread ltc6811_balance_thread;

void ltc6811_balance_thread_entry(void* parameter)
{
    while (1)
    {
        rt_uint32_t e;
        if (rt_event_recv(&ltc6811_event, EVENT_LTC6811_NEED_BALANCE,
                          RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                          500, &e) == RT_EOK)
        {
            rt_mutex_take(&ltc6811_mutex, RT_WAITING_FOREVER);
            Misaka_LTC6811_Balance_Group(2);
            rt_mutex_release(&ltc6811_mutex);
            rt_thread_mdelay(20000);//1000ms * 20 = 20000 = 20s


            rt_mutex_take(&ltc6811_mutex, RT_WAITING_FOREVER);
            Misaka_LTC6811_Balance_Group(1);
            rt_mutex_release(&ltc6811_mutex);
            rt_thread_mdelay(20000);//1000ms * 20 = 20000 = 20s
        }
        else
        {
            rt_mutex_take(&ltc6811_mutex, RT_WAITING_FOREVER);
            Misaka_LTC6811_Balance_Group(0);
            rt_mutex_release(&ltc6811_mutex);
            rt_thread_mdelay(2000);//1000ms * 2 = 2000 = 2s
        }
    }
}

/**
 * @brief            ltc6811线程初始化函数
 * @return int @c
 */
static int ltc6811_setup(void)
{
    rt_event_init(&ltc6811_event, "ltc6811_event", RT_IPC_FLAG_PRIO);
    rt_mutex_init(&ltc6811_mutex, "ltc6811_mutex", RT_IPC_FLAG_FIFO);

    rt_thread_init(&ltc6811_thread,
                   "ltc6811_thread",
                   ltc6811_thread_entry,
                   RT_NULL,
                   &ltc6811_thread_stack[0],
                   sizeof(ltc6811_thread_stack),
                   10, 100);
    rt_thread_startup(&ltc6811_thread);

    rt_thread_init(&ltc6811_open_wire_check_thread,
                   "ltc6811_open_wire_check_thread",
                   ltc6811_open_wire_check_thread_entry,
                   RT_NULL,
                   &ltc6811_open_wire_check_thread_stack[0],
                   sizeof(ltc6811_open_wire_check_thread_stack),
                   9, 100);
    rt_thread_startup(&ltc6811_open_wire_check_thread);

    rt_thread_init(&ltc6811_self_test_thread,
                   "ltc6811_self_test_thread",
                   ltc6811_self_test_thread_entry,
                   RT_NULL,
                   &ltc6811_self_test_thread_stack[0],
                   sizeof(ltc6811_self_test_thread_stack),
                   11, 100);

	rt_thread_startup(&ltc6811_self_test_thread);
				   
    rt_thread_init(&ltc6811_balance_thread,
                   "ltc6811_balance_thread",
                   ltc6811_balance_thread_entry,
                   RT_NULL,
                   &ltc6811_balance_thread_stack[0],
                   sizeof(ltc6811_balance_thread_stack),
                   12, 100);

    rt_thread_startup(&ltc6811_balance_thread);

    return 0;
}

INIT_APP_EXPORT(ltc6811_setup);

static int ltc6811_init()
{
    uint16_t vuv = 0;
    uint16_t vov = 0;
    if (Eeprom_Read_Uint16(&vuv, EEPROM_TABLE_VUV))
    {
        vuv = DEFAULT_VUV;
    }
    if (Eeprom_Read_Uint16(&vov, EEPROM_TABLE_VOV))
    {
        vov = DEFAULT_VOV;
    }

    Misaka_LTC6811_Device_Object[0].Cell_Select = 0x01CF;
    Misaka_LTC6811_Device_Object[0].GPIO_Select = 0x1F;

    ltc6811_cfgr.GPIOX = LTC6811_GPIO11111;
    ltc6811_cfgr.REFON = LTC6811_REFON1;
    ltc6811_cfgr.DTEN = LTC6811_DTEN1;
    ltc6811_cfgr.ADCOPT = LTC6811_ADCOPT0;

    ltc6811_cfgr.VUV = vuv;
    ltc6811_cfgr.VOV = vov;

    ltc6811_cfgr.DCTO = LTC6811_DCTO_30s;
    Misaka_LTC6811_WRCFGA(&ltc6811_cfgr);

    return 0;
}

INIT_COMPONENT_EXPORT(ltc6811_init);












