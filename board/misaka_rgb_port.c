/**
 * @file misaka_rgb_port.c
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-10-23
 * @copyright Copyright © 2021-2021 xqyjlj<xqyjlj@126.com>
 * @SPDX-License-Identifier: Apache-2.0
 *
 * ********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-10-23 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * ********************************************************************************
 */
#include "misaka_device/rgb.h"

/**
 * @brief 设置RGB引脚
 * @param color 颜色
 */
void misaka_rgb_set_pin(misaka_rgb_color_enum color)
{
	switch (color)
	{
		case misaka_rgb_color_none:
		{

		}
			break;
		case misaka_rgb_color_red:
		{

		}
			break;
		case misaka_rgb_color_green:
		{

		}
			break;
		case misaka_rgb_color_blue:
		{

		}
			break;
		case misaka_rgb_color_yellow:
		{

		}
			break;
		case misaka_rgb_color_cyan:
		{

		}
			break;
		case misaka_rgb_color_white:
		{

		}
			break;
		case misaka_rgb_color_purple:
		{

		}
			break;
		default:
		{

		}
			break;
	}
}