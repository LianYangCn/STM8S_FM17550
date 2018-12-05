/******************************************************
�ļ�����	MemIf_cfg.h

������

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
/**********�꿪�ض��e*******/


/**********�곣�����e*******/
/********************************************************/
#define EEPROM_START_ADDR       0x004000//Ƭ��EEPROM����ʼ��ַ��stm8s003f��Ƭ��0x004000,�ռ�128Byte
/*EEPROM_START_ADDR��ַ���eeprom������Ч�Ա�־�ֽڣ�ÿһbitλ����һ�����������Ƿ���Ч��
�ϵ��EEPROMʱ������⵽���ֽ�ĳbitλ = 1���������Ӧ��������Ч����Ӧ��ϵ����*/
/*
�洢����ַ = EEPROM_START_ADDR��0x004000��
	 _______________________
	|  |  |  |	|  |  |  |  |
	|__|__|__|__|__|__|__|__|
	bit7	 ~            bit0
bit0:��ʾ��Ƭ�Զ����������Ч�Ա�־λ:1--��Ч��0--��Ч
bit1:��ʾ��Կ������Ч�Ա�־λ:1--��Ч��0--��Ч
bit2:��ʾ������������Ч�Ա�־λ:1--��Ч��0--��Ч
bit3~bit7Ԥ��
*/
#define EE_AUTO_DECT_MASK      0x01//��Ƭ�Զ�����־���ݶ�Ӧ����Ч�Ա�־λ����
#define EE_KEY_MASK      	   0x02//��Կ���ݶ�Ӧ����Ч�Ա�־λ����
#define EE_BAUD_RATE_MASK      0x04//���������ݶ�Ӧ����Ч�Ա�־λ����
/********************************************************/

#define EE_OBJECT_NUM           3U

#define EE_AUTO_DECT_OFFSET     1U//��Ƭ�Զ�����־��ַ�����EE��ʼ��ַƫ����
#define EE_AUTO_DECT_LNG     	1U//��Ƭ�Զ�����־���ݶγ���
#define EE_AUTO_DECT_ADDR       (EEPROM_START_ADDR +EE_AUTO_DECT_OFFSET)//��Ƭ�Զ�����־���ݶ���ʼ��ַ

#define EE_KEY_OFFSET     		(EE_AUTO_DECT_OFFSET + EE_AUTO_DECT_LNG)//��Կ��ַ�����EE��ʼ��ַƫ����
#define EE_KEY_LNG     			6U//��Կ���ݶγ���
#define EE_KEY_ADDR       		(EEPROM_START_ADDR +EE_KEY_OFFSET)//��Կ���ݶ���ʼ��ַ

#define EE_BAUD_RATE_OFFSET     (EE_KEY_OFFSET + EE_KEY_LNG)//�����ʵ�ַ�����EE��ʼ��ַƫ����
#define EE_BAUD_RATE_LNG     	4U//���������ݶγ���
#define EE_BAUD_RATE_ADDR       (EEPROM_START_ADDR +EE_BAUD_RATE_OFFSET)//���������ݶ���ʼ��ַ



/***********�꺯��*********/

/*******************************************************
description?truct definitions
*******************************************************/

/*******************************************************
description?ypedef definitions
*******************************************************/
/*****struct definitions*****/
typedef struct
{
	uint8  Space;/*���ʵĴ洢λ�ã�Ƭ�ڻ�Ƭ��*/
	uint32 Addr;/*�׵�ַ*/
	uint8  Lng;/*��������ݶγ���*/
	uint8  Mask;/*��Ӧ����Ч�Ա�־λ����*/
}EepromCfg_ConfStruct;

/******enum definitions******/
typedef enum 
{
	EepromCfg_AutoDectFlg = 0U,/*��Ƭ�Զ�����־ֵ*/
	EepromCfg_Key = 1U,/*��Կ*/
	EepromCfg_UartBaudrate = 2/*������*/
}EepromCfg_StrgObject;

typedef enum 
{
	EepromCfg_IntEE = 0U,/*Ƭ��EE*/
	EepromCfg_ExtEE = 1U/*Ƭ��EE*/
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
