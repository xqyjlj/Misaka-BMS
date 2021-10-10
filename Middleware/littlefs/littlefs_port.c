/**
 * @file littlefs_port.c
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-02
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-02 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#include <rtthread.h>
#include "littlefs.h"
#include <stdio.h>
#include <string.h>
#include "sfud.h"

static sfud_flash_t sfud_dev = NULL;
static struct rt_mutex littlefs_mutex;
int littlefs_init()
{
    sfud_dev = sfud_get_device(SFUD_W25Q128_DEVICE_INDEX);
    rt_mutex_init(&littlefs_mutex, "littlefs_mutex", RT_IPC_FLAG_FIFO);
    int err = lfs_mount(&littlefs, &littlefs_cfg);

    if (err)
    {
        lfs_format(&littlefs, &littlefs_cfg);
        return lfs_mount(&littlefs, &littlefs_cfg);
    }
    return 1;
}

#ifdef LFS_THREADSAFE
// Lock the underlying block device. Negative error codes
// are propogated to the user.
static int _lock(const struct lfs_config* c)
{
    if (rt_mutex_take(&littlefs_mutex, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -1;
    }
    return 0;
}

// Unlock the underlying block device. Negative error codes
// are propogated to the user.
static int _unlock(const struct lfs_config* c)
{
    if (rt_mutex_release(&littlefs_mutex) != RT_EOK)
    {
        return -1;
    }
    return 0;
}
#endif

static int _block_read(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, void* buffer, lfs_size_t size)
{
    return sfud_read(sfud_dev, block * c->block_size + off, size, (uint8_t*)buffer);
}
static int _block_prog(const struct lfs_config* c, lfs_block_t block, lfs_off_t off, const void* buffer, lfs_size_t size)
{
    return sfud_write(sfud_dev, block * c->block_size + off, size, (uint8_t*)buffer);
}
static int _block_erase(const struct lfs_config* c, lfs_block_t block)
{
    return sfud_erase(sfud_dev, block * c->block_size, 1);
}
static int _block_sync(const struct lfs_config* c)
{
    return 0;
}

struct lfs littlefs = {0};

struct lfs_config littlefs_cfg =
{
    // block device operations
    .read  = _block_read,
    .prog  = _block_prog,
    .erase = _block_erase,
    .sync  = _block_sync,

    .lock = _lock,
    .unlock = _unlock,

    // block device configuration
    .read_size = 16,
    .prog_size = 16,
    .cache_size = 16,
    .block_cycles = -1,
    .block_size = 4096,
    .block_count = 4096,
    .lookahead_size = 16,
};









