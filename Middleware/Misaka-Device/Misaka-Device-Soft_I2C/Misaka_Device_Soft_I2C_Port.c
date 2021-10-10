#include "Misaka_Device_Soft_I2C.h"
#include "main.h"
#include <rtthread.h>

static Misaka_Device_Soft_I2C i2c_obj;
static struct rt_mutex Misaka_Device_Soft_I2C_mutex;

extern void delay_us(uint16_t us);

static void set_sda(uint8_t level)
{
    if (level == 0)
    {
        LL_GPIO_ResetOutputPin(I2C_SDA_GPIO_Port, I2C_SDA_Pin);
    }
    else
    {
        LL_GPIO_SetOutputPin(I2C_SDA_GPIO_Port, I2C_SDA_Pin);
    }
}

static void set_scl(uint8_t level)
{
    if (level == 0)
    {
        LL_GPIO_ResetOutputPin(I2C_SCL_GPIO_Port, I2C_SCL_Pin);
    }
    else
    {
        LL_GPIO_SetOutputPin(I2C_SCL_GPIO_Port, I2C_SCL_Pin);
    }
}

static uint8_t get_sda()
{
    return LL_GPIO_IsInputPinSet(I2C_SDA_GPIO_Port, I2C_SDA_Pin);
}

static void mutex_take()
{
    rt_mutex_take(&Misaka_Device_Soft_I2C_mutex, RT_WAITING_FOREVER);
}

static void mutex_release()
{
    rt_mutex_release(&Misaka_Device_Soft_I2C_mutex);
}

static void delay_ms(uint16_t ms)
{
    rt_thread_mdelay(ms);
}

static void set_sda_out()
{
//    GPIOB->CRL &= 0X0FFFFFFF;
//    GPIOB->CRL |= (uint32_t) 3 << 28;
}

static void set_sda_in()
{
//    GPIOB->CRL &= 0X0FFFFFFF;
//    GPIOB->CRL |= (uint32_t) 8 << 28;
}

Misaka_Device_Soft_I2C_t Misaka_Device_Soft_I2C_port_init()
{
    rt_mutex_init(&Misaka_Device_Soft_I2C_mutex, "Misaka_Device_Soft_I2C_mutex", RT_IPC_FLAG_FIFO);

    i2c_obj.delay_us = delay_us;
    i2c_obj.get_sda = get_sda;
    i2c_obj.mutex_release = mutex_release;
    i2c_obj.mutex_take = mutex_take;
    i2c_obj.set_scl = set_scl;
    i2c_obj.set_sda = set_sda;
    i2c_obj.set_sda_out = set_sda_out;
    i2c_obj.set_sda_in = set_sda_in;
    i2c_obj.us = 1;

    set_sda(1);
    set_scl(1);

    Misaka_Device_Soft_I2C_init(&i2c_obj);

    return &i2c_obj;
}

