/******************************************************
�ļ�����	MemIf_cfg.c

������		
Data			Vasion			author
2018/1/13		V1.0			liujian
*******************************************************/

/*******************************************************
description�� include the header file
*******************************************************/
#include "MemIf_cfg.h"


/*******************************************************
description�� global variable definitions
*******************************************************/
const EepromCfg_ConfStruct    CaEepromCfg_Conf[EE_OBJECT_NUM] = 
{
	
	{EepromCfg_IntEE,EE_AUTO_DECT_ADDR,EE_AUTO_DECT_LNG,EE_AUTO_DECT_MASK},//��Ƭ�Զ����
	{EepromCfg_IntEE,EE_KEY_ADDR,EE_KEY_LNG,EE_KEY_MASK},//��Կ
	{EepromCfg_IntEE,EE_BAUD_RATE_ADDR,EE_BAUD_RATE_LNG,EE_BAUD_RATE_MASK}//���ڲ�����
};

/*******************************************************
description�� static variable definitions
*******************************************************/


/*******************************************************
description�� function declaration
*******************************************************/
/*Global function declaration*/


/*Static function declaration*/



/******************************************************
*��������
 
*��  �Σ�
 
*����ֵ��void
 
*��  ����eeprom����
 
*��  ע��
******************************************************/
void MemIfCfg_FLASH_Unlock(void)
{
	FLASH_Unlock(FLASH_MEMTYPE_DATA); //EEPROM�������
}

/******************************************************
*��������
 
*��  �Σ�
 
*����ֵ��void
 
*��  ����eeprom��������
 
*��  ע��
******************************************************/
void MemIfCfg_FLASH_Lock(void)
{
	FLASH_Lock(FLASH_MEMTYPE_DATA);//EEPROM���ϱ���
}

/******************************************************
*��������
 
*��  �Σ�
 
*����ֵ��void
 
*��  ����дeeprom
 
*��  ע��
******************************************************/
void MemIfCfg_FLASH_ProgramByte(uint32 Address, uint8 Data)
{
	FLASH_ProgramByte(Address,Data);
}

/******************************************************
*��������
 
*��  �Σ�
 
*����ֵ��void
 
*��  ������eeprom
 
*��  ע��
******************************************************/
uint8 MemIfCfg_FLASH_ReadByte(uint32 Le_u_Addr)
{
	return (FLASH_ReadByte(Le_u_Addr));
}


