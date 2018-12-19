/******************************************************
文件名：	TX522B.c

描述：	全双工串口通信	TX522B	
Data			Vasion			author
2018/1/10		V1.0			liujian
*******************************************************/

/*******************************************************
description： include the header file
*******************************************************/
#include "Tx522b.h"

/*******************************************************
description： global variable definitions
*******************************************************/

/*******************************************************
description： static variable definitions
*******************************************************/
static Tx522b_RxMsg RxMsg;/*存放指令数据的buff*/
static uint8 		SeTx522b_u_AutoDtctFlag;/*自动侦测卡片标志*/
//static uint8 		SeTx522b_u_FirstDtctFlag;/*自动侦测卡片模式下首次侦测到卡片标志*/
//static uint8        SeTx522b_u_UnDtctCnt;/*未检测到卡片计数器*/

static Tx522b_TxMsg  TxMsg[TXBUFF_NUM];
static unsigned char TxMsgHeader;/*发送数据缓冲区头指示*/
static unsigned char TxMsgRear;/* 发送数据缓冲区尾指示*/
static uint32  SeTx522b_dw_DelayTimer;
static uint32  SeTx522b_dw_RcovrAutoDtctT;
//static unsigned int  SeTx522b_w_Timer;/* 发送数据缓冲区尾指示*/
//static unsigned char SeTx522b_u_CardOnLineFlg;/* 发送数据缓冲区尾指示*/
static uint8 	SeTx522b_u_AutoDtcTaskFlag;/*自动侦测卡片任务标志*/

/*******************************************************
description： function declaration
*******************************************************/
/*Global function declaration*/

/*Static function declaration*/

static void  Tx522b_CmdDeal(void);
static uint8 CalTx522b_u_XOR(uint8* LeTx522b_u_Data,uint8 LeTx522b_u_Lng);
static void  Tx522b_AutoDetectCard(void);
static void  SendTx522b_CardId(uint8 CardType,uint8  *TagType, uint8  *Sak,uint8 SnrLen,uint8 *Snr);
static uint8 Tx522b_DataSaveToBuff(uint8* LeTx522b_u_Data,uint8 LeTx522b_u_Lng);
/******************************************************
description： function code
******************************************************/
/******************************************************
*函数名：InitUartCmn_parameter

*形  参：void

*返回值：void

*描  述：初始化

*备  注：
******************************************************/
void InitTx522b_parameter(void)
{
	uint8 Le_u_i;
	
	SeTx522b_dw_RcovrAutoDtctT =0U;
	SeTx522b_dw_DelayTimer = 0U;
	SeTx522b_u_AutoDtctFlag = 1U;/*未读到有效值，给默认值--开启自动寻卡*/
	SeTx522b_u_AutoDtcTaskFlag = 0;
	//SeTx522b_u_FirstDtctFlag = 0U;
	//SeTx522b_u_UnDtctCnt = 0U;
	for(Le_u_i = 0U;Le_u_i < TXBUFF_NUM;Le_u_i++)
	{	
		TxMsg[Le_u_i].NewFlag = 0U;
		TxMsg[Le_u_i].Lng = 0U;
	}
	TxMsgHeader = 0U;
	TxMsgRear = 0U;
	(void)Tx522bCfg_ReadEE(EepromCfg_Key,SaCardRd_u_PDfultKey,6U);//读取keyA密码RAM
}


