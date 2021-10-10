/**
 * @file eeprom.h
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

#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "stdint.h"
#include "Misaka_AT24CXX.h"

typedef enum
{
    EEPROM_TABLE_TEMPERATURE_LPF_FACTOR = 0,//uint32_t
    EEPROM_TABLE_VUV = 4,//uint16_t
    EEPROM_TABLE_VOV = 6,//uint16_t
    EEPROM_TABLE_CURRENT_LPF_FACTOR = 8,//uint32_t
} BMS_PARAMETER_TABLE;

#define DEFAULT_TEMPERATURE_LPF_FACTOR          1
#define DEFAULT_VUV                             37000
#define DEFAULT_VOV                             42000
#define DEFAULT_CURRENT_LPF_FACTOR              1


extern Misaka_AT24CXX_t at24cxx_obj;

uint8_t Eeprom_Read_Uint32(uint32_t* data, uint16_t addr);
uint8_t Eeprom_Read_Uint16(uint16_t* data, uint16_t addr);
uint8_t Eeprom_Read_Uint8(uint8_t* data, uint16_t addr);
uint8_t Eeprom_Write_Uint32(uint32_t data, uint16_t addr);
uint8_t Eeprom_Write_Uint16(uint16_t data, uint16_t addr);
uint8_t Eeprom_Write_Uint8(uint8_t data, uint16_t addr);

void Restore_Factory_Parameters();
#endif
