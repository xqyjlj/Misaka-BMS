#include "Misaka_Device_Soft_I2C.h"

#define LOG_NAME "Misaka_Device_Soft_I2C"

/**
 * @brief   产生起始信号
 *
 * @param   ops:    i2c设备
 *
 * @return  void
*/
static void Misaka_Device_Soft_I2C_start(Misaka_Device_Soft_I2C_t ops)
{
    ops->set_sda_out();
    ops->set_sda(0);
    ops->delay_us((ops->us + 1) >> 1);
    ops->set_scl(0);
}

/**
 * @brief   重复产生起始信号，一般是连续读写中
 *
 * @param   ops:    i2c设备
 *
 * @return  void
*/
static void Misaka_Device_Soft_I2C_restart(Misaka_Device_Soft_I2C_t ops)
{
    ops->set_sda_out();
    ops->set_sda(1);
    ops->set_scl(1);
    ops->delay_us((ops->us + 1) >> 1);
    ops->set_sda(0);
    ops->delay_us((ops->us + 1) >> 1);
    ops->set_scl(0);
}

/**
 * @brief   产生停止信号
 *
 * @param   ops:    i2c设备
 *
 * @return  void
*/
static void Misaka_Device_Soft_I2C_stop(Misaka_Device_Soft_I2C_t ops)
{
    ops->set_sda_out();

    ops->set_sda(0);
    ops->delay_us((ops->us + 1) >> 1);
    ops->set_scl(1);
    ops->delay_us((ops->us + 1) >> 1);
    ops->set_sda(1);
    ops->delay_us(ops->us);
}

/**
 * @brief   等待应答信号到来
 *
 * @param   ops:    i2c设备
 *
 * @return  0，接收应答失败
 *          1，接收应答成功
*/
static uint8_t Misaka_Device_Soft_I2C_wait_ack(Misaka_Device_Soft_I2C_t ops)
{
    uint8_t ack;

    ops->set_sda_in();

    ops->set_sda(1);
    ops->delay_us((ops->us + 1) >> 1);
    ops->set_scl(1);
    ack = !ops->get_sda();
    ops->set_scl(0);

    return ack;
}

/**
 * @brief   发送一个字节
 *
 * @param   ops:        i2c设备
 *          data:       待发送数据
 *
 * @return  0，无应答
 *          1，有应答
*/
static uint8_t Misaka_Device_Soft_I2C_write_byte(Misaka_Device_Soft_I2C_t ops, uint8_t data)
{
    int8_t i;
    uint8_t bit;

    ops->set_sda_out();

    for (i = 7; i >= 0; i--)
    {
        ops->set_scl(0);
        bit = (data >> i) & 1;
        ops->set_sda(bit);
        ops->delay_us((ops->us + 1) >> 1);
        ops->set_scl(1);
        ops->delay_us((ops->us + 1) >> 1);
    }
    ops->set_scl(0);
    ops->delay_us((ops->us + 1) >> 1);

    return Misaka_Device_Soft_I2C_wait_ack(ops);
}

/**
 * @brief   读1个字节
 *
 * @param   ops:    i2c设备
 *
 * @return  读取到的1个字节
*/
static uint8_t Misaka_Device_Soft_I2C_read_byte(Misaka_Device_Soft_I2C_t ops)
{
    uint8_t i;
    uint8_t data = 0;

    ops->set_sda_in();

    ops->set_sda(1);
    ops->delay_us((ops->us + 1) >> 1);
    for (i = 0; i < 8; i++)
    {
        data <<= 1;

        ops->set_scl(1);

        if (ops->get_sda())
        {
            data |= 1;
        }
        ops->set_scl(0);
        ops->delay_us(ops->us);
    }

    return data;
}

