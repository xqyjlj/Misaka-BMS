/**
 * @file misaka_at24cxx_port.c
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
#include "misaka_device/at24cxx.h"
#include "misaka_device/soft_i2c.h"
#include "rtthread.h"

static struct rt_mutex s_misaka_at24cxx_mutex;
misaka_at24cxx_t s_misaka_at24cxx_obj = {0};

misaka_at24cxx_t *misaka_at24cxx_obj = {0};
extern misaka_soft_i2c_t *i2c1_obj;

/**
 * @brief i2c发送后再接收
 * @param  address          地址
 * @param  txbuf            发送数据
 * @param  txlen            发送长度
 * @param  rxbuf            接收数据
 * @param  rxlen            接收长度
 * @return 0 @c             成功
 * @return 1 @c             失败
 */
static uint16_t i2c_send_then_recv(uint8_t address, uint8_t *txbuf, uint32_t txlen, uint8_t *rxbuf, uint32_t rxlen)
{
	uint16_t ret;
	ret = misaka_soft_i2c_master_send_then_recv(i2c1_obj, address, txbuf, txlen, rxbuf, rxlen);
	if (ret == 2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
 * @brief i2c发送后再发送
 * @param  address          地址
 * @param  txbuf1           发送数据
 * @param  txlen1           发送长度
 * @param  txbuf2           发送数据再发送数据
 * @param  txlen2           发送数据再发送长度
 * @return 0 @c             成功
 * @return 1 @c             失败
 */
static uint16_t i2c_send_then_send(uint8_t address, uint8_t *txbuf1, uint32_t txlen1, uint8_t *txbuf2, uint32_t txlen2)
{
	uint16_t ret;
	ret = misaka_soft_i2c_master_send_then_send(i2c1_obj, address, txbuf1, txlen1, txbuf2, txlen2);
	if (ret == 2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
 * @brief 延时函数，单位为1ms
 * @param  ms               desc
 */
static void delay_ms(uint16_t ms)
{
	rt_thread_mdelay(ms);
}

/**
 * @brief 获取互斥量，如果为裸机系统，空函数即可
 */
static void mutex_take()
{
	rt_mutex_take(&s_misaka_at24cxx_mutex, RT_WAITING_FOREVER);
}

/**
 * @brief 释放互斥量，如果为裸机系统，空函数即可
 */
static void mutex_release()
{
	rt_mutex_release(&s_misaka_at24cxx_mutex);
}

/**
 * @brief i2c错误回调函数，不需要设置成空函数即可
 */
void misaka_at24cxx_i2c_error_callback()
{

}

/**
 * @brief
 * @return misaka_at24cxx_t @c
 */
int misaka_at24cxx_port_init()
{
	rt_mutex_init(&s_misaka_at24cxx_mutex, "misaka_at24cxx_mutex", RT_IPC_FLAG_FIFO);

	s_misaka_at24cxx_obj.type = MISAKA_AT24C02;
	s_misaka_at24cxx_obj.is_fram = 0;
	s_misaka_at24cxx_obj.mutex_release = mutex_release;
	s_misaka_at24cxx_obj.mutex_take = mutex_take;
	s_misaka_at24cxx_obj.delay_ms = delay_ms;
	s_misaka_at24cxx_obj.i2c_send_then_recv = i2c_send_then_recv;
	s_misaka_at24cxx_obj.i2c_send_then_send = i2c_send_then_send;
	s_misaka_at24cxx_obj.address = 0x50;

	misaka_at24cxx_init(&s_misaka_at24cxx_obj);

	misaka_at24cxx_obj = &s_misaka_at24cxx_obj;

	return 1;
}

INIT_DEVICE_EXPORT(misaka_at24cxx_port_init);