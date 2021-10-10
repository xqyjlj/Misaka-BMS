/**
 * @file adc_mux.c
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-09-01
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-09-01 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#include "adc_mux.h"
#include "rtthread.h"
#include "analog.h"
#include "adc.h"
#include "system.h"
#include "main.h"
#include "gpio.h"
#include "eeprom.h"
#include "temperature.h"

#define LOG_NAME "adc_mux"

void read_adc_mux(uint16_t* data)
{
    uint8_t count = 0;
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_0);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_1);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_2);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_3);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_4);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_5);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_6);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_7);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_8);
    rt_thread_mdelay(10);
    data[count++] = analog_get_adc(LL_ADC_CHANNEL_9);
    rt_thread_mdelay(10);
}

void set_adc_mux_key(uint8_t group)
{
    switch (group)
    {
    case 0:
    {
        LL_GPIO_ResetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 0
        LL_GPIO_ResetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 0
        LL_GPIO_ResetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 0
    }
    break;
    case 1:
    {
        LL_GPIO_ResetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 0
        LL_GPIO_ResetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 0
        LL_GPIO_SetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 1
    }
    break;
    case 2:
    {
        LL_GPIO_ResetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 0
        LL_GPIO_SetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 1
        LL_GPIO_ResetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 0
    }
    break;
    case 3:
    {
        LL_GPIO_ResetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 0
        LL_GPIO_SetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 1
        LL_GPIO_SetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 1
    }
    break;
    case 4:
    {
        LL_GPIO_SetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 1
        LL_GPIO_ResetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 0
        LL_GPIO_ResetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 0
    }
    break;
    case 5:
    {
        LL_GPIO_SetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 1
        LL_GPIO_ResetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 0
        LL_GPIO_SetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 1
    }
    break;
    case 6:
    {
        LL_GPIO_SetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 1
        LL_GPIO_SetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 1
        LL_GPIO_ResetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 0
    }
    break;
    case 7:
    {
        LL_GPIO_SetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 1
        LL_GPIO_SetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 1
        LL_GPIO_SetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 1
    }
    break;
    default:
    {
        LL_GPIO_ResetOutputPin(CH443K_SEL_GPIO_Port, CH443K_SEL_Pin);// 0
        LL_GPIO_ResetOutputPin(CH444G_IN1_GPIO_Port, CH444G_IN1_Pin);// 0
        LL_GPIO_ResetOutputPin(CH444G_IN0_GPIO_Port, CH444G_IN0_Pin);// 0
    }
    break;
    }

    rt_thread_mdelay(5);
}

static char adc_mux_thread_stack[512];
static struct rt_thread adc_mux_thread;

const int8_t bms_voltage_table[85] =
{
    - 1,    //0 GPIO4
        - 1,   //1 GPIO5
        - 1,   //2 GPIO2
        - 1,   //3 GPIO3
        44,    //4 ADC4_1_1
        - 1,   //5 GPIO1
        64,    //6 ADC4_1_3
        54,    //7 ADC4_1_2
        4,     //8 ADC4_0_1
        74,    //9 ADC4_1_4

        24,    //10 ADC4_0_3
        14,    //11 ADC4_0_2
        46,    //12 ADC6_1_1
        34,    //13 ADC4_0_4
        66,    //14 ADC6_1_3
        56,    //15 ADC6_1_2
        6,     //16 ADC6_0_1
        76,    //17 ADC6_1_4
        26,    //18 ADC6_0_3
        16,    //19 ADC6_0_2

        48,    //20 ADC8_1_1
        36,    //21 ADC6_0_4
        68,    //22 ADC8_1_3
        58,    //23 ADC8_1_2
        15,    //24 ADC5_0_2
        78,    //25 ADC8_1_4
        35,    //26 ADC5_0_4
        25,    //27 ADC5_0_3
        57,    //28 ADC7_1_2
        47,    //29 ADC7_1_1

        77,    //30 ADC7_1_4
        67,    //31 ADC7_1_3
        17,    //32 ADC7_0_2
        7,     //33 ADC7_0_1
        37,    //34 ADC7_0_4
        27,    //35 ADC7_0_3
        59,    //36 ADC9_1_2
        49,    //37 ADC9_1_1
        79,    //38 ADC9_1_4
        69,    //39 ADC9_1_3

        29,    //40 ADC9_0_3
        39,    //41 ADC9_0_4
        9,     //42 ADC9_0_1
        19,    //43 ADC9_0_2
        45,    //44 ADC5_1_1
        5,     //45 ADC5_0_1
        65,    //46 ADC5_1_3
        55,    //47 ADC5_1_2
        33,    //48 ADC3_0_4
        75,    //49 ADC5_1_4

        13,    //50 ADC3_0_2
        23,    //51 ADC3_0_3
        43,    //52 ADC3_1_1
        3,     //53 ADC3_0_1
        63,    //54 ADC3_1_3
        53,    //55 ADC3_1_2
        32,    //56 ADC2_0_4
        73,    //57 ADC3_1_4
        12,    //58 ADC2_0_2
        22,    //59 ADC2_0_3

        42,    //60 ADC2_1_1
        2,     //61 ADC2_0_1
        62,    //62 ADC2_1_3
        52,    //63 ADC2_1_2
        31,    //64 ADC1_0_4
        72,    //65 ADC2_1_4
        11,    //66 ADC1_0_2
        21,    //67 ADC1_0_3
        41,    //68 ADC1_1_1
        1,     //69 ADC1_0_1

        61,    //70 ADC1_1_3
        51,    //71 ADC1_1_2
        30,    //72 ADC0_0_4
        71,    //73 ADC1_1_4
        10,    //74 ADC0_0_2
        20,    //75 ADC0_0_3
        40,    //76 ADC0_1_1
        0,     //77 ADC0_0_1
        60,    //78 ADC0_1_3
        50,    //79 ADC0_1_2

        38,    //80 ADC8_0_4 CELL7
        28,    //81 ADC8_0_3 VREF2
        18,    //82 ADC8_0_2 VREG
        8,     //83 ADC8_0_1 5V
        70,    //84 ADC0_1_4
    };
static uint16_t stm32_adc_data[81] = {0};

Adc_Mux_Voltage_Struct adc_mux_voltage[80] = {0};

uint32_t voltage_5v = 0;
uint32_t voltage_cell7 = 0;
uint32_t voltage_vref2 = 0;
uint32_t voltage_vreg = 0;
void adc_mux_thread_entry(void* parameter)
{
    while (1)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            set_adc_mux_key(i);
            read_adc_mux(&stm32_adc_data[i * 10]);
        }
        stm32_adc_data[80] = analog_get_adc(LL_ADC_CHANNEL_TEMPSENSOR);

        for (uint8_t i = 0; i < 80; i++)
        {
            if (bms_voltage_table[i] >= 0)
            {
                adc_mux_voltage[i].voltage = stm32_adc_data[bms_voltage_table[i]] * 134277;
                // adc_mux_voltage[i].voltage = Misaka_Filter_NF_LPF(&adc_mux_voltage[bms_voltage_table[i]].filter, stm32_adc_data[bms_voltage_table[i]]);
                if (get_temperature(EKX_NTC_Voltage_Table_100K_4150, adc_mux_voltage[i].voltage, &BMS_Temperature[i]) == 0)
                {
                    BMS_Temperature[i].temperature = 0;
                    BMS_Temperature[i].temperature_f = 0;
                }
            }
        }

        /**
         * @brief 由于硬件问题，暂时无法使用
         */
        voltage_cell7 = stm32_adc_data[bms_voltage_table[80]] * 134277;
        voltage_vref2 = stm32_adc_data[bms_voltage_table[81]] * 134277;
        voltage_vreg = stm32_adc_data[bms_voltage_table[82]] * 134277;
        voltage_5v = stm32_adc_data[bms_voltage_table[83]] * 134277;
        /**********************************************************************/


    }
}

static int adc_mux_thread_setup(void)
{
    uint32_t LPF_factor = 1;
    if (Eeprom_Read_Uint32(&LPF_factor, EEPROM_TABLE_TEMPERATURE_LPF_FACTOR))
    {
        LPF_factor = DEFAULT_TEMPERATURE_LPF_FACTOR;
    }

    for (uint8_t i = 0; i < 80; i++)
    {
        adc_mux_voltage[i].filter.factor = LPF_factor;
        adc_mux_voltage[i].filter.multiple = 100000;
    }

    rt_thread_init(&adc_mux_thread,
                   "adc_mux_thread",
                   adc_mux_thread_entry,
                   RT_NULL,
                   &adc_mux_thread_stack[0],
                   sizeof(adc_mux_thread_stack),
                   8, 100);
    rt_thread_startup(&adc_mux_thread);

    return 0;
}


INIT_APP_EXPORT(adc_mux_thread_setup);