/******************************************************
*函数名：Tx522b_MainFunction

*形  参：void

*返回值：void

*描  述：主任务函数

*备  注：
******************************************************/
void Tx522b_MainFunction(void)
{
	if(1U == GetTx522bCfg_u_RxMsgRenew())/*串口数据更新*/
	{
		GetTx522bCfg_u_RxMsg(RxMsg.Dt.Block);
		Tx522b_CmdDeal();
	}
	
	if(1U == SeTx522b_u_AutoDtctFlag)/*卡片自动检测模式*/
	{
		SeTx522b_dw_RcovrAutoDtctT = 0U;
		Tx522b_AutoDetectCard();
	}
	else
	{
		if(SeTx522b_dw_RcovrAutoDtctT >= 0x00030FAF)
		{
			SeTx522b_dw_RcovrAutoDtctT = 0U;			
			SeTx522b_u_AutoDtctFlag = 1U;
		}
		else
		{
			SeTx522b_dw_RcovrAutoDtctT++;
		}
	}
	
	if(1 == GetTx522bCfg_u_TxIdle())/*发送数据发送缓冲区数据*/
	{
		if(SeTx522b_dw_DelayTimer >= 0x00000E2A)
		{
			SeTx522b_dw_DelayTimer = 0U;
			if(TxMsg[TxMsgRear].NewFlag == 1U)
			{
				SetTx522bCfg_TxMsg(TxMsg[TxMsgRear].Dt,TxMsg[TxMsgRear].Lng);
				TxMsg[TxMsgRear].NewFlag = 0U;
				TxMsgRear++;
				if(TxMsgRear == TXBUFF_NUM)
				{
					TxMsgRear = 0U;
				}
			}
		}
		else
		{
			SeTx522b_dw_DelayTimer++;
		}
	}
	else
	{
		SeTx522b_dw_DelayTimer = 0U;
	}
	
	FM175X_ExitSoftPowerdown();//设备进入低功耗模式时，退出低功耗
}

