/**
 * @file Beep.c
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
#include "Beep.h"
#include "main.h"
#include "gpio.h"
#include "Misaka_Beep.h"
#include "rtthread.h"

static char beep_thread_stack[256];
static struct rt_thread beep_thread;

void beep_thread_entry(void* parameter)
{
    while (1)
    {
        rt_thread_mdelay(100);
        Misaka_Beep_Cycle_Process();
    }
}

/**
 * @brief            Misaka_beep线程初始化函数
 * @return int @c
 */
static int beep_thread_setup(void)
{
    Misaka_Beep_Init(100);
    // Misaka_Beep_Mode_Set(200,
    //                      500,
    //                      1,
    //                      0);
    rt_thread_init(&beep_thread,
                   "beep_thread",
                   beep_thread_entry,
                   RT_NULL,
                   &beep_thread_stack[0],
                   sizeof(beep_thread_stack),
                   21, 100);
    rt_thread_startup(&beep_thread);
    return 0;
}

INIT_APP_EXPORT(beep_thread_setup);


