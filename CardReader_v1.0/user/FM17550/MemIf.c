/******************************************************
文件名：	MemIf.c

描述：		
Data			Vasion			author
2018/1/13		V1.0			liujian
*******************************************************/

/*******************************************************
description： include the header file
*******************************************************/
#include "MemIf.h"


/*******************************************************
description： global variable definitions
*******************************************************/


/*******************************************************
description： static variable definitions
*******************************************************/

/*******************************************************
description： function declaration
*******************************************************/
/*Global function declaration*/

/*Static function declaration*/


/******************************************************
description： function code
******************************************************/
/******************************************************
*函数名：MemIf_Init

*形  参：void

*返回值：void

*描  述：初始化

*备  注：
******************************************************/
void MemIf_Init(void)
{

}


/******************************************************
*函数名：MemIf_WriteEE

*形  参：

*返回值：

*描  述：写eeprom

*备  注：
******************************************************/
uint8 MemIf_WriteEE(uint8 Le_u_Object,uint8* Le_u_Data,uint8 Le_u_Lng)
{
	uint8 Le_u_ok = 0U;
	uint8 Le_u_i = 0U;
	uint8 Le_u_ValidFlag = 0U;
	
	switch(CaEepromCfg_Conf[Le_u_Object].Space)
	{
		case EepromCfg_IntEE:/*写片上eeprom*/
		{
			MemIfCfg_FLASH_Unlock();/*eeprom解锁保护*/
			Le_u_ValidFlag = MemIfCfg_FLASH_ReadByte(EEPROM_START_ADDR);/*读取数据有效性标志字节*/
			Le_u_ValidFlag &= (~CaEepromCfg_Conf[Le_u_Object].Mask);
			MemIfCfg_FLASH_ProgramByte(EEPROM_START_ADDR,Le_u_ValidFlag);/*清数据有效性标志位*/
			if(CaEepromCfg_Conf[Le_u_Object].Lng == Le_u_Lng)
			{
				for(Le_u_i=0; Le_u_i < Le_u_Lng; Le_u_i++)//将数据写入EEPROM中
				{
					MemIfCfg_FLASH_ProgramByte((CaEepromCfg_Conf[Le_u_Object].Addr + Le_u_i), Le_u_Data[Le_u_i]);			
				}
				Le_u_ValidFlag |= CaEepromCfg_Conf[Le_u_Object].Mask;
				MemIfCfg_FLASH_ProgramByte(EEPROM_START_ADDR,Le_u_ValidFlag);/*置位数据有效性标志位*/
				Le_u_ok = 1U;
			}
			MemIfCfg_FLASH_Lock();/*eeprom加锁保护*/
		}
		break;
		case EepromCfg_ExtEE:/*写片外eeprom*/
		
		break;
		default:
		break;
	}
	
	return  Le_u_ok;	
}


/******************************************************
*函数名：MemIf_ReadEE

*形  参：

*返回值：

*描  述：读eeprom

*备  注：
******************************************************/
uint8 MemIf_ReadEE(uint8 Le_u_Object,uint8* Le_u_Data,uint8 Le_u_Lng)
{
	uint8 Le_u_ok = 0U;
	uint8 Le_u_i = 0U;
	uint8 Le_u_ValidFlag = 0U;
	
	switch(CaEepromCfg_Conf[Le_u_Object].Space)
	{
		case EepromCfg_IntEE:/*读片上eeprom*/
		{
			MemIfCfg_FLASH_Unlock();/*eeprom解锁保护*/
			Le_u_ValidFlag = MemIfCfg_FLASH_ReadByte(EEPROM_START_ADDR);/*读取数据有效性标志字节*/
			if((CaEepromCfg_Conf[Le_u_Object].Lng == Le_u_Lng) && (CaEepromCfg_Conf[Le_u_Object].Mask & Le_u_ValidFlag))
			{
				for(Le_u_i=0; Le_u_i < Le_u_Lng; Le_u_i++)
				{
					Le_u_Data[Le_u_i] = MemIfCfg_FLASH_ReadByte(CaEepromCfg_Conf[Le_u_Object].Addr + Le_u_i);			
				}
				Le_u_ok = 1U;
			}
			MemIfCfg_FLASH_Lock();/*eeprom加锁保护*/
		}
		break;
		case EepromCfg_ExtEE:/*读片外eeprom*/
		
		break;
		default:
		break;
	}
	return Le_u_ok;
}
