/******************************************************
文件名：	CardRd.c

描述：		
Data			Vasion			author
2018/1/5		V1.0			liujian
*******************************************************/

/*******************************************************
description： include the header file
*******************************************************/
#include "CardRd.h"


/*******************************************************
description： global variable definitions
*******************************************************/


/*******************************************************
description： static variable definitions
*******************************************************/

#if(1 == CARD_RD_TEST)	
static uint8_t   CardRd_u_TEST;
#endif	

unsigned char  SaCardRd_u_PDfultKey[6] = {0};
//static unsigned char  SaCardRd_u_Sec6DfultKey[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
//static unsigned char  SaCardRd_u_DfultData[16] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16};; 
/*******************************************************
description： function declaration
*******************************************************/
/*Global function declaration*/

/*Static function declaration*/


/******************************************************
description： function code
******************************************************/
/******************************************************
*函数名：CardRd_Init

*形  参：void

*返回值：void

*描  述：初始化

*备  注：
******************************************************/
void CardRd_Init(void)
{
	
}

/******************************************************
*函数名：CardRd_MainFunction

*形  参：void

*返回值：void

*描  述：主任务

*备  注：
******************************************************/
void CardRd_MainFunction(void)
{

}


/******************************************************
*函数名：GetCardRd_u_BlockData

*形  参：void

*返回值：void

*描  述：读块数据

*备  注：
******************************************************/
uint8 GetCardRd_u_BlockData(uint8 LeCardRd_u_Block,uint8* LaCardRd_u_Data)
{
	uint8 	LeCardRd_u_Ok = COMM_ERR;  
	uint8 	LeCardRd_u_statues;
	uint8	LaCardRd_u_picc_atqa[2U];
	uint8	LaCardRd_u_picc_sak[3U];
	uint8   LaCardRd_u_picc_uid[15];
	uint8	LeCardRd_u_uidLng;
	uint8 	Le_u_i  = 10U;
	Pcd_ConfigISOType(0);/*切换到ISO/IEC 14443A卡*/
	Set_Rf(3);   //turn on radio
	while(Le_u_i--)
	{
		LeCardRd_u_statues = CardRd_TypeA_CardActive(LaCardRd_u_picc_atqa,LaCardRd_u_picc_uid,&LeCardRd_u_uidLng,LaCardRd_u_picc_sak);
		if(TRUE == LeCardRd_u_statues)
		{
			//使用密码验证
			LeCardRd_u_statues = CardRd_Mifare_Auth(0x00,LeCardRd_u_Block,SaCardRd_u_PDfultKey,LaCardRd_u_picc_uid,LeCardRd_u_uidLng);	//card authentication	
			if(TRUE == LeCardRd_u_statues)
			{//使用密码验证ok
				LeCardRd_u_statues = CardRd_Mifare_Blockread(LeCardRd_u_Block,LaCardRd_u_Data);	//bolck read function(读块的数据)
				if(TRUE == LeCardRd_u_statues)
				{					
					LeCardRd_u_Ok = COMM_OK;
					break;
				}
				else
				{//读失败
					LeCardRd_u_Ok = READ_ERR;	
				}
			}
			else
			{//使用密码验证失败
				LeCardRd_u_Ok = KEY_ERR;
			}
		}
	}
	Set_Rf(0);
	return LeCardRd_u_Ok;
}


/******************************************************
*函数名：WrCardRd_MiCard
 
*形  参：void
 
*返回值：void
 
*描  述：Mifare 写块数据
 
*备  注：
******************************************************/
uint8_t WrCardRd_MiCard_TyteA(uint8_t Block,uint8_t *Data)
{
	uint8 	LeCardRd_u_Ok = COMM_ERR;  
	uint8 	LeCardRd_u_statues;
	uint8	LaCardRd_u_picc_atqa[2U];
	uint8	LaCardRd_u_picc_sak[3U];
	uint8   LaCardRd_u_picc_uid[15];
    uint8	LeCardRd_u_uidLng;
	uint8  	Le_u_i  = 5U;
	Pcd_ConfigISOType(0);/*切换到ISO/IEC 14443A卡*/
	Set_Rf(3);   //turn on radio
	while(Le_u_i--)
	{
		LeCardRd_u_statues = CardRd_TypeA_CardActive(LaCardRd_u_picc_atqa,LaCardRd_u_picc_uid,&LeCardRd_u_uidLng,LaCardRd_u_picc_sak);
		if(TRUE == LeCardRd_u_statues)
		{
			//使用keyA密码验证
			LeCardRd_u_statues = CardRd_Mifare_Auth(0x00,Block,SaCardRd_u_PDfultKey,LaCardRd_u_picc_uid,LeCardRd_u_uidLng);	//card authentication
			if(TRUE == LeCardRd_u_statues)
			{//密码验证ok
				LeCardRd_u_statues = CardRd_Mifare_Blockwrite(Block,Data);	//bolck write function(写块的数据)
				if(TRUE == LeCardRd_u_statues)
				{		
					LeCardRd_u_Ok = COMM_OK;
					break;
				}
				else
				{//写失败
					LeCardRd_u_Ok = WRITE_ERR;
				}
			}
			else
			{//密码验证失败
				LeCardRd_u_Ok = KEY_ERR;
			}
		}
	}
	Set_Rf(0); 
	return LeCardRd_u_Ok;
}



