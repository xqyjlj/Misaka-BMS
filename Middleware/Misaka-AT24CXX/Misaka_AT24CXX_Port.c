#include "Misaka_Device_Soft_I2C.h"
#include "Misaka_AT24CXX.h"
#include "rtthread.h"

static struct rt_mutex Misaka_AT24CXX_mutex;
Misaka_AT24CXX Misaka_AT24CXX_obj = {0};
static Misaka_Device_Soft_I2C_t i2c_obj;


static uint16_t i2c_send_then_recv(uint8_t address, uint8_t* txbuf, uint32_t txlen, uint8_t* rxbuf, uint32_t rxlen)
{
    uint16_t ret;
    ret = Misaka_Device_Soft_I2C_master_send_then_recv(i2c_obj, address, txbuf, txlen, rxbuf, rxlen);
    if (ret == 2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

static uint16_t i2c_send_then_send(uint8_t address, uint8_t* txbuf1, uint32_t txlen1, uint8_t* txbuf2, uint32_t txlen2)
{
    uint16_t ret;
    ret = Misaka_Device_Soft_I2C_master_send_then_send(i2c_obj, address, txbuf1, txlen1, txbuf2, txlen2);
    if (ret == 2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

static void delay_ms(uint16_t ms)
{
    rt_thread_mdelay(ms);
}

static void mutex_take()
{
    rt_mutex_take(&Misaka_AT24CXX_mutex, RT_WAITING_FOREVER);
}

static void mutex_release()
{
    rt_mutex_release(&Misaka_AT24CXX_mutex);
}

Misaka_AT24CXX_t Misaka_AT24CXX_port_init(Misaka_Device_Soft_I2C_t ops)
{
    i2c_obj = ops;

    rt_mutex_init(&Misaka_AT24CXX_mutex, "Misaka_AT24CXX_mutex", RT_IPC_FLAG_FIFO);

    Misaka_AT24CXX_obj.type = OCTO_AT24C02;
    Misaka_AT24CXX_obj.isFRAM = 0;
    Misaka_AT24CXX_obj.mutex_release = mutex_release;
    Misaka_AT24CXX_obj.mutex_take = mutex_take;
    Misaka_AT24CXX_obj.delay_ms = delay_ms;
    Misaka_AT24CXX_obj.i2c_send_then_recv = i2c_send_then_recv;
    Misaka_AT24CXX_obj.i2c_send_then_send = i2c_send_then_send;
    Misaka_AT24CXX_obj.address = 0x50;

    Misaka_AT24CXX_Init(&Misaka_AT24CXX_obj);

    return &Misaka_AT24CXX_obj;
}
