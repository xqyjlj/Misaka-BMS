/**
 * @file Misaka_FSC_Station.c
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
#include "Misaka_FSC_Station.h"
#include "Misaka_LTC6811.h"
#include "temperature.h"
#include "rtthread.h"
#include "bat_current.h"
#include "ltc6811_check.h"
#include "self_status.h"


static struct rt_mutex misaka_fsc_station_mutex;
uint8_t misaka_fsc_station_data_buf[100] = {0}; //待发送数据缓冲区

void Misaka_FSC_Station_BMS_Min_Bat_Voltage_Send()
{
    uint8_t cnt = 0;
    uint8_t sum = 0;

    rt_mutex_take(&misaka_fsc_station_mutex, RT_WAITING_FOREVER);

    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD1;
    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD2;
    misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_VOLTAGE >> 8);
    misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_VOLTAGE >> 0);
    misaka_fsc_station_data_buf[cnt++] = 0;

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].CellVolt[0]);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].CellVolt[0]);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].CellVolt[1]);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].CellVolt[1]);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].CellVolt[2]);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].CellVolt[2]);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].CellVolt[3]);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].CellVolt[3]);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].CellVolt[6]);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].CellVolt[6]);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].CellVolt[7]);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].CellVolt[7]);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].CellVolt[8]);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].CellVolt[8]);

    misaka_fsc_station_data_buf[cnt++] = BYTE3(Misaka_LTC6811_Device_Object[0].TotalVolt);
    misaka_fsc_station_data_buf[cnt++] = BYTE2(Misaka_LTC6811_Device_Object[0].TotalVolt);
    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].TotalVolt);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].TotalVolt);

    misaka_fsc_station_data_buf[4] = cnt - 5;

    for (uint8_t i = 0; i < cnt; i++)
    {
        sum ^= misaka_fsc_station_data_buf[i];
    }

    misaka_fsc_station_data_buf[cnt++] = sum;

    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END1;
    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END2;

    Misaka_FSC_Station_Data_Send(misaka_fsc_station_data_buf, cnt);

    rt_mutex_release(&misaka_fsc_station_mutex);
}

void Misaka_FSC_Station_BMS_Min_Bat_Temperature_Send()
{
    // uint8_t cnt = 0;
    // uint8_t sum = 0;

    // rt_mutex_take(&misaka_fsc_station_mutex, RT_WAITING_FOREVER);

    // misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD1;
    // misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD2;
    // misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_TEMPERATURE >> 8);
    // misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_TEMPERATURE >> 0);
    // misaka_fsc_station_data_buf[cnt++] = 0;

    // for (uint8_t i = 0; i < 45; i++)
    // {
    //     misaka_fsc_station_data_buf[cnt++] = Temperature[i].temperature;
    //     misaka_fsc_station_data_buf[cnt++] = Temperature[i].temperature_f;
    // }

    // misaka_fsc_station_data_buf[4] = cnt - 5;

    // for (uint8_t i = 0; i < cnt; i++)
    // {
    //     sum ^= misaka_fsc_station_data_buf[i];
    // }

    // misaka_fsc_station_data_buf[cnt++] = sum;

    // misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END1;
    // misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END2;

    // Misaka_FSC_Station_Data_Send(misaka_fsc_station_data_buf, cnt);

    // rt_mutex_release(&misaka_fsc_station_mutex);
}

void Misaka_FSC_Station_BMS_Min_Bat_Current_Send()
{
    uint8_t cnt = 0;
    uint8_t sum = 0;

    rt_mutex_take(&misaka_fsc_station_mutex, RT_WAITING_FOREVER);

    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD1;
    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD2;
    misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_CURRENT >> 8);
    misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_CURRENT >> 0);
    misaka_fsc_station_data_buf[cnt++] = 0;

    misaka_fsc_station_data_buf[cnt++] = BYTE3(bat_current);
    misaka_fsc_station_data_buf[cnt++] = BYTE2(bat_current);
    misaka_fsc_station_data_buf[cnt++] = BYTE1(bat_current);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(bat_current);

    misaka_fsc_station_data_buf[cnt++] = charge_flag;

    uint32_t power = power_2_5_V * 2;
    misaka_fsc_station_data_buf[cnt++] = BYTE3(power);
    misaka_fsc_station_data_buf[cnt++] = BYTE2(power);
    misaka_fsc_station_data_buf[cnt++] = BYTE1(power);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(power);

    misaka_fsc_station_data_buf[4] = cnt - 5;

    for (uint8_t i = 0; i < cnt; i++)
    {
        sum ^= misaka_fsc_station_data_buf[i];
    }

    misaka_fsc_station_data_buf[cnt++] = sum;

    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END1;
    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END2;

    Misaka_FSC_Station_Data_Send(misaka_fsc_station_data_buf, cnt);

    rt_mutex_release(&misaka_fsc_station_mutex);
}

void Misaka_FSC_Station_BMS_Min_Bat_LTC6811_Status_Send()
{
    uint8_t cnt = 0;
    uint8_t sum = 0;

    rt_mutex_take(&misaka_fsc_station_mutex, RT_WAITING_FOREVER);

    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD1;
    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD2;
    misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_LTC6811_STATUS >> 8);
    misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_LTC6811_STATUS >> 0);
    misaka_fsc_station_data_buf[cnt++] = 0;

    misaka_fsc_station_data_buf[cnt++] = BYTE3(ltc6811_vref2);
    misaka_fsc_station_data_buf[cnt++] = BYTE2(ltc6811_vref2);
    misaka_fsc_station_data_buf[cnt++] = BYTE1(ltc6811_vref2);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(ltc6811_vref2);

    misaka_fsc_station_data_buf[cnt++] = BYTE3(ltc6811_vreg);
    misaka_fsc_station_data_buf[cnt++] = BYTE2(ltc6811_vreg);
    misaka_fsc_station_data_buf[cnt++] = BYTE1(ltc6811_vreg);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(ltc6811_vreg);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].ITM);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].ITM);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].REFVolt);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].REFVolt);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].VAVolt);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].VAVolt);

    misaka_fsc_station_data_buf[cnt++] = BYTE1(Misaka_LTC6811_Device_Object[0].VDVolt);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(Misaka_LTC6811_Device_Object[0].VDVolt);

    misaka_fsc_station_data_buf[cnt++] = Misaka_LTC6811_Device_Object[0].REV;

    misaka_fsc_station_data_buf[4] = cnt - 5;

    for (uint8_t i = 0; i < cnt; i++)
    {
        sum ^= misaka_fsc_station_data_buf[i];
    }

    misaka_fsc_station_data_buf[cnt++] = sum;

    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END1;
    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END2;

    Misaka_FSC_Station_Data_Send(misaka_fsc_station_data_buf, cnt);

    rt_mutex_release(&misaka_fsc_station_mutex);
}

void Misaka_FSC_Station_BMS_Min_Bat_CPU_Status_Send()
{
    uint8_t cnt = 0;
    uint8_t sum = 0;

    rt_mutex_take(&misaka_fsc_station_mutex, RT_WAITING_FOREVER);

    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD1;
    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_HEAD2;
    misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_CPU_STATUS >> 8);
    misaka_fsc_station_data_buf[cnt++] = (uint8_t)(MISAKA_FSC_STATION_FUNCTION_BMS_MIN_CPU_STATUS >> 0);
    misaka_fsc_station_data_buf[cnt++] = 0;

    misaka_fsc_station_data_buf[cnt++] = BYTE3(stm32_temperature);
    misaka_fsc_station_data_buf[cnt++] = BYTE2(stm32_temperature);
    misaka_fsc_station_data_buf[cnt++] = BYTE1(stm32_temperature);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(stm32_temperature);

    misaka_fsc_station_data_buf[cnt++] = cpu_usage_major;
    misaka_fsc_station_data_buf[cnt++] = cpu_usage_minor;

    misaka_fsc_station_data_buf[cnt++] = BYTE3(stm32_power_5_V);
    misaka_fsc_station_data_buf[cnt++] = BYTE2(stm32_power_5_V);
    misaka_fsc_station_data_buf[cnt++] = BYTE1(stm32_power_5_V);
    misaka_fsc_station_data_buf[cnt++] = BYTE0(stm32_power_5_V);

    misaka_fsc_station_data_buf[cnt++] = STM32_VERSION;

    misaka_fsc_station_data_buf[4] = cnt - 5;

    for (uint8_t i = 0; i < cnt; i++)
    {
        sum ^= misaka_fsc_station_data_buf[i];
    }

    misaka_fsc_station_data_buf[cnt++] = sum;

    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END1;
    misaka_fsc_station_data_buf[cnt++] = MISAKA_FSC_STATION_END2;

    Misaka_FSC_Station_Data_Send(misaka_fsc_station_data_buf, cnt);

    rt_mutex_release(&misaka_fsc_station_mutex);
}


static int Misaka_FSC_Station_Init()
{
    rt_mutex_init(&misaka_fsc_station_mutex, "misaka_fsc_station_mutex", RT_IPC_FLAG_FIFO);
    return 0;
}

INIT_COMPONENT_EXPORT(Misaka_FSC_Station_Init);





















