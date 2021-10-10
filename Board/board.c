/**
 * @file board.c
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
#include <stdint.h>
#include <rthw.h>
#include <main.h>
#include <rtthread.h>
#include "sfud.h"

#include "easyflash.h"

#include "spi.h"
#include "adc.h"
#include "can.h"
#include "iwdg.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "dma.h"

#include "communicate.h"


#define RAM_START              (0x20000000)
#define RAM_SIZE               (20 * 1024)
#define RAM_END                (RAM_START + RAM_SIZE)
#define STM32_SRAM1_END         RAM_END

#if defined(__CC_ARM) || defined(__CLANG_ARM)
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN      ((void *)Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
    #pragma section="CSTACK"
    #define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
    extern int __bss_end;
    #define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END                       STM32_SRAM1_END

void SystemClock_Config(void);
/**
 * @brief 板级初始化
 */
void rt_hw_board_init()
{
    HAL_Init();

    SystemClock_Config();

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);
#endif
}

/**
 * @brief  控制台输出
 * @param  str              字符串
 */
void rt_hw_console_output(const char* str)
{
    uint16_t i = 0, size = 0;

    size = rt_strlen(str);
    char a = '\r';
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            uint32_t time = 0;
            while (LL_USART_IsActiveFlag_TXE(USART1) == RESET)
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
            LL_USART_TransmitData8(USART1, a);
        }
        uint32_t time = 0;
        while (LL_USART_IsActiveFlag_TXE(USART1) == RESET)
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
        LL_USART_TransmitData8(USART1, str[i]);
    }
}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (LL_USART_IsActiveFlag_RXNE(USART1) != RESET)
    {
        ch = LL_USART_ReceiveData8(USART1) & 0xff;
    }
    else
    {
        if (LL_USART_IsActiveFlag_ORE(USART1) != RESET)
        {
            LL_USART_ClearFlag_ORE(USART1);
        }
        rt_thread_mdelay(10);
    }
    return ch;
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_IncTick();
    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * @brief 延时毫米级别
 * @param  us               毫秒
 */
void delay_us(uint16_t us)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

/**
 * @brief 板级硬件初始化
 * @return int @c
 */
static int board_init()
{
    MX_GPIO_Init();

    MX_USART1_UART_Init();
    MX_USART3_UART_Init();

    MX_ADC1_Init();

    MX_CAN_Init();

    MX_SPI1_Init();

    MX_IWDG_Init();

    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();

#if USE_DMA == 1
    MX_DMA_Init();
#endif
    show_information();

    return 0;
}

INIT_BOARD_EXPORT(board_init);

static void iwdg_idle_hook(void)
{
    /* 在空闲线程的回调函数里喂狗 */
    LL_IWDG_ReloadCounter(IWDG);
}

/**
 * @brief 中间件初始化
 * @return int @c
 */
static int middleware_init()
{
    rt_thread_idle_sethook(iwdg_idle_hook);
    return 0;
}

INIT_DEVICE_EXPORT(middleware_init);

int main()
{
    return 0;
}

