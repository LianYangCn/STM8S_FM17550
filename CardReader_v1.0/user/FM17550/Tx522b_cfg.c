/******************************************************
文件名：	Tx522b_cfg.c

描述：	全双工串口通信	TX522B	
Data			Vasion			author
2018/1/10		V1.0			liujian
*******************************************************/

/*******************************************************
description： include the header file
*******************************************************/
#include "Tx522b_cfg.h"

/*******************************************************
description： function declaration
*******************************************************/
/*Global function declaration*/

/*Static function declaration*/


/*******************************************************
description： global variable definitions
*******************************************************/

/*******************************************************
description： static variable definitions
*******************************************************/



/******************************************************
description： function code
******************************************************/
/******************************************************
*函数名：GetTx522bCfg_u_RxMsgRenew

*形  参：void

*返回值：

*描  述：获取串口数据更新状态

*备  注：
******************************************************/
uint8 GetTx522bCfg_u_RxMsgRenew(void)
{
	return (GetUartCmn_u_RxMsgRenew());
}

/******************************************************
*函数名：GetTx522bCfg_u_RxMsg

*形  参：

*返回值：void

*描  述：获取串口数据

*备  注：
******************************************************/
void  GetTx522bCfg_u_RxMsg(uint8* Le_u_RxData)
{
	GetUartCmn_u_RxMsg(Le_u_RxData);
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：
 
*描  述：写eeprom
 
*备  注：
******************************************************/
uint8  Tx522bCfg_WriteEE(uint8 Object,uint8* Le_u_Data,uint8 Le_u_Lng)
{
	return(MemIf_WriteEE(Object,Le_u_Data,Le_u_Lng));
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：
 
*描  述：读eeprom
 
*备  注：
******************************************************/
uint8  Tx522bCfg_ReadEE(uint8 Object,uint8* Le_u_Data,uint8 Le_u_Lng)
{
	return(MemIf_ReadEE(Object,Le_u_Data,Le_u_Lng));
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：设置串口发送数据
 
*备  注：
******************************************************/
void  SetTx522bCfg_TxMsg(uint8* Le_u_TxData,uint8 Le_u_Lng)
{
	SetUartCmn_TxMsg(Le_u_TxData,Le_u_Lng);
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：获取块数据
 
*备  注：
******************************************************/
uint8 GetTx522bCfg_u_BlockData(uint8 Le_u_Block,uint8 *Le_u_Data)
{
	return (GetCardRd_u_BlockData(Le_u_Block,Le_u_Data));
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：获取块数据
 
*备  注：
******************************************************/
uint8 Tx522bCfg_DetectCard(uint8 Le_u_ReqCode)
{
  return  1;
}


/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：获取A卡片Uid
 
*备  注：
******************************************************/
uint8 GetTx522bCfg_u_ACardSnr(uint8 ReqCode, uint8  *TagType, uint8  *Sak,uint8  *SnrLen, uint8  *Snr)
{
	return (RdCardRd_u_MiCard_TyteA(ReqCode,TagType,Sak,SnrLen,Snr));
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：void
 
*描  述：获取B卡片Uid
 
*备  注：
******************************************************/
uint8 GetTx522bCfg_u_BCardSnr( uint8  *Snr,uint8 *SnrLen)
{
	return (RdCardRd_u_Card_TyteB(Snr,SnrLen));
}


/******************************************************
*函数名：
 
*形  参：
 
*返回值：
 
*描  述：写块
 
*备  注：
******************************************************/
uint8 Tx522bCfg_u_WriteBlock(uint8 Block,uint8 *Data)
{
	return (WrCardRd_MiCard_TyteA(Block,Data));
}

/******************************************************
*函数名：
 
*形  参：
 
*返回值：
 
*描  述：写块
 
*备  注：
******************************************************/
void SetTx522bCfg_BaudRtae(uint32 BaudRate)
{
	Mcu_Init_SetBaudRtae(BaudRate);
}

/******************************************************
*函数名：
*形  参：
 
*返回值：
 
*描  述：获取发送空闲状态
 
*备  注：
******************************************************/
uint8 GetTx522bCfg_u_TxIdle(void)
{
	return(GetUartCmn_u_TxIdle());
}
