/**
 * @file Misaka_Filter_LPF.c
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
#include "Misaka_Filter.h"

/**
 * @brief                   一阶低通滤波非浮点数版
 * @param  obj              对象
 * @param  value            数值
 * @return uint32_t @c      滤波后数值，为obj->multiple倍
 */
uint32_t Misaka_Filter_NF_LPF(Misaka_Filter_NF_LPF_Struct* obj, uint32_t value)
{
    obj->last_data = obj->last_data * obj->factor + value * (obj->multiple - obj->factor);
    return obj->last_data;
}

/**
 * @brief                   一阶低通滤波完整版
 * @param  obj              对象
 * @param  value            数值
 * @return float @c         滤波后数值，
 */
float Misaka_Filter_LPF(Misaka_Filter_LPF_Struct* obj, uint32_t value)
{
    obj->last_data = obj->last_data * obj->factor + value * (1 - obj->factor);
    return obj->last_data;
}
