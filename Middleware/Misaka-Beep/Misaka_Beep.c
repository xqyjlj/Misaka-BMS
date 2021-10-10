/**
 * @file Misaka_Beep.c
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

static Misaka_Beep_Struct s_misaka_beep = {0};

/**
 * @brief
 * @param  base             desc
 */
void Misaka_Beep_Init(uint16_t base)
{
    s_misaka_beep.contiune_time = 0;
    s_misaka_beep.beep_cnt = 0;
    s_misaka_beep.period_cnt = 0;
    s_misaka_beep.cnt = 0;
    s_misaka_beep.time_base = base;
    s_misaka_beep.endless_flag = 0;
    Misaka_Set_Beep_GPIO(0);
}

/**
 * @brief
 * @param  beep_time        desc
 * @param  nbeep_time       desc
 * @param  cnt              desc
 * @param  endless_flag     desc
 */
void Misaka_Beep_Mode_Set(uint32_t beep_time,
                          uint32_t nbeep_time,
                          uint16_t cnt,
                          uint8_t endless_flag)
{
    s_misaka_beep.beep_cnt = beep_time / s_misaka_beep.time_base;
    s_misaka_beep.period_cnt = s_misaka_beep.beep_cnt + (nbeep_time / s_misaka_beep.time_base);
    s_misaka_beep.cnt = cnt;
    s_misaka_beep.contiune_time = cnt * s_misaka_beep.period_cnt;
    s_misaka_beep.endless_flag = endless_flag;
}

/**
 * @brief
 */
void Misaka_Beep_Cycle_Process()
{
    if (s_misaka_beep.contiune_time >= 1)
    {
        s_misaka_beep.contiune_time--;
    }
    else
    {
        Misaka_Set_Beep_GPIO(0);
    }

    if (s_misaka_beep.contiune_time != 0 //总时间未清0
            || s_misaka_beep.endless_flag == 1) //判断无尽模式是否开启
    {
        s_misaka_beep.cnt++;
        if (s_misaka_beep.cnt <= s_misaka_beep.beep_cnt)
        {
            Misaka_Set_Beep_GPIO(1);
        }
        else if (s_misaka_beep.cnt > s_misaka_beep.beep_cnt && s_misaka_beep.cnt <= s_misaka_beep.period_cnt)
        {
            Misaka_Set_Beep_GPIO(0);
        }
        else
        {
            s_misaka_beep.cnt = 0;
        }
    }
}
