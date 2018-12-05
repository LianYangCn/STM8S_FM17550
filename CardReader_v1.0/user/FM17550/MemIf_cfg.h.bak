/******************************************************
文件名：	MemIf_cfg.h

描述）

Data			  Vasion			author
2018/1/13		  V1.0			    liujian
*******************************************************/
#ifndef		MEMIF_CFG_H
#define		MEMIF_CFG_H
/*******************************************************
description?nclude the header file
*******************************************************/
#include "Include.h"
#include "stm8s.h"

/*******************************************************
description?acro definitions
*******************************************************/
/**********宏开关定乪*******/


/**********宏常量定乪*******/
/********************************************************/
#define EEPROM_START_ADDR       0x004000//片内EEPROM的起始地址：stm8s003f单片机0x004000,空间128Byte
/*EEPROM_START_ADDR地址存放eeprom数据有效性标志字节，每一bit位代表一个对象数据是否有效。
上电读EEPROM时，若检测到该字节某bit位 = 1，则与其对应的数据有效。对应关系如下*/
/*
存储器地址 = EEPROM_START_ADDR（0x004000）
	 _______________________
	|  |  |  |	|  |  |  |  |
	|__|__|__|__|__|__|__|__|
	bit7	 ~            bit0
bit0:表示卡片自动检测数据有效性标志位:1--有效；0--无效
bit1:表示密钥数据有效性标志位:1--有效；0--无效
bit2:表示波特率数据有效性标志位:1--有效；0--无效
bit3~bit7预留
*/
#define EE_AUTO_DECT_MASK      0x01//卡片自动侦测标志数据对应的有效性标志位掩码
#define EE_KEY_MASK      	   0x02//密钥数据对应的有效性标志位掩码
#define EE_BAUD_RATE_MASK      0x04//波特率数据对应的有效性标志位掩码
/********************************************************/

#define EE_OBJECT_NUM           3U

#define EE_AUTO_DECT_OFFSET     1U//卡片自动侦测标志地址相对于EE起始地址偏移量
#define EE_AUTO_DECT_LNG     	1U//卡片自动侦测标志数据段长度
#define EE_AUTO_DECT_ADDR       (EEPROM_START_ADDR +EE_AUTO_DECT_OFFSET)//卡片自动侦测标志数据段起始地址

#define EE_KEY_OFFSET     		(EE_AUTO_DECT_OFFSET + EE_AUTO_DECT_LNG)//密钥地址相对于EE起始地址偏移量
#define EE_KEY_LNG     			6U//密钥数据段长度
#define EE_KEY_ADDR       		(EEPROM_START_ADDR +EE_KEY_OFFSET)//密钥数据段起始地址

#define EE_BAUD_RATE_OFFSET     (EE_KEY_OFFSET + EE_KEY_LNG)//波特率地址相对于EE起始地址偏移量
#define EE_BAUD_RATE_LNG     	4U//波特率数据段长度
#define EE_BAUD_RATE_ADDR       (EEPROM_START_ADDR +EE_BAUD_RATE_OFFSET)//波特率数据段起始地址



/***********宏函敪*********/

/*******************************************************
description?truct definitions
*******************************************************/

/*******************************************************
description?ypedef definitions
*******************************************************/
/*****struct definitions*****/
typedef struct
{
	uint8  Space;/*访问的存储位置：片内或片外*/
	uint32 Addr;/*首地址*/
	uint8  Lng;/*分配的数据段长度*/
	uint8  Mask;/*对应的有效性标志位掩码*/
}EepromCfg_ConfStruct;

/******enum definitions******/
typedef enum 
{
	EepromCfg_AutoDectFlg = 0U,/*卡片自动侦测标志值*/
	EepromCfg_Key = 1U,/*密钥*/
	EepromCfg_UartBaudrate = 2/*波特率*/
}EepromCfg_StrgObject;

typedef enum 
{
	EepromCfg_IntEE = 0U,/*片内EE*/
	EepromCfg_ExtEE = 1U/*片外EE*/
}EepromCfg_EE_Index;
/******union definitions*****/




/*******************************************************
description?ariable External declaration
*******************************************************/
extern const EepromCfg_ConfStruct    CaEepromCfg_Conf[EE_OBJECT_NUM];


/*******************************************************
description?unction External declaration
*******************************************************/
extern uint8  MemIfCfg_WriteEE(uint32 Le_u_Addr,uint8* Le_u_Data,uint8 Le_u_Lng);
extern uint8  MemIfCfg_ReadEE(uint32 Le_u_Addr,uint8* Le_u_Data,uint8 Le_u_Lng);
extern void  MemIfCfg_FLASH_Unlock(void);
extern void  MemIfCfg_FLASH_Lock(void);
extern void  MemIfCfg_FLASH_ProgramByte(uint32 Address, uint8 Data);
extern uint8 MemIfCfg_FLASH_ReadByte(uint32 Le_u_Addr);
#endif