/**
 * @brief   发送多字节
 *
 * @param   ops:    i2c设备
 *          msg:        消息对象
 *
 * @return  发送的字节数
*/
static uint32_t Misaka_Device_Soft_I2C_send_bytes(Misaka_Device_Soft_I2C_t ops, Misaka_Device_Soft_I2C_message_t msg)
{
    uint8_t ret;
    uint32_t bytes = 0;
    uint8_t* ptr = msg->buf;
    uint32_t len = msg->len;
    uint16_t ignore_nack = msg->flags & Misaka_Device_Soft_I2C_IGNORE_NACK;

    while (len > 0)
    {
        ret = Misaka_Device_Soft_I2C_write_byte(ops, *ptr);

        if ((ret > 0) || (ignore_nack && (ret == 0)))
        {
            len--;
            ptr++;
            bytes++;
        }
        else if (ret == 0)
        {
            return 0;
        }
        else
        {
            return ret;
        }
    }

    return bytes;
}

/**
 * @brief   产生ACK应答
 *
 * @param   ops:    i2c设备
 *          ack:        0, 不产生
 *                      1, 产生
 *
 * @return  void
*/
static void Misaka_Device_Soft_I2C_send_ack_or_nack(Misaka_Device_Soft_I2C_t ops, uint8_t ack)
{
    ops->set_sda_out();

    if (ack)
    {
        ops->set_sda(0);
    }
    ops->delay_us((ops->us + 1) >> 1);
    ops->set_scl(1);
    ops->set_scl(0);
}

/**
 * @brief   接收多字节
 *
 * @param   ops:    i2c设备
 *          msg:        消息对象
 *
 * @return  接收多字节数
*/
static uint32_t Misaka_Device_Soft_I2C_recv_bytes(Misaka_Device_Soft_I2C_t ops, Misaka_Device_Soft_I2C_message_t msg)
{
    uint8_t val;
    uint32_t bytes = 0;   /* actual bytes */
    uint8_t* ptr = msg->buf;
    uint32_t len = msg->len;
    uint16_t flags = msg->flags;

    while (len > 0)
    {
        val = Misaka_Device_Soft_I2C_read_byte(ops);
        if (val >= 0)
        {
            *ptr = val;
            bytes++;
        }
        else
        {
            break;
        }

        ptr++;
        len--;

        if (!(flags & Misaka_Device_Soft_I2C_NO_READ_ACK))
        {
            Misaka_Device_Soft_I2C_send_ack_or_nack(ops, len);
        }
    }

    return bytes;
}

/**
 * @brief   发送地址，启动i2c总线，可重复
 *
 * @param   ops:    i2c设备
 *          addr:       地址
 *          retries:    重复次数
 *
 * @return  0，有应答
 *          1，无应答
*/
static uint8_t Misaka_Device_Soft_I2C_send_address(Misaka_Device_Soft_I2C_t ops, uint8_t addr, uint8_t retries)
{
    uint8_t i;
    uint8_t ret = 0;

    for (i = 0; i <= retries; i++)
    {
        ret = Misaka_Device_Soft_I2C_write_byte(ops, addr);
        if (ret == 1 || i == retries)
        {
            break;
        }
        Misaka_Device_Soft_I2C_stop(ops);
        ops->delay_us(ops->us);
        Misaka_Device_Soft_I2C_start(ops);
    }

    return ret;
}

