/**
 * @file Misaka_LTC6811_Port.c
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-07-21
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-07-21 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */

#include "Misaka_LTC6811_Base.h"
#include "spi.h"
#include "system.h"
#include "gpio.h"
#include "main.h"
#include "rtthread.h"

#define Misaka_LTC6811_Debug 0

uint8_t Misaka_LTC6811_Transmit_Receive(uint8_t* tx_data, uint8_t* rx_data, uint16_t size)
{
    uint8_t status = 0;
    LL_GPIO_ResetOutputPin(LTC6811_CS_GPIO_Port, LTC6811_CS_Pin);
    for (uint16_t i = 0; i < size; i++)
    {
        uint32_t time = 0;
        while (LL_SPI_IsActiveFlag_TXE(SPI1) == RESET)
        {
            if (time < 1000)
            {
                time++;
            }
            else
            {
                return 1;
            }
        }
        LL_SPI_TransmitData8(SPI1, tx_data[i]);
        time = 0;
        while (LL_SPI_IsActiveFlag_RXNE(SPI1) == RESET)
        {
            if (time < 1000)
            {
                time++;
            }
            else
            {
                return 1;
            }
        }
        rx_data[i] = LL_SPI_ReceiveData8(SPI1);
    }
    LL_GPIO_SetOutputPin(LTC6811_CS_GPIO_Port, LTC6811_CS_Pin);
#if Misaka_LTC6811_Debug == 1
    sys_printf("\ntx: ");
    for (uint16_t i = 0; i < size; i++)
    {
        sys_printf("%02X ", tx_data[i]);
    }
    sys_printf("\nrx: ");
    for (uint16_t i = 0; i < size; i++)
    {
        sys_printf("%02X ", rx_data[i]);
    }
    sys_printf("\n");
#endif

    return status;
}


void Misaka_LTC6811_Delay_Ms(uint16_t ms)
{
    rt_thread_mdelay(ms);
}