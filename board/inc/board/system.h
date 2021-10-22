/**
 * @file system.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-10-21
 * @copyright Copyright © 2021-2021 xqyjlj<xqyjlj@126.com>
 * @SPDX-License-Identifier: Apache-2.0
 *
 * ********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-10-21 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * ********************************************************************************
 */

#ifndef ___SYSTEM___H
#define ___SYSTEM___H

#include "usart.h"
#include <stdio.h>
#include <stdarg.h>
#include <rtthread.h>

#define DEBUG 1

#define sys_printf rt_kprintf

#pragma region LOG
#define _DBG_LOG_HDR(lvl_name, color_n, name)                    \
    sys_printf("\033["#color_n"m[" lvl_name "/" name "] ")

#define _DBG_LOG_X_END                                     \
    sys_printf("\033[0m\n")

#define dbg_log_line(lvl, color_n, name, fmt, ...)                \
    do                                                      \
    {                                                       \
        _DBG_LOG_HDR(lvl, color_n, name);                         \
        sys_printf(fmt, ##__VA_ARGS__);                     \
        _DBG_LOG_X_END;                                     \
    }                                                       \
    while (0)

#define dbg_raw(...)         sys_printf(__VA_ARGS__);

#if DEBUG == 1
    #define LOG_D(fmt, ...)      dbg_log_line("D", 0, LOG_NAME, fmt, ##__VA_ARGS__)
#else
    #define LOG_D(fmt, ...)
#endif

#if DEBUG == 1
    #define LOG_I(fmt, ...)      dbg_log_line("I", 32, LOG_NAME, fmt, ##__VA_ARGS__)
#else
    #define LOG_I(fmt, ...)
#endif

#define LOG_W(fmt, ...)      dbg_log_line("W", 33, LOG_NAME, fmt, ##__VA_ARGS__)

#define LOG_E(fmt, ...)      dbg_log_line("E", 31, LOG_NAME, fmt, ##__VA_ARGS__)

#define LOG_RAW(...)         dbg_raw(__VA_ARGS__)

#define SYS_ASSERT(EXPR)                                                       \
if (!(EXPR))                                                                  \
{                                                                             \
    sys_printf("(%s: %d) (%s) has assert failed at %s.\n", __FILE__ , __LINE__ , #EXPR, __FUNCTION__);         \
    while (1);                                                                \
}

#if DEBUG == 1
    #define LOG_D_NAME(name, fmt, ...)      dbg_log_line("D", 0, name, fmt, ##__VA_ARGS__)
#else
    #define LOG_D_NAME(fmt, ...)
#endif

#if DEBUG == 1
    #define LOG_I_NAME(name, fmt, ...)      dbg_log_line("I", 32, name, fmt, ##__VA_ARGS__)
#else
    #define LOG_I_NAME(fmt, ...)
#endif
#define LOG_W_NAME(name, fmt, ...)      dbg_log_line("W", 33, name, fmt, ##__VA_ARGS__)

#define LOG_E_NAME(name, fmt, ...)      dbg_log_line("E", 31, name, fmt, ##__VA_ARGS__)

#pragma endregion LOG

#define ABS(X)      (((X)>0)?(X):-(X))
#define MAX(a,b)    ((a)>(b)?(a):(b))
#define MIN(a,b)    ((a)>(b)?(b):(a))

void show_information();

#endif //___SYSTEM___H
