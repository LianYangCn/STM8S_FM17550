/******************************************************
文件名：	MemIf_cfg.c

描述：		
Data			Vasion			author
2018/1/13		V1.0			liujian
*******************************************************/

/*******************************************************
description： include the header file
*******************************************************/
#include "MemIf_cfg.h"


/*******************************************************
description： global variable definitions
*******************************************************/
const EepromCfg_ConfStruct    CaEepromCfg_Conf[EE_OBJECT_NUM] = 
{
	
	{EepromCfg_IntEE,EE_AUTO_DECT_ADDR,EE_AUTO_DECT_LNG,EE_AUTO_DECT_MASK},//卡片自动侦测
	{EepromCfg_IntEE,EE_KEY_ADDR,EE_KEY_LNG,EE_KEY_MASK},//密钥
	{EepromCfg_IntEE,EE_BAUD_RATE_ADDR,EE_BAUD_RATE_LNG,EE_BAUD_RATE_MASK}//串口波特率
};

/*******************************************************
description： static variable definitions
*******************************************************/


/*******************************************************
description： function declaration
*******************************************************/
/*Global function declaration*/


/*Static function declaration*/



/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：eeprom解锁
 
*备  注：
******************************************************/
void MemIfCfg_FLASH_Unlock(void)
{
	FLASH_Unlock(FLASH_MEMTYPE_DATA); //EEPROM解除保护
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：eeprom加锁保护
 
*备  注：
******************************************************/
void MemIfCfg_FLASH_Lock(void)
{
	FLASH_Lock(FLASH_MEMTYPE_DATA);//EEPROM加上保护
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：写eeprom
 
*备  注：
******************************************************/
void MemIfCfg_FLASH_ProgramByte(uint32 Address, uint8 Data)
{
	FLASH_ProgramByte(Address,Data);
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：读eeprom
 
*备  注：
******************************************************/
uint8 MemIfCfg_FLASH_ReadByte(uint32 Le_u_Addr)
{
	return (FLASH_ReadByte(Le_u_Addr));
}


