/*
 * This file is part of the EasyFlash Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
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
 * Function: Portable interface for FAL (Flash Abstraction Layer) partition.
 * Created on: 2018-05-19
 */

#include <easyflash.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>
#include <sfud.h>

/* default ENV set for user */
static const ef_env default_env_set[] =
{
    {"boot_times", "0"}
};

static struct rt_semaphore env_cache_lock;
static sfud_flash_t sfud_dev = NULL;

/**
 * Flash port for hardware initialize.
 *
 * @param default_env default ENV set for user
 * @param default_env_size default ENV size
 *
 * @return result
 */
EfErrCode ef_port_init(ef_env const** default_env, size_t* default_env_size)
{
    EfErrCode result = EF_NO_ERR;

    *default_env = default_env_set;
    *default_env_size = sizeof(default_env_set) / sizeof(default_env_set[0]);

    rt_sem_init(&env_cache_lock, "env lock", 1, RT_IPC_FLAG_PRIO);

    sfud_dev = sfud_get_device(SFUD_W25Q128_DEVICE_INDEX);
    EF_ASSERT(sfud_dev);

    return result;
}

/**
 * Read data from flash.
 * @note This operation's units is word.
 *
 * @param addr flash address
 * @param buf buffer to store read data
 * @param size read bytes size
 *
 * @return result
 */
EfErrCode ef_port_read(uint32_t addr, uint32_t* buf, size_t size)
{
    if (sfud_read(sfud_dev, addr, size, (uint8_t*)buf) == SFUD_SUCCESS)
    {
        return EF_NO_ERR;
    }
    else
    {
        return EF_READ_ERR;
    }
}

/**
 * Erase data on flash.
 * @note This operation is irreversible.
 * @note This operation's units is different which on many chips.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
EfErrCode ef_port_erase(uint32_t addr, size_t size)
{
    if (sfud_erase(sfud_dev, addr, size) == SFUD_SUCCESS)
    {
        return EF_NO_ERR;
    }
    else
    {
        return EF_ERASE_ERR;
    }
}

/**
 * Write data to flash.
 * @note This operation's units is word.
 * @note This operation must after erase. @see flash_erase.
 *
 * @param addr flash address
 * @param buf the write data buffer
 * @param size write bytes size
 *
 * @return result
 */
EfErrCode ef_port_write(uint32_t addr, const uint32_t* buf, size_t size)
{
    if (sfud_write(sfud_dev, addr, size, (uint8_t*)buf) == SFUD_SUCCESS)
    {
        return EF_NO_ERR;
    }
    else
    {
        return EF_WRITE_ERR;
    }
}

/**
 * lock the ENV ram cache
 */
void ef_port_env_lock(void)
{
    rt_sem_take(&env_cache_lock, RT_WAITING_FOREVER);
}

/**
 * unlock the ENV ram cache
 */
void ef_port_env_unlock(void)
{
    rt_sem_release(&env_cache_lock);
}

