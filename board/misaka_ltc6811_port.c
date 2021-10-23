/**
 * @file misaka_ltc6811_port.c
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

#include "misaka_device/spi.h"
#include "misaka_device/ltc6811.h"
#include "rtthread.h"

extern misaka_spi_t *misaka_spi11_obj;

misaka_ltc6811_cfgr_struct s_ltc6811_cfgr = {0};

uint8_t misaka_ltc6811_transmit_receive(uint8_t *tx_data, uint8_t *rx_data, uint16_t size)
{
	return misaka_spi_transfer(misaka_spi11_obj, tx_data, rx_data, size);
}

void misaka_ltc6811_delay_ms(uint16_t ms)
{
	rt_thread_mdelay(ms);
}

static int misaka_ltc6811_init()
{
	uint16_t vuv = 0;
	uint16_t vov = 0;
	//if (Eeprom_Read_Uint16(&vuv, EEPROM_TABLE_VUV))
	//{
	//	vuv = DEFAULT_VUV;
	//}
	//if (Eeprom_Read_Uint16(&vov, EEPROM_TABLE_VOV))
	//{
	//	vov = DEFAULT_VOV;
	//}

	misaka_ltc6811_device_object[0].cell_select = 0x01CF;
	misaka_ltc6811_device_object[0].gpio_select = 0x1F;

	s_ltc6811_cfgr.gpiox = LTC6811_GPIO11111;
	s_ltc6811_cfgr.refon = LTC6811_REFON1;
	s_ltc6811_cfgr.dten = LTC6811_DTEN1;
	s_ltc6811_cfgr.adcopt = LTC6811_ADCOPT0;

	s_ltc6811_cfgr.vuv = vuv;
	s_ltc6811_cfgr.vov = vov;

	s_ltc6811_cfgr.dcto = LTC6811_DCTO_30s;
	misaka_ltc6811_wrcfga(&s_ltc6811_cfgr);

	return 0;
}

INIT_DEVICE_EXPORT(misaka_ltc6811_init);