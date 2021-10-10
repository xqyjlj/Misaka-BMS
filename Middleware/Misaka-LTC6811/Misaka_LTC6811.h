/**
 * @file Misaka_LTC6811.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-07-22
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-07-22 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#ifndef __MISAKA_LTC6811_H__
#define __MISAKA_LTC6811_H__

#include "Misaka_LTC6811_Base.h"

typedef struct
{
    uint8_t     GPIOX;
    uint8_t     REFON;
    uint8_t     DTEN;       //只读位
    uint8_t     ADCOPT;
    uint16_t    VUV;
    uint16_t    VOV;
    uint8_t     DCTO;
} Misaka_LTC6811_CFGR_Struct;

#define Misaka_LTC6811_Delay_Unit 3

uint8_t Misaka_LTC6811_WakeIdle(void);
uint8_t Misaka_LTC6811_WRCFGA(Misaka_LTC6811_CFGR_Struct* cfgr);
uint8_t Misaka_LTC6811_RDCFGA(void);
uint8_t Misaka_LTC6811_RDCVA(void);
uint8_t Misaka_LTC6811_RDCVB(void);
uint8_t Misaka_LTC6811_RDCVC(void);
uint8_t Misaka_LTC6811_RDCVD(void);
uint8_t Misaka_LTC6811_RDAUXA(void);
uint8_t Misaka_LTC6811_RDAUXB(void);
uint8_t Misaka_LTC6811_RDSTATA(void);
uint8_t Misaka_LTC6811_RDSTATB(void);
uint8_t Misaka_LTC6811_WRSCTRL(void);
uint8_t Misaka_LTC6811_WRPWM(void);
uint8_t Misaka_LTC6811_RDSCTRL(void);
uint8_t Misaka_LTC6811_RDPWM(void);
uint8_t Misaka_LTC6811_STSCTRL(void);
uint8_t Misaka_LTC6811_CLRSCTRL(void);
uint8_t Misaka_LTC6811_ADCV(uint16_t md, uint8_t dcp, uint8_t ch);
uint8_t Misaka_LTC6811_ADOW(uint16_t md, uint8_t pup, uint8_t dcp, uint8_t ch);
uint8_t Misaka_LTC6811_CVST(uint16_t md, uint8_t st);
uint8_t Misaka_LTC6811_ADOL(uint16_t md, uint8_t dcp);
uint8_t Misaka_LTC6811_ADAX(uint16_t md, uint8_t chg);
uint8_t Misaka_LTC6811_ADAXD(uint16_t md, uint8_t chg);
uint8_t Misaka_LTC6811_AXST(uint16_t md, uint8_t st);
uint8_t Misaka_LTC6811_ADSTAT(uint16_t md, uint8_t chst);
uint8_t Misaka_LTC6811_ADSTATD(uint16_t md, uint8_t chst);
uint8_t Misaka_LTC6811_STATST(uint16_t md, uint8_t st);
uint8_t Misaka_LTC6811_ADCVAX(uint16_t md, uint8_t dcp);
uint8_t Misaka_LTC6811_ADCVSC(uint16_t md, uint8_t dcp);
uint8_t Misaka_LTC6811_CLRCELL(void);
uint8_t Misaka_LTC6811_CLRAUX(void);
uint8_t Misaka_LTC6811_CLRSTAT(void);
uint8_t Misaka_LTC6811_PLADC(void);
uint8_t Misaka_LTC6811_DIAGN(void);
uint8_t Misaka_LTC6811_WRCOMM(void);
uint8_t Misaka_LTC6811_RDCOMM(void);
uint8_t Misaka_LTC6811_STCOMM(void);
uint8_t Misaka_LTC6811_Calculate_Cell_Voltage(void);
uint8_t Misaka_LTC6811_Read_All_Cell_Voltage(uint16_t md, uint8_t dcp, uint8_t ch);
uint8_t Misaka_LTC6811_Calculate_Auxiliary_Voltage(void);
uint8_t Misaka_LTC6811_Read_All_Auxiliary_Voltage(uint16_t md, uint8_t chg);
uint8_t Misaka_LTC6811_Calculate_Status(void);
uint8_t Misaka_LTC6811_Read_All_Status(uint16_t md, uint8_t chst);
uint8_t Misaka_LTC6811_Cell_Voltage_Self_Test(uint16_t md, uint8_t st, uint16_t stc);
uint8_t Misaka_LTC6811_Auxiliary_Voltage_Self_Test(uint16_t md, uint8_t st, uint16_t stc);
uint8_t Misaka_LTC6811_Status_Voltage_Self_Test(uint16_t md, uint8_t st, uint16_t stc);
uint8_t Misaka_LTC6811_Status_Self_Test(uint16_t md, uint8_t st, uint16_t stc);
uint8_t Misaka_LTC6811_Open_Wire_Check(uint16_t md, uint8_t dcp, uint8_t ch);
uint8_t Misaka_LTC6811_Balance_Group(uint8_t group);
void Misaka_LTC6811_DCC_Flag(uint8_t balance_threshold);
void Misaka_LTC6811_Max_Cell_Voltage();
void Misaka_LTC6811_Min_Cell_Voltage();
uint8_t Misaka_LTC6811_Self_Test(uint16_t md, uint8_t st, uint16_t stc);
void Misaka_LTC6811_Calculate_ALL_NTC_Resistance(void);

#endif