/**
 * @brief   发送i2c从地址
 *
 * @param   ops:    i2c设备
 *          msg:        消息对象
 *
 * @return  0，有应答
 *          1，无应答
*/
static uint8_t Misaka_Device_Soft_I2C_bit_send_address(Misaka_Device_Soft_I2C_t ops, Misaka_Device_Soft_I2C_message_t msg)
{
    uint16_t flags = msg->flags;
    uint16_t ignore_nack = msg->flags & Misaka_Device_Soft_I2C_IGNORE_NACK;

    uint8_t addr1, addr2, retries;
    uint8_t ret;

    retries = ignore_nack ? 0 : 1;

    if (flags & Misaka_Device_Soft_I2C_ADDR_10BIT)
    {
        addr1 = 0xf0 | ((msg->addr >> 7) & 0x06);
        addr2 = msg->addr & 0xff;

        ret = Misaka_Device_Soft_I2C_send_address(ops, addr1, retries);
        if ((ret != 1) && !ignore_nack)
        {
            return 1;
        }

        ret = Misaka_Device_Soft_I2C_write_byte(ops, addr2);
        if ((ret != 1) && !ignore_nack)
        {
            return 1;
        }
        if (flags & Misaka_Device_Soft_I2C_RD)
        {
            Misaka_Device_Soft_I2C_restart(ops);
            addr1 |= 0x01;
            ret = Misaka_Device_Soft_I2C_send_address(ops, addr1, retries);
            if ((ret != 1) && !ignore_nack)
            {
                return 1;
            }
        }
    }
    else
    {
        /* 7-bit addr */
        addr1 = msg->addr << 1;
        if (flags & Misaka_Device_Soft_I2C_RD)
        {
            addr1 |= 1;
        }
        ret = Misaka_Device_Soft_I2C_send_address(ops, addr1, retries);
        if ((ret != 1) && !ignore_nack)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief   外部操作函数
 *
 * @param   ops:        i2c设备
 *          msg:        消息对象
 *          num:        消息数量
 *
 * @return  操作的消息数
*/
static uint16_t Misaka_Device_Soft_I2C_bit_xfer(Misaka_Device_Soft_I2C_t ops, Misaka_Device_Soft_I2C_message* msgs, uint16_t num)
{
    Misaka_Device_Soft_I2C_message_t msg;
    uint32_t i, ret;
    uint16_t ignore_nack;

    Misaka_Device_Soft_I2C_start(ops);
    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        ignore_nack = msg->flags & Misaka_Device_Soft_I2C_IGNORE_NACK;

        if (!(msg->flags & Misaka_Device_Soft_I2C_NO_START))
        {
            if (i)
            {
                Misaka_Device_Soft_I2C_restart(ops);
            }
            ret = Misaka_Device_Soft_I2C_bit_send_address(ops, msg);
            if ((ret != 0) && !ignore_nack)
            {
                goto out;
            }
        }
        if (msg->flags & Misaka_Device_Soft_I2C_RD)
        {
            ret = Misaka_Device_Soft_I2C_recv_bytes(ops, msg);
            if (ret < msg->len)
            {
                if (ret >= 0)
                {
                    ret = 0;
                }
                goto out;
            }
        }
        else
        {
            ret = Misaka_Device_Soft_I2C_send_bytes(ops, msg);
            if (ret < msg->len)
            {
                if (ret >= 0)
                {
                    ret = 0;
                }
                goto out;
            }
        }
    }
    ret = i;

out:
    Misaka_Device_Soft_I2C_stop(ops);

    return ret;
}

/**
 * @brief   外部操作函数
 *
 * @param   ops:    i2c设备
 *          msg:        消息对象
 *          num:        消息数量
 *
 * @return  操作的消息数
*/
uint16_t Misaka_Device_Soft_I2C_transfer(Misaka_Device_Soft_I2C_t ops, Misaka_Device_Soft_I2C_message* msgs, uint16_t num)
{
    uint16_t ret;

    ops->mutex_take();
    ret = Misaka_Device_Soft_I2C_bit_xfer(ops, msgs, num);
    ops->mutex_release();

    return ret;
}

/**
 * @brief   发送数据
 *
 * @param   ops: i2c设备
 *          addr:   地址
 *          flags:  标志
 *          buf:    待发送数据
 *          count:  发送数据长度
 *
 * @return  操作的消息数
*/
uint16_t Misaka_Device_Soft_I2C_master_send(Misaka_Device_Soft_I2C_t ops, uint16_t addr, uint16_t flags, uint8_t* buf, uint32_t len)
{
    uint16_t ret;
    Misaka_Device_Soft_I2C_message msg;

    msg.addr = addr;
    msg.flags = flags;
    msg.len = len;
    msg.buf = (uint8_t*) buf;

    ret = Misaka_Device_Soft_I2C_transfer(ops, &msg, 1);

    return ret;
}

/**
 * @brief   接收数据
 *
 * @param   ops:        i2c设备
 *          addr:       地址
 *          flags:      标志
 *          rxbuf:      待接收数据
 *          txlen:      接收数据长度
 *
 * @return  操作的消息数
*/
uint16_t Misaka_Device_Soft_I2C_master_recv(Misaka_Device_Soft_I2C_t ops, uint16_t addr, uint16_t flags, uint8_t* rxbuf, uint32_t txlen)
{
    uint16_t ret;
    Misaka_Device_Soft_I2C_message msg;

    msg.addr = addr;
    msg.flags = flags | Misaka_Device_Soft_I2C_RD;
    msg.len = txlen;
    msg.buf = rxbuf;

    ret = Misaka_Device_Soft_I2C_transfer(ops, &msg, 1);

    return ret;
}

/**
 * @brief   发送数据后接收数据
 *
 * @param   ops:        i2c设备
 *          addr:       地址
 *          txbuf:      待发送数据
 *          txlen:      发送数据长度
 *          rxbuf:      待接收数据
 *          rxlen:      接收数据长度
 *
 * @return  操作的消息数
*/
uint16_t Misaka_Device_Soft_I2C_master_send_then_recv(Misaka_Device_Soft_I2C_t ops, uint16_t addr, uint8_t* txbuf, uint32_t txlen, uint8_t* rxbuf, uint32_t rxlen)
{
    uint16_t ret;
    Misaka_Device_Soft_I2C_message msg[2];

    msg[0].addr = addr;
    msg[0].flags = Misaka_Device_Soft_I2C_WR;
    msg[0].buf = txbuf;
    msg[0].len = txlen;

    msg[1].addr = addr;
    msg[1].flags = Misaka_Device_Soft_I2C_RD;
    msg[1].buf = rxbuf;
    msg[1].len = rxlen;

    ret = Misaka_Device_Soft_I2C_transfer(ops, msg, 2);

    return ret;
}

/**
 * @brief   发送数据后接收数据
 *
 * @param   ops:        i2c设备
 *          addr:       地址
 *          txbuf1:     待发送数据1
 *          txlen1:     发送数据长度1
 *          txbuf2:     待接收数据2
 *          txlen2:     接收数据长度2
 *
 * @return  操作的消息数
*/
uint16_t Misaka_Device_Soft_I2C_master_send_then_send(Misaka_Device_Soft_I2C_t ops, uint16_t addr, uint8_t* txbuf1, uint32_t txlen1, uint8_t* txbuf2, uint32_t txlen2)
{
    uint16_t ret;
    Misaka_Device_Soft_I2C_message msg[2];

    msg[0].addr = addr;
    msg[0].flags = Misaka_Device_Soft_I2C_WR;
    msg[0].buf = txbuf1;
    msg[0].len = txlen1;

    msg[1].addr = addr;
    msg[1].flags = Misaka_Device_Soft_I2C_WR | Misaka_Device_Soft_I2C_NO_START;
    msg[1].buf = txbuf2;
    msg[1].len = txlen2;

    ret = Misaka_Device_Soft_I2C_transfer(ops, msg, 2);

    return ret;
}

void Misaka_Device_Soft_I2C_init(Misaka_Device_Soft_I2C_t ops)
{
    Misaka_Device_Soft_I2C_ASSERT(ops);
    Misaka_Device_Soft_I2C_ASSERT(ops->delay_us);
    Misaka_Device_Soft_I2C_ASSERT(ops->set_scl);
    Misaka_Device_Soft_I2C_ASSERT(ops->set_sda);
    Misaka_Device_Soft_I2C_ASSERT(ops->set_sda_out);
    Misaka_Device_Soft_I2C_ASSERT(ops->get_sda);
    Misaka_Device_Soft_I2C_ASSERT(ops->set_sda_in);
    Misaka_Device_Soft_I2C_ASSERT(ops->mutex_release);
    Misaka_Device_Soft_I2C_ASSERT(ops->mutex_take);
}