/******************************************************
*函数名：Tx522b_CmdDeal

*形  参：void

*返回值：void

*描  述：命令处理过程

*备  注：
******************************************************/
static void Tx522b_CmdDeal(void)
{
	uint8  LeTx_u_i;
	uint8  LeTx_u_Lng;
	uint8  LaTx_u_SendBuff[52];
	uint8  LaTx_u_TagType[2];
	uint8  LaTx_u_Sak[3];

	LaTx_u_SendBuff[0] = RxMsg.Dt.DtSrt.Seqnr;/*填充发送包号*/
	switch(RxMsg.Dt.DtSrt.Cmd)
	{
        case LoadKey:/*装载密钥指令*/
		{
			SeTx522b_u_AutoDtctFlag = 0U;/*退出自动侦测卡片*/
			for(LeTx_u_i = 0U;LeTx_u_i < RxMsg.Dt.DtSrt.DtLng;LeTx_u_i++)
			{
				SaCardRd_u_PDfultKey[LeTx_u_i] = RxMsg.Dt.DtSrt.ValidDt[LeTx_u_i];
			}
			if(1U == Tx522bCfg_WriteEE(Tx522bCfg_Key,RxMsg.Dt.DtSrt.ValidDt,RxMsg.Dt.DtSrt.DtLng))/*写密钥成功*/
			{
				LaTx_u_SendBuff[1] = COMM_OK;
			}
			else
			{
				LaTx_u_SendBuff[1] = COMM_ERR;
			}
			LaTx_u_SendBuff[2] = 0;/*有效数据0长度*/
			LaTx_u_SendBuff[3] = CalTx522b_u_XOR(LaTx_u_SendBuff,3);/*计算校验和*/
			LeTx_u_Lng = 4U;
		}
		break;
		case GetCardSnr:/*激活A卡片并获取卡号*/
		{
			SeTx522b_u_AutoDtctFlag = 0U;/*退出自动侦测卡片*/
			if(1U == GetTx522bCfg_u_ACardSnr(RxMsg.Dt.DtSrt.ValidDt[0U],LaTx_u_TagType,LaTx_u_Sak,&RxMsg.Dt.DtSrt.DtLng,RxMsg.Dt.DtSrt.ValidDt))
			{
				LaTx_u_SendBuff[1] = COMM_OK;
			}
			else
			{
				LaTx_u_SendBuff[1] = COMM_ERR;
			}					
			LaTx_u_SendBuff[2] = (4U+ RxMsg.Dt.DtSrt.DtLng);/*数据长度*/
			LaTx_u_SendBuff[3] = LaTx_u_TagType[0];
			LaTx_u_SendBuff[4] = LaTx_u_TagType[1];
			LaTx_u_SendBuff[5] = LaTx_u_Sak[0];
			LaTx_u_SendBuff[6] = RxMsg.Dt.DtSrt.DtLng;
			for(LeTx_u_i = 0U;LeTx_u_i < RxMsg.Dt.DtSrt.DtLng;LeTx_u_i++)
			{
				LaTx_u_SendBuff[7 + LeTx_u_i] = RxMsg.Dt.DtSrt.ValidDt[LeTx_u_i];
			}
			LaTx_u_SendBuff[7+RxMsg.Dt.DtSrt.DtLng] = CalTx522b_u_XOR(LaTx_u_SendBuff,(7+RxMsg.Dt.DtSrt.DtLng));/*计算校验和*/
			LeTx_u_Lng = 8 + RxMsg.Dt.DtSrt.DtLng;
		}
		break;
		case ReadBlock:/*读块*/
		{
			SeTx522b_u_AutoDtctFlag = 0U;/*退出自动侦测卡片*/
			LaTx_u_SendBuff[2] = 0x10;/*有效数据16Byte长度*/
			LaTx_u_SendBuff[1] = GetTx522bCfg_u_BlockData(RxMsg.Dt.DtSrt.ValidDt[0],RxMsg.Dt.DtSrt.ValidDt);
			if(COMM_OK == LaTx_u_SendBuff[1])
			{
				for(LeTx_u_i = 0U;LeTx_u_i < 16U;LeTx_u_i++)
				{
					LaTx_u_SendBuff[3 + LeTx_u_i] = RxMsg.Dt.DtSrt.ValidDt[LeTx_u_i];
				}
			}
			LaTx_u_SendBuff[19] = CalTx522b_u_XOR(LaTx_u_SendBuff,19);/*计算校验和*/
			LeTx_u_Lng = 20;
		}
		break;
		case WriteBlock:/*写块*/
		{
			SeTx522b_u_AutoDtctFlag = 0U;/*退出自动侦测卡片*/
			LaTx_u_SendBuff[1] = Tx522bCfg_u_WriteBlock(RxMsg.Dt.DtSrt.ValidDt[0U],&RxMsg.Dt.DtSrt.ValidDt[1U]);
			LaTx_u_SendBuff[2] = 0;/*有效数据0长度*/
			LaTx_u_SendBuff[3] = CalTx522b_u_XOR(LaTx_u_SendBuff,3);/*计算校验和*/
			LeTx_u_Lng = 4;
		}
		break;
		case ReadSector:/*读扇区*/
		{
			SeTx522b_u_AutoDtctFlag = 0U;/*退出自动侦测卡片*/
		}	
		break;
		case DetectCard:/*自动寻卡*/
		{
			SeTx522b_u_AutoDtctFlag = 1U;/*开启自动侦测卡片*/
			LaTx_u_SendBuff[1] = COMM_OK;
			LaTx_u_SendBuff[2] = 0;/*有效数据0长度*/
			LaTx_u_SendBuff[3] = CalTx522b_u_XOR(LaTx_u_SendBuff,3);/*计算校验和*/
			LeTx_u_Lng = 4;
		}
		break;
		case SetBaudRate:/*设置波特率*/
		{
			if(1U == Tx522bCfg_WriteEE(Tx522bCfg_BaudRate,RxMsg.Dt.DtSrt.ValidDt,RxMsg.Dt.DtSrt.DtLng))/*写波特率成功*/
			{
				SetTx522bCfg_BaudRtae(*((uint32*)(&RxMsg.Dt.DtSrt.ValidDt[0U])));
				LaTx_u_SendBuff[1] = COMM_OK;
			}
			else
			{
				LaTx_u_SendBuff[1] = COMM_ERR;
			}
			LaTx_u_SendBuff[2] = 0;/*有效数据0长度*/
			LaTx_u_SendBuff[3] = CalTx522b_u_XOR(LaTx_u_SendBuff,3);/*计算校验和*/
			LeTx_u_Lng = 4U;
		}
		break;
		case SetConfig://设置一下读卡芯片
		{
			//(void)FM175X_SoftReset();
			LaTx_u_SendBuff[1] = COMM_OK;
			LaTx_u_SendBuff[2] = 0;/*有效数据0长度*/
			LaTx_u_SendBuff[3] = CalTx522b_u_XOR(LaTx_u_SendBuff,3);/*计算校验和*/
			LeTx_u_Lng = 4U;
		}
		break;
		default://无效/非法指令
		{
			LaTx_u_SendBuff[1] = COMM_ILLEGAL;
			LaTx_u_SendBuff[2] = 0;/*有效数据0长度*/
			LaTx_u_SendBuff[3] = CalTx522b_u_XOR(LaTx_u_SendBuff,3);/*计算校验和*/
			LeTx_u_Lng = 4U;
		}
		break;
	}
	
	if(1 == GetTx522bCfg_u_TxIdle())
	{
		SetTx522bCfg_TxMsg(LaTx_u_SendBuff,LeTx_u_Lng);
	}
	else
	{
		(void)Tx522b_DataSaveToBuff(LaTx_u_SendBuff,LeTx_u_Lng);
	}
}


