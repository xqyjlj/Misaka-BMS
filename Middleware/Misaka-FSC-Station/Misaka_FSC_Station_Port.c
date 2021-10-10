/**
 * @file Misaka_FSC_Station_Port.c
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
#include "usart.h"
#include "main.h"
#include "communicate.h"

void Misaka_FSC_Station_Data_Send(uint8_t* buf, uint32_t cnt)
{
    for (uint32_t i = 0; i < cnt; i++)
    {
        LL_USART_TransmitData8(USART3, buf[i]);
        uint32_t time = 0;
        while (LL_USART_IsActiveFlag_TXE(USART3) == RESET)
        {
            if (time < 1000)
            {
                time++;
            }
            else
            {
                return;
            }
        }
    }
}






