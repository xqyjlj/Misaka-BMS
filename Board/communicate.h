/**
 * @file communicate.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-03
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-03 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */

#ifndef __COMMUNICATE_H__
#define __COMMUNICATE_H__

#include "can.h"
#include "main.h"
#include "system.h"
#include "usart.h"
#include "time.h"

#define BOARD_CAN_ID_SDC_CURRENT    0x10
#define BOARD_CAN_ID_AS             0x11
#define BOARD_CAN_ID_RES            0x12
#define BOARD_CAN_ID_EBS            0x13

#define USE_DMA 0

/**
 * @brief   设置Can过滤器
 *
 * @param   void
 *
 * @return  void
*/
void set_can_filter();

/**
 * @brief   can发送一组数据(固定格式:标准帧,数据帧)
 *
 * @param   len:    数据长度(最大为8)
 *          msg:    数据指针,最大为8个字节.
 *          id:     ID
 *
 * @return  0:      成功;
 *          1:      失败;
*/
uint8_t send_can_rtr_msg(uint8_t* msg, uint8_t len, uint32_t id, uint32_t id_type);

/**
 * @brief   uart1设置中断
 *
 * @param   void
 *
 * @return  void
*/
void set_uart1_interrupt_enable();

/**
 * @brief   uart3设置中断
 *
 * @param   void
 *
 * @return  void
*/
void set_uart3_interrupt_enable();


void uart_data_coming(USART_TypeDef* USARTx, uint32_t data);

#if USE_DMA == 1
    void uart1_dma_send_complete();

    void uart1_send_data_with_dma(uint8_t* data, uint32_t length);

    void uart3_dma_send_complete();

    void uart3_send_data_with_dma(uint8_t* data, uint32_t length);
#endif
#endif //__COMMUNICATE_H__
