/**
 * @file communicate.c
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

#include "communicate.h"
#include "Misaka_RGB_Bling.h"
/**
 * @brief   can设置过滤器
 *
 * @param   filter_bank:    过滤器组(0-13)
 *          id1:            ID1
 *          id1_type:       ID1种类
 *          id2:            ID2
 *          id2_type:       ID2种类
 *          fifo:           fifo号
 *
 * @return  void
*/

void set_can_list_filter(uint32_t filter_bank, uint32_t id1, uint32_t id1_type, uint32_t id2, uint32_t id2_type, uint32_t fifo)
{
    CAN_FilterTypeDef can_filter;

    /*配置CAN过滤器*/
    can_filter.FilterBank = filter_bank; /* 过滤器0 */
    can_filter.FilterMode = CAN_FILTERMODE_IDLIST;
    can_filter.FilterScale = CAN_FILTERSCALE_32BIT;
    if (id1_type == CAN_ID_STD)
    {
        can_filter.FilterIdHigh = id1 << 5; /* 32位ID */
        can_filter.FilterIdLow = 0 | CAN_ID_STD;
    }
    else
    {
        can_filter.FilterIdHigh = ((id1 << 3) >> 16) & 0xffff; /* 32位MASK */
        can_filter.FilterIdLow = ((id1 << 3) & 0xffff) | CAN_ID_EXT;
    }

    if (id2_type == CAN_ID_STD)
    {
        can_filter.FilterMaskIdHigh = id2 << 5; /* 32位ID */
        can_filter.FilterMaskIdLow = 0 | CAN_ID_STD;
    }
    else
    {
        can_filter.FilterMaskIdHigh = ((id2 << 3) >> 16) & 0xffff; /* 32位MASK */
        can_filter.FilterMaskIdLow = ((id2 << 3) & 0xffff) | CAN_ID_EXT;
    }

    can_filter.FilterFIFOAssignment = fifo; /* 过滤器0关联到FIFO0 */
    can_filter.FilterActivation = ENABLE; /* 激活过滤器 */
    can_filter.SlaveStartFilterBank = 14;

    /* 过滤器配置 */
    if (HAL_CAN_ConfigFilter(&hcan, &can_filter) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief   设置Can过滤器
 *
 * @param   void
 *
 * @return  void
*/
void set_can_filter()
{
    set_can_list_filter(0, BOARD_CAN_ID_AS, CAN_ID_STD, BOARD_CAN_ID_EBS, CAN_ID_STD, CAN_RX_FIFO0);

    /* 启动CAN外围设备 */
    if (HAL_CAN_Start(&hcan) != HAL_OK)
    {
        Error_Handler();
    }

    /* 激活可以RX通知 */
    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
}

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
uint8_t send_can_rtr_msg(uint8_t* msg, uint8_t len, uint32_t id, uint32_t id_type)
{
    CAN_TxHeaderTypeDef tx_header;
    uint32_t tx_mailbox;
    tx_header.IDE = id_type;
    if (id_type == CAN_ID_STD)
    {
        tx_header.StdId = id;
    }
    else
    {
        tx_header.ExtId = id;
    }
    tx_header.RTR = CAN_RTR_DATA; //数据帧
    tx_header.DLC = len;
    tx_header.TransmitGlobalTime = DISABLE;
    if (HAL_CAN_AddTxMessage(&hcan, &tx_header, msg, &tx_mailbox) != HAL_OK) //发送
    {
        return 1;
    }
    while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0)
    {
        HAL_Delay(10);
    }
    return 0;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* obj)
{
    CAN_RxHeaderTypeDef packet;
    uint8_t rx_data[8];
    if (obj == &hcan)
    {
        if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &packet, rx_data) == HAL_OK) //获得接收到的数据头和数据
        {
            if (packet.IDE == CAN_ID_STD)
            {
                if (packet.StdId == BOARD_CAN_ID_AS)
                {
                    if (packet.DLC == 1 && rx_data[0] == BOARD_CAN_ID_AS)//TODO 待定
                    {

                    }
                    else
                    {

                    }
                }
                else if (packet.StdId == BOARD_CAN_ID_EBS)
                {
                    if (packet.DLC == 1 && rx_data[0] == BOARD_CAN_ID_AS)//TODO 待定
                    {
                    }
                    else
                    {

                    }

                }
            }
            HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING); //再次使能FIFO0接收中断
        }
    }
}

/**
 * @brief   uart1设置中断
 *
 * @param   void
 *
 * @return  void
*/
void set_uart1_interrupt_enable()
{
    LL_USART_EnableIT_RXNE(USART1);
}

/**
 * @brief   uart3设置中断
 *
 * @param   void
 *
 * @return  void
*/
void set_uart3_interrupt_enable()
{
    LL_USART_EnableIT_RXNE(USART3);
}

void uart_data_coming(USART_TypeDef* USARTx, uint32_t data)
{
    if (USARTx == USART1)
    {
        Misaka_Bling_Mode_Set(Misaka_Bling_Color_Cyan,
                              Misaka_Bling_Color_Blue,
                              100,
                              100,
                              10,
                              0);
    }
    else if (USARTx == USART3)
    {

    }
}

#if USE_DMA == 1

static char uart1_send_buf[256] = {0};
static void set_uart1_dma_enable()
{
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)uart1_send_buf);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)LL_USART_DMA_GetRegAddr(USART1));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, 0);
    LL_USART_EnableDMAReq_TX(USART1);
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
}

void uart1_send_data_with_dma(uint8_t* data, uint32_t length)
{
    if (status == RT_EOK)
    {
        if (length > sizeof(uart1_send_buf))
        {
            return;
        }
        rt_memcpy(uart1_send_buf, data, length);
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)uart1_send_buf);
        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, length);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
    }
}

void uart1_dma_send_complete()
{
    rt_interrupt_enter();

    rt_interrupt_leave();
}


static char uart3_send_buf[256] = {0};
static void set_uart3_dma_enable()
{
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t)uart3_send_buf);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t)LL_USART_DMA_GetRegAddr(USART3));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, 0);
    LL_USART_EnableDMAReq_TX(USART3);
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
}

void uart3_send_data_with_dma(uint8_t* data, uint32_t length)
{

    if (status == RT_EOK)
    {
        if (length > sizeof(uart3_send_buf))
        {
            return;
        }
        rt_memcpy(uart3_send_buf, data, length);
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t)uart3_send_buf);
        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, length);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
    }
}

void uart3_dma_send_complete()
{
    rt_interrupt_enter();

    rt_interrupt_leave();
}

#endif

static int communicate_init()
{
    set_uart1_interrupt_enable();
    set_uart3_interrupt_enable();

#if USE_DMA == 1
    set_uart1_dma_enable();
    set_uart3_dma_enable();
#endif

    return 0;
}

INIT_PREV_EXPORT(communicate_init);