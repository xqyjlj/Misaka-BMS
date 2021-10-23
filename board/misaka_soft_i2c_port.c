/**
 * @file misaka_soft_i2c_port.c
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
#include "misaka_device/soft_i2c.h"
#include "main.h"
#include "rtthread.h"

static struct rt_mutex s_misaka_soft_i2c1_mutex;

static misaka_soft_i2c_t s_i2c1_obj;
misaka_soft_i2c_t *i2c1_obj;

extern void delay_us(uint16_t us);

/**
 * @brief 设置sda引脚电平
 * @param level 0: 低电平 1: 高电平
 */
static void set_sda(uint8_t level)
{
	if (level == 0)
	{
		LL_GPIO_ResetOutputPin(I2C_SDA_GPIO_Port, I2C_SDA_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(I2C_SDA_GPIO_Port, I2C_SDA_Pin);
	}
}

/**
 * @brief 设置scl引脚电平
 * @param level 0: 低电平 1: 高电平
 */
static void set_scl(uint8_t level)
{
	if (level == 0)
	{
		LL_GPIO_ResetOutputPin(I2C_SCL_GPIO_Port, I2C_SCL_Pin);
	}
	else
	{
		LL_GPIO_SetOutputPin(I2C_SCL_GPIO_Port, I2C_SCL_Pin);
	}
}

/**
 * @brief 读取sda引脚电平
 * @return 0 @c 低电平
 * @return 1 @c 高电平
 */
static uint8_t get_sda()
{
	return LL_GPIO_IsInputPinSet(I2C_SDA_GPIO_Port, I2C_SDA_Pin);
}

/**
 * @brief 获取互斥量，如果为裸机系统，空函数即可
 */
static void mutex_take()
{
	rt_mutex_take(&s_misaka_soft_i2c1_mutex, RT_WAITING_FOREVER);
}

/**
 * @brief 释放互斥量，如果为裸机系统，空函数即可
 */
static void mutex_release()
{
	rt_mutex_release(&s_misaka_soft_i2c1_mutex);
}

/**
 * @brief 设置sda引脚为输出模式（硬件无上拉时需要添加）
 */
static void set_sda_out()
{
//    GPIOB->CRL &= 0X0FFFFFFF;
//    GPIOB->CRL |= (uint32_t) 3 << 28;
}

/**
 * @brief 设置sda引脚为输入模式（硬件无上拉时需要添加）
 */
static void set_sda_in()
{
//    GPIOB->CRL &= 0X0FFFFFFF;
//    GPIOB->CRL |= (uint32_t) 8 << 28;
}

/**
 * @brief I2C读写错误回调函数
 * @param  ops              i2c设备
 */
void misaka_soft_i2c_error_callback(const misaka_soft_i2c_t *ops)
{

}

static int misaka_soft_i2c_port_init()
{
	rt_mutex_init(&s_misaka_soft_i2c1_mutex, "misaka_soft_i2c1_mutex", RT_IPC_FLAG_FIFO);

	s_i2c1_obj.delay_us = delay_us;
	s_i2c1_obj.get_sda = get_sda;
	s_i2c1_obj.mutex_release = mutex_release;
	s_i2c1_obj.mutex_take = mutex_take;
	s_i2c1_obj.set_scl = set_scl;
	s_i2c1_obj.set_sda = set_sda;
	s_i2c1_obj.set_sda_out = set_sda_out;
	s_i2c1_obj.set_sda_in = set_sda_in;
	s_i2c1_obj.us = 1;

	set_sda(1);
	set_scl(1);

	misaka_soft_i2c_init(&s_i2c1_obj);

	i2c1_obj = &s_i2c1_obj;

	return 1;
}

INIT_PREV_EXPORT(misaka_soft_i2c_port_init);