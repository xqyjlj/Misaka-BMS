/**
 * @file Misaka_LTC6811.c
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
#include "Misaka_LTC6811.h"

/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_WakeIdle(void)
{
    return Misaka_LTC6811_CMD_WakeIdle();
}
/**
 * @brief
 * @param  cfgr             desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_WRCFGA(Misaka_LTC6811_CFGR_Struct* cfgr)
{
    uint16_t vuv = (((cfgr->VUV * 10) / 16) - 1);
    uint16_t vov = ((cfgr->VOV * 10) / 16);
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].CFGR[0] = cfgr->GPIOX | cfgr->REFON | cfgr->DTEN | cfgr->ADCOPT;
        Misaka_LTC6811_Device_Object[i].CFGR[1] = 0x00FF & vuv;
        Misaka_LTC6811_Device_Object[i].CFGR[2] = ((0x000F & vov) << 4) + ((0x0F00 & vuv) >> 8);
        Misaka_LTC6811_Device_Object[i].CFGR[3] = (0x0FF0 & vov) >> 4;
        Misaka_LTC6811_Device_Object[i].CFGR[4] = 0x00FF & 0x0000;
        Misaka_LTC6811_Device_Object[i].CFGR[5] = cfgr->DCTO | ((0x0F00 & 0x0000) >> 8);
    }
    return Misaka_LTC6811_CMD_WRCFGA();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDCFGA(void)
{
    return Misaka_LTC6811_CMD_RDCFGA();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDCVA(void)
{
    return Misaka_LTC6811_CMD_RDCVA();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDCVB(void)
{
    return Misaka_LTC6811_CMD_RDCVB();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDCVC(void)
{
    return Misaka_LTC6811_CMD_RDCVC();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDCVD(void)
{
    return Misaka_LTC6811_CMD_RDCVD();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDAUXA(void)
{
    return Misaka_LTC6811_CMD_RDAUXA();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDAUXB(void)
{
    return Misaka_LTC6811_CMD_RDAUXB();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDSTATA(void)
{
    return Misaka_LTC6811_CMD_RDSTATA();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDSTATB(void)
{
    return Misaka_LTC6811_CMD_RDSTATB();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_WRSCTRL(void)
{
    return Misaka_LTC6811_CMD_WRSCTRL();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_WRPWM(void)
{
    return Misaka_LTC6811_CMD_WRPWM();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDSCTRL(void)
{
    return Misaka_LTC6811_CMD_RDSCTRL();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDPWM(void)
{
    return Misaka_LTC6811_CMD_RDPWM();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_STSCTRL(void)
{
    return Misaka_LTC6811_CMD_STSCTRL();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_CLRSCTRL(void)
{
    return Misaka_LTC6811_CMD_CLRSCTRL();
}
/**
 * @brief
 * @param  md               desc
 * @param  dcp              desc
 * @param  ch               desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADCV(uint16_t md, uint8_t dcp, uint8_t ch)
{
    return Misaka_LTC6811_CMD_ADCV(md | dcp | ch);
}
/**
 * @brief
 * @param  md               desc
 * @param  pup              desc
 * @param  dcp              desc
 * @param  ch               desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADOW(uint16_t md, uint8_t pup, uint8_t dcp, uint8_t ch)
{
    return Misaka_LTC6811_CMD_ADOW(md | pup | dcp | ch);
}
/**
 * @brief
 * @param  md               desc
 * @param  st               desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_CVST(uint16_t md, uint8_t st)
{
    return Misaka_LTC6811_CMD_CVST(md | st);
}
/**
 * @brief
 * @param  md               desc
 * @param  dcp              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADOL(uint16_t md, uint8_t dcp)
{
    return Misaka_LTC6811_CMD_ADOL(md | dcp);
}
/**
 * @brief
 * @param  md               desc
 * @param  chg              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADAX(uint16_t md, uint8_t chg)
{
    return Misaka_LTC6811_CMD_ADAX(md | chg);
}
/**
 * @brief
 * @param  md               desc
 * @param  chg              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADAXD(uint16_t md, uint8_t chg)
{
    return Misaka_LTC6811_CMD_ADAXD(md | chg);
}
/**
 * @brief
 * @param  md               desc
 * @param  st               desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_AXST(uint16_t md, uint8_t st)
{
    return Misaka_LTC6811_CMD_AXST(md | st);
}
/**
 * @brief
 * @param  md               desc
 * @param  chst             desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADSTAT(uint16_t md, uint8_t chst)
{
    return Misaka_LTC6811_CMD_ADSTAT(md | chst);
}
/**
 * @brief
 * @param  md               desc
 * @param  chst             desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADSTATD(uint16_t md, uint8_t chst)
{
    return Misaka_LTC6811_CMD_ADSTATD(md | chst);
}
/**
 * @brief
 * @param  md               desc
 * @param  st               desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_STATST(uint16_t md, uint8_t st)
{
    return Misaka_LTC6811_CMD_STATST(md | st);
}
/**
 * @brief
 * @param  md               desc
 * @param  dcp              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADCVAX(uint16_t md, uint8_t dcp)
{
    return Misaka_LTC6811_CMD_ADCVAX(md | dcp);
}
/**
 * @brief
 * @param  md               desc
 * @param  dcp              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_ADCVSC(uint16_t md, uint8_t dcp)
{
    return Misaka_LTC6811_CMD_ADCVSC(md | dcp);
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_CLRCELL(void)
{
    return Misaka_LTC6811_CMD_CLRCELL();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_CLRAUX(void)
{
    return Misaka_LTC6811_CMD_CLRAUX();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_CLRSTAT(void)
{
    return Misaka_LTC6811_CMD_CLRSTAT();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_PLADC(void)
{
    return Misaka_LTC6811_CMD_PLADC();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_DIAGN(void)
{
    return Misaka_LTC6811_CMD_DIAGN();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_WRCOMM(void)
{
    return Misaka_LTC6811_CMD_WRCOMM();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_RDCOMM(void)
{
    return Misaka_LTC6811_CMD_RDCOMM();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_STCOMM(void)
{
    return Misaka_LTC6811_CMD_STCOMM();
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Calculate_Cell_Voltage(void)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_RDCVA();
    status += Misaka_LTC6811_RDCVB();
    status += Misaka_LTC6811_RDCVC();
    status += Misaka_LTC6811_RDCVD();
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++) //将电压缓存在电压辅助数组里
    {
        Misaka_LTC6811_Device_Object[i].CellVolt[0] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVAR[1]) << 8) + Misaka_LTC6811_Device_Object[i].CVAR[0];
        Misaka_LTC6811_Device_Object[i].CellVolt[1] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVAR[3]) << 8) + Misaka_LTC6811_Device_Object[i].CVAR[2];
        Misaka_LTC6811_Device_Object[i].CellVolt[2] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVAR[5]) << 8) + Misaka_LTC6811_Device_Object[i].CVAR[4];
        Misaka_LTC6811_Device_Object[i].CellVolt[3] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVBR[1]) << 8) + Misaka_LTC6811_Device_Object[i].CVBR[0];
        Misaka_LTC6811_Device_Object[i].CellVolt[4] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVBR[3]) << 8) + Misaka_LTC6811_Device_Object[i].CVBR[2];
        Misaka_LTC6811_Device_Object[i].CellVolt[5] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVBR[5]) << 8) + Misaka_LTC6811_Device_Object[i].CVBR[4];
        Misaka_LTC6811_Device_Object[i].CellVolt[6] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVCR[1]) << 8) + Misaka_LTC6811_Device_Object[i].CVCR[0];
        Misaka_LTC6811_Device_Object[i].CellVolt[7] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVCR[3]) << 8) + Misaka_LTC6811_Device_Object[i].CVCR[2];
        Misaka_LTC6811_Device_Object[i].CellVolt[8] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVCR[5]) << 8) + Misaka_LTC6811_Device_Object[i].CVCR[4];
        Misaka_LTC6811_Device_Object[i].CellVolt[9] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVDR[1]) << 8) + Misaka_LTC6811_Device_Object[i].CVDR[0];
        Misaka_LTC6811_Device_Object[i].CellVolt[10] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVDR[3]) << 8) + Misaka_LTC6811_Device_Object[i].CVDR[2];
        Misaka_LTC6811_Device_Object[i].CellVolt[11] = (((uint16_t)Misaka_LTC6811_Device_Object[i].CVDR[5]) << 8) + Misaka_LTC6811_Device_Object[i].CVDR[4];
    }
    return status;
}
/**
 * @brief
 * @param  md               desc
 * @param  dcp              desc
 * @param  ch               desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Read_All_Cell_Voltage(uint16_t md, uint8_t dcp, uint8_t ch)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_ADCV(md, dcp, ch);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_Calculate_Cell_Voltage();
    return status;
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Calculate_Auxiliary_Voltage(void)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_RDAUXA();
    status += Misaka_LTC6811_RDAUXB();
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].GPIOVolt[0] = (((uint16_t)Misaka_LTC6811_Device_Object[i].AVAR[1]) << 8) + Misaka_LTC6811_Device_Object[i].AVAR[0];
        Misaka_LTC6811_Device_Object[i].GPIOVolt[1] = (((uint16_t)Misaka_LTC6811_Device_Object[i].AVAR[3]) << 8) + Misaka_LTC6811_Device_Object[i].AVAR[2];
        Misaka_LTC6811_Device_Object[i].GPIOVolt[2] = (((uint16_t)Misaka_LTC6811_Device_Object[i].AVAR[5]) << 8) + Misaka_LTC6811_Device_Object[i].AVAR[4];
        Misaka_LTC6811_Device_Object[i].GPIOVolt[3] = (((uint16_t)Misaka_LTC6811_Device_Object[i].AVBR[1]) << 8) + Misaka_LTC6811_Device_Object[i].AVBR[0];
        Misaka_LTC6811_Device_Object[i].GPIOVolt[4] = (((uint16_t)Misaka_LTC6811_Device_Object[i].AVBR[3]) << 8) + Misaka_LTC6811_Device_Object[i].AVBR[2];
        Misaka_LTC6811_Device_Object[i].REFVolt = (((uint16_t)Misaka_LTC6811_Device_Object[i].AVBR[5]) << 8) + Misaka_LTC6811_Device_Object[i].AVBR[4];
    }
    return status;
}
/**
 * @brief
 * @param  md               desc
 * @param  chg              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Read_All_Auxiliary_Voltage(uint16_t md, uint8_t chg)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_ADAX(md, chg);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_Calculate_Auxiliary_Voltage();
    return status;
}
/**
 * @brief
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Calculate_Status(void)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_RDSTATA();
    status += Misaka_LTC6811_RDSTATB();
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].SOCVolt = (((uint16_t)Misaka_LTC6811_Device_Object[i].STAR[1]) << 8) + Misaka_LTC6811_Device_Object[i].STAR[0];
        Misaka_LTC6811_Device_Object[i].TotalVolt = Misaka_LTC6811_Device_Object[i].SOCVolt * 20;
        Misaka_LTC6811_Device_Object[i].ITMPVolt = (((uint16_t)Misaka_LTC6811_Device_Object[i].STAR[3]) << 8) + Misaka_LTC6811_Device_Object[i].STAR[2];
        Misaka_LTC6811_Device_Object[i].ITM = ((Misaka_LTC6811_Device_Object[i].ITMPVolt * 100) / 75) - 273;
        Misaka_LTC6811_Device_Object[i].VAVolt = (((uint16_t)Misaka_LTC6811_Device_Object[i].STAR[5]) << 8) + Misaka_LTC6811_Device_Object[i].STAR[4];
        Misaka_LTC6811_Device_Object[i].VDVolt = (((uint16_t)Misaka_LTC6811_Device_Object[i].STBR[1]) << 8) + Misaka_LTC6811_Device_Object[i].STBR[0];
        Misaka_LTC6811_Device_Object[i].CV_Flag = (((uint32_t)Misaka_LTC6811_Device_Object[i].STBR[4]) << 16) + (((uint16_t)Misaka_LTC6811_Device_Object[i].STBR[3]) << 8) + Misaka_LTC6811_Device_Object[i].STBR[2];
        Misaka_LTC6811_Device_Object[i].REV = (Misaka_LTC6811_Device_Object[i].STBR[5] & 0xF0) >> 4;
        Misaka_LTC6811_Device_Object[i].MuxFail = (Misaka_LTC6811_Device_Object[i].STBR[5] & 0x02) >> 1;
        Misaka_LTC6811_Device_Object[i].Thsd = (Misaka_LTC6811_Device_Object[i].STBR[5] & 0x01) >> 0;
    }
    return status;
}
/**
 * @brief
 * @param  md               desc
 * @param  chst             desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Read_All_Status(uint16_t md, uint8_t chst)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_ADSTAT(md, chst);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_Calculate_Status();
    return status;
}
/**
 * @brief
 * @param  md               desc
 * @param  st               desc
 * @param  stc              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Cell_Voltage_Self_Test(uint16_t md, uint8_t st, uint16_t stc)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_CLRCELL();
    status += Misaka_LTC6811_CVST(md, st);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_Calculate_Cell_Voltage();
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        for (uint8_t j = 0; j < 12; j++)
        {
            if (Misaka_LTC6811_Device_Object[i].CellVolt[j] != stc)
            {
                status ++;
            }
        }
    }
    return status;
}
/**
 * @brief
 * @param  md               desc
 * @param  st               desc
 * @param  stc              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Auxiliary_Voltage_Self_Test(uint16_t md, uint8_t st, uint16_t stc)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_CLRAUX();
    status += Misaka_LTC6811_AXST(md, st);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_Calculate_Auxiliary_Voltage();
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        for (uint8_t j = 0; j < 5; j++)
        {
            if (Misaka_LTC6811_Device_Object[i].GPIOVolt[j] != stc)
            {
                status ++;
            }
        }
        if (Misaka_LTC6811_Device_Object[i].REFVolt != stc)
        {
            status ++;
        }
    }
    return status;
}
/**
 * @brief
 * @param  md               desc
 * @param  st               desc
 * @param  stc              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Status_Voltage_Self_Test(uint16_t md, uint8_t st, uint16_t stc)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_CLRSTAT();
    status += Misaka_LTC6811_STATST(md, st);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_Calculate_Status();
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        if (Misaka_LTC6811_Device_Object[i].SOCVolt != stc)
        {
            status ++;
        }
        if (Misaka_LTC6811_Device_Object[i].ITMPVolt != stc)
        {
            status ++;
        }
        if (Misaka_LTC6811_Device_Object[i].VAVolt != stc)
        {
            status ++;
        }
        if (Misaka_LTC6811_Device_Object[i].VDVolt != stc)
        {
            status ++;
        }
    }
    return status;
}

/**
 * @brief
 * @param  md               desc
 * @param  st               desc
 * @param  stc              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Status_Self_Test(uint16_t md, uint8_t st, uint16_t stc)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_CLRSTAT();
    status += Misaka_LTC6811_STATST(md, st);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_DIAGN();
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_Calculate_Status();
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        if (Misaka_LTC6811_Device_Object[i].SOCVolt != stc)
        {
            status ++;
        }
        if (Misaka_LTC6811_Device_Object[i].ITMPVolt != stc)
        {
            status ++;
        }
        if (Misaka_LTC6811_Device_Object[i].VAVolt != stc)
        {
            status ++;
        }
        if (Misaka_LTC6811_Device_Object[i].VDVolt != stc)
        {
            status ++;
        }
        if (Misaka_LTC6811_Device_Object[i].MuxFail != 0)
        {
            status ++;
        }
    }
    return status;
}
/**
 * @brief
 * @param  md               desc
 * @param  dcp              desc
 * @param  ch               desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Open_Wire_Check(uint16_t md, uint8_t dcp, uint8_t ch)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_CLRCELL();
    /*上拉电流源*/
    status += Misaka_LTC6811_ADOW(md, LTC6811_PUP1, dcp, ch);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_ADOW(md, LTC6811_PUP1, dcp, ch);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_ADOW(md, LTC6811_PUP1, dcp, ch);

    status += Misaka_LTC6811_Calculate_Cell_Voltage();

    /*下拉电流源*/
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_CLRCELL();
    status += Misaka_LTC6811_ADOW(md, LTC6811_PUP0, dcp, ch);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_ADOW(md, LTC6811_PUP0, dcp, ch);
    Misaka_LTC6811_Delay_Ms(Misaka_LTC6811_Delay_Unit);
    status += Misaka_LTC6811_ADOW(md, LTC6811_PUP0, dcp, ch);

    status += Misaka_LTC6811_RDCVA();
    status += Misaka_LTC6811_RDCVB();
    status += Misaka_LTC6811_RDCVC();
    status += Misaka_LTC6811_RDCVD();

    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].OPENWires = 0;
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[0] == 0))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 0);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[0] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVAR[1]) << 8) + Misaka_LTC6811_Device_Object[i].CVAR[0]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 1);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[1] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVAR[3]) << 8) + Misaka_LTC6811_Device_Object[i].CVAR[2]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 2);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[2] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVAR[5]) << 8) + Misaka_LTC6811_Device_Object[i].CVAR[4]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 3);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[3] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVBR[1]) << 8) + Misaka_LTC6811_Device_Object[i].CVBR[0]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 4);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[4] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVBR[3]) << 8) + Misaka_LTC6811_Device_Object[i].CVBR[2]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 5);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[5] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVBR[5]) << 8) + Misaka_LTC6811_Device_Object[i].CVBR[4]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 6);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[6] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVCR[1]) << 8) + Misaka_LTC6811_Device_Object[i].CVCR[0]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 7);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[7] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVCR[3]) << 8) + Misaka_LTC6811_Device_Object[i].CVCR[2]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 8);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[8] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVCR[5]) << 8) + Misaka_LTC6811_Device_Object[i].CVCR[4]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 9);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[9] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVDR[1]) << 8) + Misaka_LTC6811_Device_Object[i].CVDR[0]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 10);
        }
        if ((Misaka_LTC6811_Device_Object[i].CellVolt[10] - ((((uint16_t)Misaka_LTC6811_Device_Object[i].CVDR[3]) << 8) + Misaka_LTC6811_Device_Object[i].CVDR[2]) < -4000))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 11);
        }
        if ((((((uint16_t)Misaka_LTC6811_Device_Object[i].CVDR[5]) << 8) + Misaka_LTC6811_Device_Object[i].CVDR[4]) == 0) && ((0x0800 & Misaka_LTC6811_Device_Object[i].Cell_Select) != 0))
        {
            status ++;
            Misaka_LTC6811_Device_Object[i].OPENWires |= (0x01 << 12);
        }
    }

    return status;
}
/**
 * @brief
 * @return uint8_t @c
 */
