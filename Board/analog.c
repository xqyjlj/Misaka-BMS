/**
 * @file analog.c
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-03
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-03 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#include "analog.h"
#include "main.h"
#include "adc.h"
#include "rtthread.h"
#include "eeprom.h"

static struct rt_mutex analog_mutex;
/**
 * @brief                   获取通道ch的ADC值
 * @param  ch               通道
 * @return uint16_t @c      通道ch的ADC值
 */
uint16_t analog_get_adc(uint32_t ch)
{
    rt_mutex_take(&analog_mutex, RT_WAITING_FOREVER);

    LL_ADC_StartCalibration(ADC1);

    uint32_t time = 0;
    while (!LL_ADC_IsCalibrationOnGoing(ADC1))
    {
        if (time < 1000)
        {
            time++;
        }
        else
        {
            return 0;
        }
    }

    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, ch);
    LL_ADC_SetChannelSamplingTime(ADC1, ch, LL_ADC_SAMPLINGTIME_239CYCLES_5);

    LL_ADC_REG_StartConversionSWStart(ADC1);
    time = 0;
    while (!LL_ADC_IsActiveFlag_EOS(ADC1))
    {
        if (time < 1000)
        {
            time++;
        }
        else
        {
            return 0;
        }
    }

    uint16_t data = LL_ADC_REG_ReadConversionData12(ADC1);
    rt_mutex_release(&analog_mutex);
    return data;
}

// /**
//  * @brief                   获取指定通道的转换值，取times次，然后平均(浮点数)，被放大1000倍
//  * @param  ch               通道
//  * @param  times            获取次数
//  * @return float @c         通道ch的times次转换结果平均值
//  */
// float Get_5_Voltage(uint32_t ch, uint8_t times)
// {
//     uint32_t temp_val = 0;
//     // HAL_ADCEx_Calibration_Start(&hadc1);
//     uint8_t t;
//     for (t = 0; t < times; t++)
//     {
//         temp_val += Get_ADC(ch);
//     }

//     float temp = temp_val / times;
//     temp *= 1.34277;
//     return (temp);
// }

// /**
//  * @brief                   获取指定通道的转换值，取times次，然后平均，被放大100000000倍
//  * @param  ch               通道
//  * @param  times            获取次数
//  * @return uint32_t @c      通道ch的times次转换结果平均值
//  */
// uint32_t Get_5_Voltage_NF(uint32_t ch, uint8_t times)
// {
//     uint32_t temp_val = 0;
//     // HAL_ADCEx_Calibration_Start(&hadc1);
//     uint8_t t;
//     for (t = 0; t < times; t++)
//     {
//         temp_val += Get_ADC(ch);
//     }

//     uint32_t temp = temp_val / times;
//     temp *= 134277;
//     temp = temp;
//     return (temp);
// }

// /**
//  * @brief                   获取指定通道的转换值，取times次，然后平均，被放大100000000倍
//  * @param  ch               通道
//  * @param  times            获取次数
//  * @return uint32_t @c      通道ch的times次转换结果平均值
//  */
// uint32_t Get_3_3_Voltage_NF(uint32_t ch, uint8_t times)
// {
//     uint32_t temp_val = 0;
//     // HAL_ADCEx_Calibration_Start(&hadc1);
//     uint8_t t;
//     for (t = 0; t < times; t++)
//     {
//         temp_val += Get_ADC(ch);
//     }

//     rt_mutex_release(&analog_mutex);

//     uint32_t temp = temp_val / times;
//     temp *= 80566;
//     temp = temp;
//     return (temp);
// }

// /**
//  * @brief                   通过一阶低通滤波器获取指定通道的转换值，取times次，然后平均，被放大1000倍
//  * @param  ch               通道
//  * @param  times            获取次数
//  * @param  obj              滤波器对象
//  * @return uint32_t @c
//  */
// uint32_t Get_5_Voltage_NF_LPF(uint32_t ch, uint8_t times, Misaka_Filter_NF_LPF_Struct* obj)
// {
//     uint32_t voltage = Get_5_Voltage_NF(ch, times);
//     return Misaka_Filter_NF_LPF(obj, voltage);
// }

// /**
//  * @brief                   通过一阶低通滤波器获取指定通道的转换值，取times次，然后平均，被放大1000倍
//  * @param  ch               通道
//  * @param  times            获取次数
//  * @param  obj              滤波器对象
//  * @return uint32_t @c
//  */
// uint32_t Get_3_3_Voltage_NF_LPF(uint32_t ch, uint8_t times, Misaka_Filter_NF_LPF_Struct* obj)
// {
//     uint32_t voltage = Get_3_3_Voltage_NF(ch, times);
//     return Misaka_Filter_NF_LPF(obj, voltage);
// }

// /**
//  * @brief                   通过一阶低通滤波器获取指定通道的转换值，取times次，然后平均(浮点数)，被放大1000倍
//  * @param  ch               通道
//  * @param  times            获取次数
//  * @param  obj              滤波器对象
//  * @return float @c
//  */
// float Get_5_Voltage_LPF(uint32_t ch, uint8_t times, Misaka_Filter_LPF_Struct* obj)
// {
//     float voltage = Get_5_Voltage(ch, times);
//     return Misaka_Filter_LPF(obj, voltage);
// }

static int analog_init()
{
    rt_mutex_init(&analog_mutex, "analog_mutex", RT_IPC_FLAG_FIFO);
    return 0;
}

INIT_COMPONENT_EXPORT(analog_init);


