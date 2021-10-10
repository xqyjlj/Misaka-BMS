/**
 * @file Misaka_RGB_Bling.c
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-01
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-01 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#include "Misaka_RGB_Bling.h"

static Misaka_Bling_Struct s_misaka_bling = {0};

/**
 * @brief Misaka_Bling初始化
 */
void Misaka_Bling_Init(uint16_t base)
{
    s_misaka_bling.color1 = Misaka_Bling_Color_None;
    s_misaka_bling.color2 = Misaka_Bling_Color_None;
    s_misaka_bling.contiune_time = 0;
    s_misaka_bling.color1_cnt = 0;
    s_misaka_bling.period_cnt = 0;
    s_misaka_bling.cnt = 0;
    s_misaka_bling.time_base = base;
    s_misaka_bling.endless_flag = 0;
    Misaka_Set_Bling_GPIO(Misaka_Bling_Color_None);
}

/**
 * @brief                   Misaka_Bling模式设置
 * @param  color1           颜色1
 * @param  color2           颜色2
 * @param  color1_time      颜色1时间
 * @param  color2_time      颜色2时间
 * @param  cnt              次数
 * @param  endless_flag     无尽模式
 */
void Misaka_Bling_Mode_Set(Misaka_Bling_Color_Enum color1,
                           Misaka_Bling_Color_Enum color2,
                           uint32_t color1_time,
                           uint32_t color2_time,
                           uint16_t cnt,
                           uint8_t endless_flag)
{
    s_misaka_bling.color1 = color1;
    s_misaka_bling.color2 = color2;
    s_misaka_bling.color1_cnt = color1_time / s_misaka_bling.time_base;
    s_misaka_bling.period_cnt = s_misaka_bling.color1_cnt + (color2_time / s_misaka_bling.time_base);
    s_misaka_bling.cnt = cnt;
    s_misaka_bling.contiune_time = cnt * s_misaka_bling.period_cnt;
    s_misaka_bling.endless_flag = endless_flag;
}

/**
 * @brief   周期处理函数
 */
void Misaka_Bling_Cycle_Process()
{
    if (s_misaka_bling.contiune_time >= 1)
    {
        s_misaka_bling.contiune_time--;
    }
    else
    {
        Misaka_Set_Bling_GPIO(Misaka_Bling_Color_None);
    }

    if (s_misaka_bling.contiune_time != 0 //总时间未清0
            || s_misaka_bling.endless_flag == 1) //判断无尽模式是否开启
    {
        s_misaka_bling.cnt++;
        if (s_misaka_bling.cnt <= s_misaka_bling.color1_cnt)
        {
            Misaka_Set_Bling_GPIO(s_misaka_bling.color1);
        }
        else if (s_misaka_bling.cnt > s_misaka_bling.color1_cnt && s_misaka_bling.cnt <= s_misaka_bling.period_cnt)
        {
            Misaka_Set_Bling_GPIO(s_misaka_bling.color2);
        }
        else
        {
            s_misaka_bling.cnt = 0;
        }
    }
}