static uint8_t Misaka_LTC6811_Balance_Group_Disable()
{
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].CFGR[4] = 0x00FF & 0x0000;
        Misaka_LTC6811_Device_Object[i].CFGR[5] &= 0xF0;
        Misaka_LTC6811_Device_Object[i].CFGR[5] |= ((0x0F00 & 0x0000) >> 8);
    }
    return Misaka_LTC6811_CMD_WRCFGA();
}
/**
 * @brief
 * @return uint8_t @c
 */
static uint8_t Misaka_LTC6811_Balance_Group_Odd()
{
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].CFGR[4] = 0x00FF & 0x0555;
        Misaka_LTC6811_Device_Object[i].CFGR[5] &= 0xF0;
        Misaka_LTC6811_Device_Object[i].CFGR[5] |= ((0x0F00 & 0x0555) >> 8);
    }
    return Misaka_LTC6811_CMD_WRCFGA();
}
/**
 * @brief
 * @return uint8_t @c
 */
static uint8_t Misaka_LTC6811_Balance_Group_Even()
{
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {

        Misaka_LTC6811_Device_Object[i].CFGR[4] = 0x00FF & 0x0AAA;
        Misaka_LTC6811_Device_Object[i].CFGR[5] &= 0xF0;
        Misaka_LTC6811_Device_Object[i].CFGR[5] |= ((0x0F00 & 0x0AAA) >> 8);
    }
    return Misaka_LTC6811_CMD_WRCFGA();
}
/**
 * @brief
 * @param  group            0:  关闭均衡
 *                          1:  奇数均衡
 *                          2:  偶数均衡
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Balance_Group(uint8_t group)
{
    uint8_t status = 0;
    if (group == 0)
    {
        status = Misaka_LTC6811_Balance_Group_Disable();
    }
    else if (group == 1)
    {
        status = Misaka_LTC6811_Balance_Group_Odd();
    }
    else if (group == 2)
    {
        status = Misaka_LTC6811_Balance_Group_Even();
    }
    return status;
}
/**
 * @brief
 * @param  balance_thresholddesc
 */
