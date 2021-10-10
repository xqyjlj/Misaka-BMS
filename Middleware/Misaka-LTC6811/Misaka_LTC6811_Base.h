/**
 * @file Misaka_LTC6811_Base.h
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-07-21
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-07-21 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#ifndef __MISAKA_LTC6811_Base_H__
#define __MISAKA_LTC6811_Base_H__

#include "stdint.h"

#define LTC6811_CRC15_POLY 0x4599

#define LTC6811_DeviceNUM 1

#define LTC6811_WRCFGA      0x0001           //写配置寄存器组命令
#define LTC6811_WRCFGB      0x0024           //写配置寄存器组命令
#define LTC6811_RDCFGA      0x0002           //读配置寄存器组命令
#define LTC6811_RDCFGB      0x0026           //读配置寄存器组命令
#define LTC6811_RDCVA       0x0004            //读电池电压寄存器组A命令
#define LTC6811_RDCVB       0x0006            //读电池电压寄存器组B命令
#define LTC6811_RDCVC       0x0008            //读电池电压寄存器组C命令
#define LTC6811_RDCVD       0x000A            //读电池电压寄存器组D命令
#define LTC6811_RDCVE       0x0009            //读电池电压寄存器组E命令
#define LTC6811_RDCVF       0x000B            //读电池电压寄存器组F命令
#define LTC6811_RDAUXA      0x000C           //读辅助寄存器组A命令
#define LTC6811_RDAUXB      0x000E           //读辅助寄存器组B命令
#define LTC6811_RDAUXC      0x000D           //读辅助寄存器组C命令
#define LTC6811_RDAUXD      0x000F           //读辅助寄存器组D命令
#define LTC6811_RDSTATA     0x0010          //读状态寄存器组A命令
#define LTC6811_RDSTATB     0x0012          //读状态寄存器组B命令
#define LTC6811_WRSCTRL     0x0014          //写S控制寄存器组命令
#define LTC6811_WRPWM       0x0020                //写PWM寄存器组命令
#define LTC6811_WRPSB       0x001C                //写PWM/S控制寄存器组B命令
#define LTC6811_RDSCTRL     0x0016        //读S控制寄存器组命令
#define LTC6811_RDPWM       0x0022                //读PWM寄存器组命令
#define LTC6811_RDPSB       0x001E                //读PWM/S控制寄存器组B命令
#define LTC6811_STSCTRL     0x0019        //开始S引脚的脉冲控制，轮询状态
#define LTC6811_CLRSCTRL    0x0018     //清除S控住寄存器组命令
#define LTC6811_ADCV        0x0260             //启动电池电压ADC转换，轮询状态
#define LTC6811_ADOW        0x0228             //启动导线开路ADC转换，轮询状态
#define LTC6811_CVST        0x0207             //启动自测试电池电压转换，轮询状态
#define LTC6811_ADOL        0x0201             //启动CELL7电压重复测量命令
#define LTC6811_ADAX        0x0460             //启动GPIO ADC转换，轮询状态
#define LTC6811_ADAXD       0x0400                //启动带数字冗余的GPIO ADC转换，轮询状态
#define LTC6811_AXST        0x0407             //启动自测试GPIO转换，轮询状态
#define LTC6811_ADSTAT      0x0468           //启动状态组(SC总电压 ITMP芯片温度 VD数字电压 VA模拟电压)ADC转换，轮询状态
#define LTC6811_ADSTATD     0x0408        //启动带数字冗余的状态组(CellsV ITMP ASP DSP)ADC转换，轮询状态
#define LTC6811_STATST      0x040f           //启动状态组自测试转换，轮询状态
#define LTC6811_ADCVAX      0x046f           //启动组合电池电压以及GPIO1、GPIO2转换，轮询状态
#define LTC6811_ADCVSC      0x0467           //启动组合电池电压以及SC转换，轮询状态
#define LTC6811_CLRCELL     0x0711        //清除电池电压寄存器组命令
#define LTC6811_CLRAUX      0x0712           //清除辅助寄存器组命令
#define LTC6811_CLRSTAT     0x0713        //清除状态寄存器组命令
#define LTC6811_PLADC       0x0714                //轮询ADC转换状态命令
#define LTC6811_DIAGN       0x0715                //诊断MUX，轮询状态
#define LTC6811_WRCOMM      0x0721           //写COMM寄存器组命令
#define LTC6811_RDCOMM      0x0722           //读COMM寄存器组命令
#define LTC6811_STCOMM      0x0723           //启动I2C/SPI通信命令

//命令参数
#define LTC6811_GPIO00000   (0x00 << 3)
#define LTC6811_GPIO00001   (0x01 << 3)
#define LTC6811_GPIO00010   (0x02 << 3)
#define LTC6811_GPIO00011   (0x03 << 3)
#define LTC6811_GPIO00100   (0x04 << 3)
#define LTC6811_GPIO00101   (0x05 << 3)
#define LTC6811_GPIO00110   (0x06 << 3)
#define LTC6811_GPIO00111   (0x07 << 3)
#define LTC6811_GPIO01000   (0x08 << 3)
#define LTC6811_GPIO01001   (0x09 << 3)
#define LTC6811_GPIO01010   (0x0A << 3)
#define LTC6811_GPIO01011   (0x0B << 3)
#define LTC6811_GPIO01100   (0x0C << 3)
#define LTC6811_GPIO01101   (0x0D << 3)
#define LTC6811_GPIO01110   (0x0E << 3)
#define LTC6811_GPIO01111   (0x0F << 3)
#define LTC6811_GPIO10000   (0x10 << 3)
#define LTC6811_GPIO10001   (0x11 << 3)
#define LTC6811_GPIO10010   (0x12 << 3)
#define LTC6811_GPIO10011   (0x13 << 3)
#define LTC6811_GPIO10100   (0x14 << 3)
#define LTC6811_GPIO10101   (0x15 << 3)
#define LTC6811_GPIO10110   (0x16 << 3)
#define LTC6811_GPIO10111   (0x17 << 3)
#define LTC6811_GPIO11000   (0x18 << 3)
#define LTC6811_GPIO11001   (0x19 << 3)
#define LTC6811_GPIO11010   (0x1A << 3)
#define LTC6811_GPIO11011   (0x1B << 3)
#define LTC6811_GPIO11100   (0x1C << 3)
#define LTC6811_GPIO11101   (0x1D << 3)
#define LTC6811_GPIO11110   (0x1E << 3)
#define LTC6811_GPIO11111   (0x1F << 3)

#define LTC6811_REFON0      (0x00 << 2)
#define LTC6811_REFON1      (0x01 << 2)

#define LTC6811_DTEN0       (0x00 << 1)
#define LTC6811_DTEN1       (0x01 << 1)

#define LTC6811_ADCOPT0     (0x00 << 0)
#define LTC6811_ADCOPT1     (0x01 << 0)

#define LTC6811_MD00        0x0000             //转换速率参数：422Hz（ADCOPT：0）；1kHz （ADCOPT：1）
#define LTC6811_MD01        0x0080             //转换速率参数：27kHz（ADCOPT：0）；14kHz（ADCOPT：1）
#define LTC6811_MD10        0x0100             //转换速率参数：7kHz （ADCOPT：0）；3kHz （ADCOPT：1）
#define LTC6811_MD11        0x0180             //转换速率参数：26Hz （ADCOPT：0）；2kHz （ADCOPT：1）

#define LTC6811_DCP1        0x0010             //测量时放电允许参数
#define LTC6811_DCP0        0x0000             //测量时放电不允许参数

#define LTC6811_CH000       0x0000            //转换电池选择参数：所有电池
#define LTC6811_CH001       0x0001            //转换电池选择参数：电池1和7
#define LTC6811_CH010       0x0002            //转换电池选择参数：电池2和8
#define LTC6811_CH011       0x0003            //转换电池选择参数：电池3和9
#define LTC6811_CH100       0x0004            //转换电池选择参数：电池4和10
#define LTC6811_CH101       0x0005            //转换电池选择参数：电池5和11
#define LTC6811_CH110       0x0006            //转换电池选择参数：电池6和12

#define LTC6811_PUP1        0x0040             //导线开路转电流设定参数：上拉电流
#define LTC6811_PUP0        0x0000             //导线开路转电流设定参数：下拉电流

#define LTC6811_ST01        0x0020             //自测模式设定参数：自测模式1
#define LTC6811_ST10        0x0040             //自测模式设定参数：自测模式2

#define LTC6811_CHG000      0x0000           //GPIO转换脚选择参数：GPIO1-5，第二基准
#define LTC6811_CHG001      0x0001           //GPIO转换脚选择参数：GPIO1
#define LTC6811_CHG010      0x0002           //GPIO转换脚选择参数：GPIO2
#define LTC6811_CHG011      0x0003           //GPIO转换脚选择参数：GPIO3
#define LTC6811_CHG100      0x0004           //GPIO转换脚选择参数：GPIO4
#define LTC6811_CHG101      0x0005           //GPIO转换脚选择参数：GPIO5
#define LTC6811_CHG110      0x0006           //GPIO转换脚选择参数：第二基准

#define LTC6811_CHST000     0x0000          //状态组选择参数：SC，ITMP，VA，VD
#define LTC6811_CHST001     0x0001          //状态组选择参数：SC
#define LTC6811_CHST010     0x0002          //状态组选择参数：ITMP
#define LTC6811_CHST011     0x0003          //状态组选择参数：VA
#define LTC6811_CHST100     0x0004          //状态组选择参数：VD

#define LTC6811_DCTO_0s         0x00
#define LTC6811_DCTO_30s        0x10
#define LTC6811_DCTO_60s        0x20
#define LTC6811_DCTO_120s       0x30
#define LTC6811_DCTO_180s       0x40
#define LTC6811_DCTO_240s       0x50
#define LTC6811_DCTO_300s       0x60
#define LTC6811_DCTO_600s       0x70
#define LTC6811_DCTO_900s       0x80
#define LTC6811_DCTO_1200s      0x90
#define LTC6811_DCTO_1800s      0xA0
#define LTC6811_DCTO_2400s      0xB0
#define LTC6811_DCTO_3600s      0xC0
#define LTC6811_DCTO_4500s      0xD0
#define LTC6811_DCTO_5400s      0xE0
#define LTC6811_DCTO_7200s      0xF0

//Self_Test_Code
#define LTC6811_ST01_26Hz_STC   0x9555
#define LTC6811_ST01_2kHz_STC   0x9555
#define LTC6811_ST01_3kHz_STC   0x9555
#define LTC6811_ST01_7kHz_STC   0x9555
#define LTC6811_ST01_14kHz_STC  0x9553
#define LTC6811_ST01_27kHz_STC  0x9565
#define LTC6811_ST10_26Hz_STC   0x6AAA
#define LTC6811_ST10_2kHz_STC   0x6AAA
#define LTC6811_ST10_3kHz_STC   0x6AAA
#define LTC6811_ST10_7kHz_STC   0x6AAA
#define LTC6811_ST10_14kHz_STC  0x6AAC
#define LTC6811_ST10_27kHz_STC  0x6A9A

typedef union
{
    uint8_t DATA[4];
    struct
    {
        uint8_t CMD[2];
        uint8_t CMD_PEC[2];
    } STRU;
} Misaka_Cmd_Struct;

typedef struct
{
    uint8_t CFGR[8];
    uint8_t RDCFGR[6];
    uint16_t DCC_Flag;//放电标志位 bit0～bit11:    为1时表示相应的n+1串需要均衡
    uint8_t CVAR[6];
    uint8_t CVBR[6];
    uint8_t CVCR[6];
    uint8_t CVDR[6];
    uint8_t AVAR[6];
    uint8_t AVBR[6];
    uint8_t STAR[6];
    uint8_t STBR[6];
    uint16_t Cell_Select;//使用的电池 bit0～bit11: 为1时表示相应的n + 1串已被使用；
    uint16_t CellVolt[12];
    uint16_t CellVolt_Max;      //所有串数中的最大值
    uint16_t CellVolt_Min;      //所有串数中的最小值
    uint16_t CellVolt_DELTA;    //单体电压最大值和最小值差值
    uint16_t MAX_Cell_NUM;      //最高电压的串数
    uint16_t MIN_Cell_NUM;      //最低电压的串数
    uint16_t OPENWires;         //bit0～bit12共13位，为1表示相应的C(n)断线
    uint8_t  GPIO_Select;       //使用的GPIO bit0～bit4: 为1时表示相应的n + 1脚已被使用；
    uint16_t GPIOVolt[5];
    uint32_t GPIO_NTCReg[5];            //计算得NTC电阻值
    uint16_t GPIO_NTC_TEMP[5];      //通过GPIO接NTC测得温度值
    uint16_t LTC6811_NTC_Temp_MAX;
    uint16_t LTC6811_NTC_Temp_MIN;
    uint16_t LTC6811_NTC_Temp_DELTA;
    uint16_t LTC6811_NTC_Temp_MAX_NUM; //NTC位号
    uint16_t LTC6811_NTC_Temp_MIN_NUM;
    uint16_t REFVolt;
    uint16_t SOCVolt;
    uint16_t TotalVolt;
    uint16_t ITMPVolt;
    uint16_t ITM;   //内置芯片温度 放大100度
    uint16_t VAVolt;
    uint16_t VDVolt;
    uint8_t REV;  //设备版本号,多路选择器状态,热关机状态
    uint32_t CV_Flag;
    uint8_t MuxFail;
    uint8_t Thsd;//热停机标志 1:热停机已经发生  0:热停机未发生
} Misaka_LTC6811_Struct;

uint8_t Misaka_LTC6811_Transmit_Receive(uint8_t* tx_data, uint8_t* rx_data, uint16_t size);
void Misaka_LTC6811_Delay_Ms(uint16_t ms);

extern Misaka_LTC6811_Struct Misaka_LTC6811_Device_Object[LTC6811_DeviceNUM];

void Misaka_LTC6811_Init_PEC15_Table();
uint8_t Misaka_LTC6811_CMD_WakeIdle(void);
uint8_t Misaka_LTC6811_CMD_WRCFGA(void);
uint8_t Misaka_LTC6811_CMD_RDCFGA(void);
uint8_t Misaka_LTC6811_CMD_RDCVA(void);
uint8_t Misaka_LTC6811_CMD_RDCVB(void);
uint8_t Misaka_LTC6811_CMD_RDCVC(void);
uint8_t Misaka_LTC6811_CMD_RDCVD(void);
uint8_t Misaka_LTC6811_CMD_RDAUXA(void);
uint8_t Misaka_LTC6811_CMD_RDAUXB(void);
uint8_t Misaka_LTC6811_CMD_RDSTATA(void);
uint8_t Misaka_LTC6811_CMD_RDSTATB(void);
uint8_t Misaka_LTC6811_CMD_WRSCTRL(void);
uint8_t Misaka_LTC6811_CMD_WRPWM(void);
uint8_t Misaka_LTC6811_CMD_RDSCTRL(void);
uint8_t Misaka_LTC6811_CMD_RDPWM(void);
uint8_t Misaka_LTC6811_CMD_STSCTRL(void);
uint8_t Misaka_LTC6811_CMD_CLRSCTRL(void);
uint8_t Misaka_LTC6811_CMD_ADCV(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_ADOW(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_CVST(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_ADOL(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_ADAX(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_ADAXD(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_AXST(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_ADSTAT(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_ADSTATD(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_STATST(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_ADCVAX(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_ADCVSC(uint16_t cmd);
uint8_t Misaka_LTC6811_CMD_CLRCELL(void);
uint8_t Misaka_LTC6811_CMD_CLRAUX(void);
uint8_t Misaka_LTC6811_CMD_CLRSTAT(void);
uint8_t Misaka_LTC6811_CMD_PLADC(void);
uint8_t Misaka_LTC6811_CMD_DIAGN(void);
uint8_t Misaka_LTC6811_CMD_WRCOMM(void);
uint8_t Misaka_LTC6811_CMD_RDCOMM(void);
uint8_t Misaka_LTC6811_CMD_STCOMM(void);

#endif