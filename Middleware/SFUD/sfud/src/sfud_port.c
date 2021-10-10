/*
 * This file is part of the Serial Flash Universal Driver Library.
 *
 * Copyright (c) 2016-2018, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2016-04-23
 */

#include <sfud.h>
#include <stdarg.h>
#include "main.h"
#include "spi.h"
#include <rtthread.h>
#include "system.h"

typedef struct
{
    SPI_HandleTypeDef* spi;
    GPIO_TypeDef* cs_gpio_port;
    uint16_t cs_gpio_pin;
    rt_mutex_t mutex;
} spi_user_data, *spi_user_data_t;

static struct rt_mutex s_flash_mutex;
static spi_user_data s_flash_spi_user_data;

/**
 * SPI write data then read data
 */
static sfud_err spi_write_read(const sfud_spi* spi, uint8_t* writeBuf, size_t writeSize, uint8_t* readBuf, size_t readSize)
{
    sfud_err status = SFUD_SUCCESS;
    /**
     * add your spi write and read code
     */
    spi_user_data_t obj = spi->user_data;

    if (writeSize)
    {
        SFUD_ASSERT(writeBuf);
    }
    if (readSize)
    {
        SFUD_ASSERT(readBuf);
    }

    HAL_GPIO_WritePin(obj->cs_gpio_port, obj->cs_gpio_pin, GPIO_PIN_RESET);
    if (writeSize > 0)
    {
        if (HAL_SPI_Transmit(obj->spi, writeBuf, writeSize, 1000) != HAL_OK)
        {
            status = SFUD_ERR_WRITE;
            goto exit;
        }
    }
    if (readSize > 0)
    {
        if (HAL_SPI_Receive(obj->spi, readBuf, readSize, 1000))
        {
            status = SFUD_ERR_READ;
            goto exit;
        }
    }

exit:
    HAL_GPIO_WritePin(obj->cs_gpio_port, obj->cs_gpio_pin, GPIO_PIN_SET);
    return status;
}

#ifdef SFUD_USING_QSPI

/**
 * read flash data by QSPI
 */
static sfud_err qspi_read(const struct __sfud_spi* spi, uint32_t addr, sfud_qspi_read_cmd_format* qspi_read_cmd_format,
                          uint8_t* read_buf, size_t read_size)
{
    sfud_err result = SFUD_SUCCESS;

    /**
     * add your qspi read flash data code
     */

    return result;
}

#endif /* SFUD_USING_QSPI */

static void spi_lock(const sfud_spi* spi)
{
    spi_user_data_t obj = (spi_user_data_t) spi->user_data;
    rt_mutex_take(obj->mutex, RT_WAITING_FOREVER);
}

static void spi_unlock(const sfud_spi* spi)
{
    spi_user_data_t obj = (spi_user_data_t) spi->user_data;
    rt_mutex_release(obj->mutex);
}

extern void delay_us(rt_uint32_t us);

static void retry_delay_100Us(void)
{
    /* 100 microsecond delay */
    delay_us(100);
}

sfud_err sfud_spi_port_init(sfud_flash* flash)
{
    sfud_err result = SFUD_SUCCESS;
    switch (flash->index)
    {
    case SFUD_W25Q128_DEVICE_INDEX:

        s_flash_spi_user_data.spi = &hspi1;
        s_flash_spi_user_data.cs_gpio_pin = FLASH_CS_Pin;
        s_flash_spi_user_data.cs_gpio_port = FLASH_CS_GPIO_Port;

        rt_mutex_init(&s_flash_mutex, "s_flash_mutex", RT_IPC_FLAG_FIFO);
        s_flash_spi_user_data.mutex = &s_flash_mutex;
        flash->spi.wr = spi_write_read;
        flash->spi.lock = spi_lock;
        flash->spi.unlock = spi_unlock;
        flash->spi.user_data = &s_flash_spi_user_data;
        flash->retry.delay = retry_delay_100Us;
        flash->retry.times = 60 * 10000;
        break;
    default:
        break;
    }
    return result;
}
