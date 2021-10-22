/**
 * @file system.c
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

#include "board/system.h"

/**
 * @brief 展示信息
 */
void show_information()
{
    sys_printf("\r\n\r\n\r\n");
    sys_printf("this project designed by xqyjlj<xqyjlj@126.com>\r\n");
    sys_printf(">[Misaka-Network](https://github.com/xqyjlj/Misaka-Network), Misaka00004\r\n");
}
