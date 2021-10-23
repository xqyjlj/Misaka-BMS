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
#include "main.h"
#include "rtthread.h"

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
			LL_GPIO_ResetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_ResetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_ResetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
		case misaka_rgb_color_red:
		{
			LL_GPIO_SetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_ResetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_ResetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
		case misaka_rgb_color_green:
		{
			LL_GPIO_ResetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_SetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_ResetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
		case misaka_rgb_color_blue:
		{
			LL_GPIO_ResetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_ResetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_SetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
		case misaka_rgb_color_yellow:
		{
			LL_GPIO_SetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_SetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_ResetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
		case misaka_rgb_color_cyan:
		{
			LL_GPIO_ResetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_SetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_SetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
		case misaka_rgb_color_white:
		{
			LL_GPIO_SetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_SetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_SetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
		case misaka_rgb_color_purple:
		{
			LL_GPIO_SetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_ResetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_SetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
		default:
		{
			LL_GPIO_ResetOutputPin(RGB_R_GPIO_Port, RGB_R_Pin);
			LL_GPIO_ResetOutputPin(RGB_G_GPIO_Port, RGB_G_Pin);
			LL_GPIO_ResetOutputPin(RGB_B_GPIO_Port, RGB_B_Pin);
		}
			break;
	}
}

static int rgb_thread_setup(void)
{
	misaka_rgb_init(100);
	misaka_rgb_set_mode(misaka_rgb_color_cyan,
	                    misaka_rgb_color_blue,
	                    100,
	                    100,
	                    10,
	                    0);
	return 0;
}

INIT_DEVICE_EXPORT(rgb_thread_setup);