void Misaka_LTC6811_DCC_Flag(uint8_t balance_threshold)
{
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].DCC_Flag = 0x0000;    //清零
        for (uint8_t j = 0; j < 12; j++)
        {
            if ((Misaka_LTC6811_Device_Object[i].Cell_Select & (0x01 >> j)) != 0)
            {
                if (((Misaka_LTC6811_Device_Object[i].CellVolt[j] - Misaka_LTC6811_Device_Object[i].CellVolt_Min >= balance_threshold) ||
                        (Misaka_LTC6811_Device_Object[i].CellVolt_Max - Misaka_LTC6811_Device_Object[i].CellVolt[j] >= balance_threshold)))
                {
                    Misaka_LTC6811_Device_Object[i].DCC_Flag |= (0x01 >> j);
                }
            }

        }
    }
}
/**
 * @brief
 */
void Misaka_LTC6811_Max_Cell_Voltage()
{
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].CellVolt_Max = Misaka_LTC6811_Device_Object[i].CellVolt[0];
        for (uint8_t j = 0; j < 12; j++)
        {
            if ((Misaka_LTC6811_Device_Object[i].Cell_Select & (0x01 >> j)) != 0)
            {
                if (Misaka_LTC6811_Device_Object[i].CellVolt[j] > Misaka_LTC6811_Device_Object[i].CellVolt_Max)
                {
                    Misaka_LTC6811_Device_Object[i].CellVolt_Max = Misaka_LTC6811_Device_Object[i].CellVolt[j];
                }
            }
        }
    }
}
/**
 * @brief
 */
