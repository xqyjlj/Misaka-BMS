/**
 * @file Misaka_Beep_Port.c
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-02
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-02 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#include "Misaka_Beep.h"
#include "gpio.h"
#include "main.h"

void Misaka_Set_Beep_GPIO(uint8_t status)
{
    if (status == 0)
    {
        LL_GPIO_ResetOutputPin(BEEP_GPIO_Port, BEEP_Pin);
    }
    else
    {
        LL_GPIO_SetOutputPin(BEEP_GPIO_Port, BEEP_Pin);
    }
}