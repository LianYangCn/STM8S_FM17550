/******************************************************
�ļ�����	MemIf.c

������		
Data			Vasion			author
2018/1/13		V1.0			liujian
*******************************************************/

/*******************************************************
description�� include the header file
*******************************************************/
#include "MemIf.h"


/*******************************************************
description�� global variable definitions
*******************************************************/


/*******************************************************
description�� static variable definitions
*******************************************************/

/*******************************************************
description�� function declaration
*******************************************************/
/*Global function declaration*/

/*Static function declaration*/


/******************************************************
description�� function code
******************************************************/
/******************************************************
*��������MemIf_Init

*��  �Σ�void

*����ֵ��void

*��  ������ʼ��

*��  ע��
******************************************************/
void MemIf_Init(void)
{

}


/******************************************************
*��������MemIf_WriteEE

*��  �Σ�

*����ֵ��

*��  ����дeeprom

*��  ע��
******************************************************/
uint8 MemIf_WriteEE(uint8 Le_u_Object,uint8* Le_u_Data,uint8 Le_u_Lng)
{
	uint8 Le_u_ok = 0U;
	uint8 Le_u_i = 0U;
	uint8 Le_u_ValidFlag = 0U;
	
	switch(CaEepromCfg_Conf[Le_u_Object].Space)
	{
		case EepromCfg_IntEE:/*дƬ��eeprom*/
		{
			MemIfCfg_FLASH_Unlock();/*eeprom��������*/
			Le_u_ValidFlag = MemIfCfg_FLASH_ReadByte(EEPROM_START_ADDR);/*��ȡ������Ч�Ա�־�ֽ�*/
			Le_u_ValidFlag &= (~CaEepromCfg_Conf[Le_u_Object].Mask);
			MemIfCfg_FLASH_ProgramByte(EEPROM_START_ADDR,Le_u_ValidFlag);/*��������Ч�Ա�־λ*/
			if(CaEepromCfg_Conf[Le_u_Object].Lng == Le_u_Lng)
			{
				for(Le_u_i=0; Le_u_i < Le_u_Lng; Le_u_i++)//������д��EEPROM��
				{
					MemIfCfg_FLASH_ProgramByte((CaEepromCfg_Conf[Le_u_Object].Addr + Le_u_i), Le_u_Data[Le_u_i]);			
				}
				Le_u_ValidFlag |= CaEepromCfg_Conf[Le_u_Object].Mask;
				MemIfCfg_FLASH_ProgramByte(EEPROM_START_ADDR,Le_u_ValidFlag);/*��λ������Ч�Ա�־λ*/
				Le_u_ok = 1U;
			}
			MemIfCfg_FLASH_Lock();/*eeprom��������*/
		}
		break;
		case EepromCfg_ExtEE:/*дƬ��eeprom*/
		
		break;
		default:
		break;
	}
	
	return  Le_u_ok;	
}


/******************************************************
*��������MemIf_ReadEE

*��  �Σ�

*����ֵ��

*��  ������eeprom

*��  ע��
******************************************************/
uint8 MemIf_ReadEE(uint8 Le_u_Object,uint8* Le_u_Data,uint8 Le_u_Lng)
{
	uint8 Le_u_ok = 0U;
	uint8 Le_u_i = 0U;
	uint8 Le_u_ValidFlag = 0U;
	
	switch(CaEepromCfg_Conf[Le_u_Object].Space)
	{
		case EepromCfg_IntEE:/*��Ƭ��eeprom*/
		{
			MemIfCfg_FLASH_Unlock();/*eeprom��������*/
			Le_u_ValidFlag = MemIfCfg_FLASH_ReadByte(EEPROM_START_ADDR);/*��ȡ������Ч�Ա�־�ֽ�*/
			if((CaEepromCfg_Conf[Le_u_Object].Lng == Le_u_Lng) && (CaEepromCfg_Conf[Le_u_Object].Mask & Le_u_ValidFlag))
			{
				for(Le_u_i=0; Le_u_i < Le_u_Lng; Le_u_i++)
				{
					Le_u_Data[Le_u_i] = MemIfCfg_FLASH_ReadByte(CaEepromCfg_Conf[Le_u_Object].Addr + Le_u_i);			
				}
				Le_u_ok = 1U;
			}
			MemIfCfg_FLASH_Lock();/*eeprom��������*/
		}
		break;
		case EepromCfg_ExtEE:/*��Ƭ��eeprom*/
		
		break;
		default:
		break;
	}
	return Le_u_ok;
}