/******************************************************
*函数名：CardRd_RdCard_TyteA

*形  参：void

*返回值：

*描  述：读取A卡Uid,激活卡（寻卡，防冲突，选卡）

*备  注：
******************************************************/
uint8_t RdCardRd_u_MiCard_TyteA(uint8_t ReqCode, uint8_t  *TagType, uint8_t  *Sak,uint8_t  *SnrLen, uint8_t  *Snr)
{
	unsigned char LeCardRd_u_ok = 0U;
	unsigned char LeCardRd_u_statuesA;
	uint8  Le_u_i  = 5U;
	Pcd_ConfigISOType(0);/*切换到ISO/IEC 14443A卡*/
	Set_Rf(3);   //turn on radio
	while(Le_u_i--)
	{
		LeCardRd_u_statuesA = CardRd_TypeA_CardActive(TagType,Snr,SnrLen,Sak);
		if(TRUE == LeCardRd_u_statuesA)
		{			
			LeCardRd_u_ok = 1U;
			break;
		}
	}
	Set_Rf(0);   /* 关闭天线  */ 
	return LeCardRd_u_ok;
}


/******************************************************
*函数名：RdCardRd_u_Card_TyteB

*形  参：void

*返回值：void

*描  述：读取B卡Uid

*备  注：
******************************************************/
uint8_t  RdCardRd_u_Card_TyteB(uint8_t* Le_u_Data,uint8_t* Le_u_Lng)
{
	unsigned int   LeCardRd_ui_RxBitLen;               //卡片返回数据bit长度
	unsigned char  LeCardRd_u_ok = 0U;
	unsigned char  LeCardRd_u_statuesB;
	unsigned char  LaCardRd_u_PUPI[4];
	unsigned char  LeCardRd_u_i = 3U;
	LeCardRd_ui_RxBitLen = 0;	
	//FM175X_SoftReset();	

	Pcd_ConfigISOType(1);             //设置TypeB
#if(1 == CARD_RD_TEST)	
	CardRd_u_TEST = spi_GetReg(ControlReg);
	CardRd_u_TEST = spi_GetReg(TxModeReg);
	CardRd_u_TEST = spi_GetReg(RxModeReg);
	CardRd_u_TEST = spi_GetReg(TxAutoReg);
	CardRd_u_TEST = spi_GetReg(RxThresholdReg);
	CardRd_u_TEST = spi_GetReg(RFCfgReg);
	CardRd_u_TEST = spi_GetReg(TxBitPhaseReg);
	CardRd_u_TEST = spi_GetReg(GsNReg);
	CardRd_u_TEST = spi_GetReg(CWGsPReg);
	CardRd_u_TEST = spi_GetReg(GsNOffReg);
	CardRd_u_TEST = spi_GetReg(ModGsPReg);	
#endif	
	Set_Rf(3);   //turn on radio
#if(1 == CARD_RD_TEST)	
	CardRd_u_TEST = spi_GetReg(TxControlReg);	
#endif
	while(LeCardRd_u_i--)
	{
		LeCardRd_u_statuesB=CardRd_TypeB_WUP(&LeCardRd_ui_RxBitLen,Le_u_Data,LaCardRd_u_PUPI);//寻卡 Standard	 send request command Standard mode
		if(LeCardRd_u_statuesB == TRUE)
		{
			LeCardRd_u_statuesB = CardRd_TypeB_Select(LaCardRd_u_PUPI,&LeCardRd_ui_RxBitLen,Le_u_Data);
			if(LeCardRd_u_statuesB == TRUE)
			{
				LeCardRd_u_statuesB = CardRd_TypeB_GetUID(&LeCardRd_ui_RxBitLen,Le_u_Data);
				if(LeCardRd_u_statuesB == TRUE)
				{				
					*Le_u_Lng = (unsigned char)(LeCardRd_ui_RxBitLen/8);
					LeCardRd_u_ok =  1U;
					break;
				}
			}
		}		
	}
	Set_Rf( 0 );   /* 关闭天线 */  
	return LeCardRd_u_ok;
}

