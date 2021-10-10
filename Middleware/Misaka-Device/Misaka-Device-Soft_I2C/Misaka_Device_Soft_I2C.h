/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: Apache License 2.0
 *
 * Change Logs:
 * Date           Author       Notes                    Email
 * 2021-05-12     xqyjlj       the first version        xqyjlj@126.com
 */

#ifndef __Misaka_Device_Soft_I2C_H__
#define __Misaka_Device_Soft_I2C_H__

#include "stdint.h"

#define Misaka_Device_Soft_I2C_ASSERT        (void *)

/*i2c bus operate flag*/
#define Misaka_Device_Soft_I2C_WR            0x0000
#define Misaka_Device_Soft_I2C_RD            (1u << 0)
#define Misaka_Device_Soft_I2C_ADDR_10BIT    (1u << 2)     /* this is a ten bit chip address */
#define Misaka_Device_Soft_I2C_NO_START      (1u << 4)
#define Misaka_Device_Soft_I2C_IGNORE_NACK   (1u << 5)
#define Misaka_Device_Soft_I2C_NO_READ_ACK   (1u << 6)     /* when I2C reading, we do not ACK */

/* the message of i2c device */
typedef struct
{
    uint16_t addr;
    uint16_t flags;
    uint32_t len;
    uint8_t* buf;
    uint8_t retries;
    uint16_t speed;
} Misaka_Device_Soft_I2C_message, *Misaka_Device_Soft_I2C_message_t;

#define OCTO_I2C_DEBUG
//#define OCTO_I2C_BITS_DEBUG


typedef struct
{
    void (*set_sda)(uint8_t state);

    void (*set_scl)(uint8_t state);

    uint8_t (*get_sda)(void);

    void (*delay_us)(uint16_t us);

    void (*set_sda_out)();

    void (*set_sda_in)();

    void (*mutex_take)();

    void (*mutex_release)();

    uint16_t us;
} Misaka_Device_Soft_I2C, *Misaka_Device_Soft_I2C_t;

uint16_t Misaka_Device_Soft_I2C_master_send(Misaka_Device_Soft_I2C_t ops, uint16_t addr, uint16_t flags, uint8_t* buf, uint32_t len);

uint16_t Misaka_Device_Soft_I2C_master_recv(Misaka_Device_Soft_I2C_t ops, uint16_t addr, uint16_t flags, uint8_t* rxbuf, uint32_t txlen);

uint16_t Misaka_Device_Soft_I2C_master_send_then_recv(Misaka_Device_Soft_I2C_t ops, uint16_t addr, uint8_t* txbuf, uint32_t txlen, uint8_t* rxbuf, uint32_t rxlen);

uint16_t Misaka_Device_Soft_I2C_master_send_then_send(Misaka_Device_Soft_I2C_t ops, uint16_t addr, uint8_t* txbuf1, uint32_t txlen1, uint8_t* txbuf2, uint32_t txlen2);

void Misaka_Device_Soft_I2C_init(Misaka_Device_Soft_I2C_t i2c_bus);

#endif //__Misaka_Device_Soft_I2C_H__