void Misaka_LTC6811_Min_Cell_Voltage()
{
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].CellVolt_Min = Misaka_LTC6811_Device_Object[i].CellVolt[0];
        for (uint8_t j = 0; j < 12; j++)
        {
            if ((Misaka_LTC6811_Device_Object[i].Cell_Select & (0x01 >> j)) != 0)
            {
                if (Misaka_LTC6811_Device_Object[i].CellVolt[j] < Misaka_LTC6811_Device_Object[i].CellVolt_Min)
                {
                    Misaka_LTC6811_Device_Object[i].CellVolt_Min = Misaka_LTC6811_Device_Object[i].CellVolt[j];
                }
            }
        }
    }
}
/**
 * @brief
 */
void Misaka_LTC6811_Max_Min_Cell_Voltage()
{
    Misaka_LTC6811_Max_Cell_Voltage();
    Misaka_LTC6811_Min_Cell_Voltage();
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        Misaka_LTC6811_Device_Object[i].CellVolt_DELTA =
            Misaka_LTC6811_Device_Object[i].CellVolt_Max - Misaka_LTC6811_Device_Object[i].CellVolt_Min;
    }
}
/**
 * @brief
 * @param  md               desc
 * @param  st               desc
 * @param  stc              desc
 * @return uint8_t @c
 */
uint8_t Misaka_LTC6811_Self_Test(uint16_t md, uint8_t st, uint16_t stc)
{
    uint8_t status = 0;
    status += Misaka_LTC6811_Cell_Voltage_Self_Test(md, st, stc);
    status += Misaka_LTC6811_Auxiliary_Voltage_Self_Test(md, st, stc);
    status += Misaka_LTC6811_Status_Self_Test(md, st, stc);
    return status;
}

void Misaka_LTC6811_Calculate_ALL_NTC_Resistance(void)
{
    for (uint8_t i = 0; i < LTC6811_DeviceNUM; i++)
    {
        for (uint8_t j = 0; j < 5; j++)
        {
            if ((Misaka_LTC6811_Device_Object[i].GPIO_Select & (0x01 >> j)) != 0)
            {
                Misaka_LTC6811_Device_Object[i].GPIO_NTCReg[j] =
                    (10000 * Misaka_LTC6811_Device_Object[i].GPIOVolt[j]) / (Misaka_LTC6811_Device_Object[i].REFVolt - Misaka_LTC6811_Device_Object[i].GPIOVolt[j]);
            }
        }
    }
}






