/**
 * @file eeprom.c
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
#include "eeprom.h"
#include "Misaka_Device_Soft_I2C.h"
#include "rtthread.h"
#include "system.h"

#define LOG_NAME "eeprom"

extern Misaka_Device_Soft_I2C_t Misaka_Device_Soft_I2C_port_init();
extern Misaka_AT24CXX_t Misaka_AT24CXX_port_init(Misaka_Device_Soft_I2C_t ops);

uint8_t eeprom_status = 0;
Misaka_Device_Soft_I2C_t soft_i2c_obj;
Misaka_AT24CXX_t at24cxx_obj;

/**
 * @brief                   EEPROM 读取数据（32位）
 * @param  data             待读取数据
 * @param  addr             地址
 * @return uint8_t @c       1：错误
 *                          0：成功
 */
uint8_t Eeprom_Read_Uint32(uint32_t* data, uint16_t addr)
{
    if (eeprom_status == 1)
    {
        return 1;
    }
    uint8_t buf[4];
    uint8_t status;
    status = Misaka_AT24CXX_Read(at24cxx_obj, addr, buf, 4);
    *data = (buf[0] << 0) + ((uint16_t)buf[1] << 8) + ((uint32_t)buf[2] << 16) + ((uint32_t)buf[3] << 24);
    return status;
}

/**
 * @brief                   EEPROM 读取数据（16位）
 * @param  data             待读取数据
 * @param  addr             地址
 * @return uint8_t @c       1：错误
 *                          0：成功
 */
uint8_t Eeprom_Read_Uint16(uint16_t* data, uint16_t addr)
{
    if (eeprom_status == 1)
    {
        return 1;
    }
    uint8_t buf[2];
    uint8_t status;
    status = Misaka_AT24CXX_Read(at24cxx_obj, addr, buf, 2);
    *data = (buf[0] << 0) + ((uint16_t)buf[1] << 8);
    return status;
}

/**
 * @brief                   EEPROM 读取数据（8位）
 * @param  data             待读取数据
 * @param  addr             地址
 * @return uint8_t @c       1：错误
 *                          0：成功
 */
uint8_t Eeprom_Read_Uint8(uint8_t* data, uint16_t addr)
{
    if (eeprom_status == 1)
    {
        return 1;
    }
    uint8_t status;
    status = Misaka_AT24CXX_Read(at24cxx_obj, addr, data, 1);
    return status;
}

/**
 * @brief                   EEPROM 写入数据（32位）
 * @param  data             待写入数据
 * @param  addr             地址
 * @return uint8_t @c       1：错误
 *                          0：成功
 */
uint8_t Eeprom_Write_Uint32(uint32_t data, uint16_t addr)
{
    if (eeprom_status == 1)
    {
        return 1;
    }
    uint8_t buf[4];
    buf[0] = (uint8_t)(data >> 0);
    buf[1] = (uint8_t)(data >> 8);
    buf[2] = (uint8_t)(data >> 16);
    buf[3] = (uint8_t)(data >> 24);
    uint8_t status;
    status = Misaka_AT24CXX_Write(at24cxx_obj, addr, buf, 4);
    return status;
}

/**
 * @brief                   EEPROM 写入数据（16位）
 * @param  data             待写入数据
 * @param  addr             地址
 * @return uint8_t @c       1：错误
 *                          0：成功
 */
uint8_t Eeprom_Write_Uint16(uint16_t data, uint16_t addr)
{
    if (eeprom_status == 1)
    {
        return 1;
    }
    uint8_t buf[2];
    buf[0] = (uint8_t)(data >> 0);
    buf[1] = (uint8_t)(data >> 8);
    uint8_t status;
    status = Misaka_AT24CXX_Write(at24cxx_obj, addr, buf, 2);
    return status;
}

/**
 * @brief                   EEPROM 写入数据（8位）
 * @param  data             待写入数据
 * @param  addr             地址
 * @return uint8_t @c       1：错误
 *                          0：成功
 */
uint8_t Eeprom_Write_Uint8(uint8_t data, uint16_t addr)
{
    if (eeprom_status == 1)
    {
        return 1;
    }
    uint8_t status;
    status = Misaka_AT24CXX_Write(at24cxx_obj, addr, &data, 1);
    return status;
}

void Restore_Factory_Parameters()
{
    Eeprom_Write_Uint32(DEFAULT_TEMPERATURE_LPF_FACTOR, EEPROM_TABLE_TEMPERATURE_LPF_FACTOR);
    Eeprom_Write_Uint16(DEFAULT_VUV, EEPROM_TABLE_VUV);
    Eeprom_Write_Uint16(DEFAULT_VOV, EEPROM_TABLE_VOV);
    Eeprom_Write_Uint32(DEFAULT_CURRENT_LPF_FACTOR, EEPROM_TABLE_CURRENT_LPF_FACTOR);
}

static int eeprom_init()
{
    soft_i2c_obj = Misaka_Device_Soft_I2C_port_init();
    at24cxx_obj = Misaka_AT24CXX_port_init(soft_i2c_obj);
    eeprom_status = Misaka_AT24CXX_Check(at24cxx_obj);
    if (eeprom_status == 1)
    {
        LOG_E("eeprom check error");
    }
    else
    {
        LOG_D("eeprom check ok");
        uint8_t rxbuf = 0;
        Misaka_AT24CXX_Read(at24cxx_obj, at24cxx_obj->capacity - 2, &rxbuf, 1);
        if (rxbuf != 0x55)
        {
            Restore_Factory_Parameters();
        }
        rxbuf = 0x55;
        Misaka_AT24CXX_Write(at24cxx_obj, at24cxx_obj->capacity - 2, &rxbuf, 1);
    }

    Restore_Factory_Parameters();//TODO 正式使用时注释掉

    return 0;
}

INIT_DEVICE_EXPORT(eeprom_init);