/******************************************************
*函数名：Tx522b_DataSaveToBuff

*形  参：

*返回值：

*描  述：数据保存到发送缓冲区

*备  注：
******************************************************/
static uint8 Tx522b_DataSaveToBuff(uint8* LeTx522b_u_Data,uint8 LeTx522b_u_Lng)
{
	uint8 Le_u_i;
	uint8 Le_u_rtnVal = 0U;
	if(TxMsg[TxMsgHeader].NewFlag == 0U)
	{
		for(Le_u_i = 0U;Le_u_i < LeTx522b_u_Lng;Le_u_i++)
		{
			TxMsg[TxMsgHeader].Dt[Le_u_i] = LeTx522b_u_Data[Le_u_i];
		}
		TxMsg[TxMsgHeader].Lng = LeTx522b_u_Lng;
		TxMsg[TxMsgHeader].NewFlag =1U;
		TxMsgHeader++;
		if(TxMsgHeader == TXBUFF_NUM)
		{
			TxMsgHeader = 0U;
		}
		Le_u_rtnVal = TX522B_OK;
	}
	else/*缓存区溢出*/
	{
		Le_u_rtnVal = TX522B_BUFF_OVERFLOW;
	}
	return Le_u_rtnVal;
}

/******************************************************
*函数名：CalTx522b_u_XOR

*形  参：

*返回值：

*描  述：异或取反

*备  注：
******************************************************/
static uint8 CalTx522b_u_XOR(uint8* LeTx522b_u_Data,uint8 LeTx522b_u_Lng)
{
	uint8 LeTx522b_u_i;
	uint8 LeTx522b_u_Xor = 0U;
	for(LeTx522b_u_i = 0U; LeTx522b_u_i < LeTx522b_u_Lng;LeTx522b_u_i++)
	{
		LeTx522b_u_Xor ^= LeTx522b_u_Data[LeTx522b_u_i];
	}
	LeTx522b_u_Xor = (~LeTx522b_u_Xor);
	return LeTx522b_u_Xor;
}


