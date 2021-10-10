/**
 * @file Bling.c
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
#include "Bling.h"
#include "Misaka_RGB_Bling.h"
#include "rtthread.h"
#include "gpio.h"

static char bling_thread_stack[256];
static struct rt_thread bling_thread;

void bling_thread_entry(void* parameter)
{
    while (1)
    {
        rt_thread_mdelay(100);
        Misaka_Bling_Cycle_Process();
    }
}

/**
 * @brief            Misaka_Bling线程初始化函数
 * @return int @c
 */
static int bling_thread_setup(void)
{
    Misaka_Bling_Init(100);
    Misaka_Bling_Mode_Set(Misaka_Bling_Color_Cyan,
                          Misaka_Bling_Color_Blue,
                          100,
                          100,
                          10,
                          0);
    rt_thread_init(&bling_thread,
                   "bling_thread",
                   bling_thread_entry,
                   RT_NULL,
                   &bling_thread_stack[0],
                   sizeof(bling_thread_stack),
                   22, 100);
    rt_thread_startup(&bling_thread);
    return 0;
}

INIT_APP_EXPORT(bling_thread_setup);




