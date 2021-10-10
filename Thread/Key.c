/**
 * @file Key.c
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
#include "Key.h"
#include "button.h"
#include "rtthread.h"
#include "gpio.h"
#include "Bling.h"
#include "eeprom.h"

#define KEY1_Pin GPIO_PIN_13
#define KEY1_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_14
#define KEY2_GPIO_Port GPIOC

static GPIO_InitTypeDef GPIO_Init_Struct = {0};
static Button_t s_key1;
static Button_t s_key2;

static void key_GPIO_init()
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_Init_Struct.Pin = KEY1_Pin | KEY2_Pin;
    GPIO_Init_Struct.Mode = GPIO_MODE_INPUT;
    GPIO_Init_Struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);
}

static uint8_t read_key1_level(void)
{
    uint8_t i;
    key_GPIO_init();
    i = HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
    Bling_GPIO_Init();
    return i;
}

static uint8_t read_key2_level(void)
{
    uint8_t i;
    key_GPIO_init();
    i = HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
    Bling_GPIO_Init();
    return i;
}

static void key1_down_callback(void* Key)
{
    rt_kprintf("key1+dowm\n");
}

static void key1_double_callback(void* Key)
{

}

static void key1_long_callback(void* Key)
{

}

static void key1_continuos_callback(void* Key)
{

}
static void key1_continuosfree_callback(void* Key)
{

}


static void key2_down_callback(void* Key)
{
    rt_kprintf("key2+dowm\n");
}

static void key2_double_callback(void* Key)
{

}

static void key2_long_callback(void* Key)
{

}

static void key2_continuos_callback(void* Key)
{

}
static void key2_continuosfree_callback(void* Key)
{

}

static char key_thread_stack[1024];
static struct rt_thread key_thread;

void key_thread_entry(void* parameter)
{
    while (1)
    {
        Button_Process();
        rt_thread_mdelay(20);
    }
}

/**
 * @brief            Misaka_key线程初始化函数
 * @return int @c
 */
static int key_thread_setup(void)
{
    Button_Create("s_key1", &s_key1, read_key1_level, 1);
    Button_Attach(&s_key1, BUTTON_DOWN, key1_down_callback);                     //单击
    Button_Attach(&s_key1, BUTTON_DOUBLE, key1_double_callback);                 //双击
    Button_Attach(&s_key1, BUTTON_CONTINUOS, key1_continuos_callback);           //连按
    Button_Attach(&s_key1, BUTTON_CONTINUOS_FREE, key1_continuosfree_callback);  //连按释放
    Button_Attach(&s_key1, BUTTON_LONG, key1_long_callback);                     //长按


    Button_Create("s_key2", &s_key2, read_key2_level, 1);
    Button_Attach(&s_key2, BUTTON_DOWN, key2_down_callback);                   //单击
    Button_Attach(&s_key2, BUTTON_DOUBLE, key2_double_callback);               //双击
    Button_Attach(&s_key2, BUTTON_CONTINUOS, key2_continuos_callback);         //连按
    Button_Attach(&s_key2, BUTTON_CONTINUOS_FREE, key2_continuosfree_callback); //连按释放
    Button_Attach(&s_key2, BUTTON_LONG, key2_long_callback);                   //长按

    rt_thread_init(&key_thread,
                   "key_thread",
                   key_thread_entry,
                   RT_NULL,
                   &key_thread_stack[0],
                   sizeof(key_thread_stack),
                   19, 100);
    rt_thread_startup(&key_thread);
    return 0;
}

INIT_APP_EXPORT(key_thread_setup);