/******************************************************
*函数名：Tx522b_AutoDetectCard

*形  参：

*返回值：

*描  述：自动侦测卡片处理

*备  注：
******************************************************/
static void Tx522b_AutoDetectCard(void)
{
	uint8  LaTx_u_TagType[2];
	uint8  LaTx_u_Sak[3];
	switch(SeTx522b_u_AutoDtcTaskFlag)
	{
		case 0:
		{
			(void)FM175X_SoftReset();
			if(1U == GetTx522bCfg_u_ACardSnr(RxMsg.Dt.DtSrt.ValidDt[0],LaTx_u_TagType,LaTx_u_Sak,&RxMsg.Dt.DtSrt.DtLng,&RxMsg.Dt.DtSrt.ValidDt[1]))
			{/*检测到A卡*/
				SendTx522b_CardId(0U,LaTx_u_TagType,LaTx_u_Sak,RxMsg.Dt.DtSrt.DtLng,&RxMsg.Dt.DtSrt.ValidDt[1]);
				SeTx522b_u_AutoDtctFlag = 0U;
			}
			SeTx522b_u_AutoDtcTaskFlag = 1;
		}
		break;
		case 1:
		{
			(void)FM175X_SoftReset();
			if(1U == GetTx522bCfg_u_BCardSnr(&RxMsg.Dt.DtSrt.ValidDt[0],&RxMsg.Dt.DtSrt.DtLng))
			{/*检测到B卡*/
				SendTx522b_CardId(1U,LaTx_u_TagType,LaTx_u_Sak,RxMsg.Dt.DtSrt.DtLng,&RxMsg.Dt.DtSrt.ValidDt[0]);
				SeTx522b_u_AutoDtctFlag = 0U;
			}
			SeTx522b_u_AutoDtcTaskFlag = 0;
		}
		default:
		{
			SeTx522b_u_AutoDtcTaskFlag = 0;
		}
		break;
	}
}


/******************************************************
*函数名：SendTx522b_CardId

*形  参：

*返回值：

*描  述：写块

*备  注：
******************************************************/
static void SendTx522b_CardId(uint8 CardType,uint8  *TagType, uint8  *Sak,uint8 SnrLen,uint8 *Snr)
{
	uint8 LeTx_u_i;
	uint8 LeTx_u_Lng = 0U;
	uint8 LaTx_u_SendBuff[18U];
	LaTx_u_SendBuff[0] = 0x00;/*填充发送包号*/
	LaTx_u_SendBuff[1] = 0x00;/*状态字节*/
	switch(CardType)
	{
		case 0U:/*A卡*/
		{
			LaTx_u_SendBuff[2] = (4U+ SnrLen);/*数据长度*/
			LaTx_u_SendBuff[3] = TagType[0];
			LaTx_u_SendBuff[4] = TagType[1];
			LaTx_u_SendBuff[5] = Sak[0];
			LaTx_u_SendBuff[6] = SnrLen;
			if(SnrLen < 8U)
			{
				for(LeTx_u_i = 0U;LeTx_u_i < SnrLen;LeTx_u_i++)
				{
					LaTx_u_SendBuff[7 + LeTx_u_i] = Snr[LeTx_u_i];
				}
				LaTx_u_SendBuff[7+SnrLen] = CalTx522b_u_XOR(LaTx_u_SendBuff,(7+SnrLen));/*计算校验和*/
				LeTx_u_Lng = 8 + SnrLen;
			}
			else
			{
				
			}
		}
		break;
        case 1U:/*B卡*/
		{
			if(SnrLen < 14)
			{
				LaTx_u_SendBuff[2] = SnrLen;/*数据长度*/
				for(LeTx_u_i = 0U;LeTx_u_i < SnrLen;LeTx_u_i++)
				{
					LaTx_u_SendBuff[3 + LeTx_u_i] = Snr[LeTx_u_i];
				}
				LaTx_u_SendBuff[3+SnrLen] = CalTx522b_u_XOR(LaTx_u_SendBuff,(3+SnrLen));/*计算校验和*/
				LeTx_u_Lng = 4 + SnrLen;
			}
			else
			{
				
			}
		}
		break;
		default:
		break;
	}
	if(1 == GetTx522bCfg_u_TxIdle())
	{
		SetTx522bCfg_TxMsg(LaTx_u_SendBuff,LeTx_u_Lng);
	}
	else
	{
		(void)Tx522b_DataSaveToBuff(LaTx_u_SendBuff,LeTx_u_Lng);
	}
}
