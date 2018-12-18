/******************************************************
文件名：	UartCmn

描述：	半双工串口通信	TX522B	
Data			Vasion			author
2018/1/10		V1.0			liujian
*******************************************************/

/*******************************************************
description： include the header file
*******************************************************/
#include "UartCmn.h"

/*******************************************************
description： function declaration
*******************************************************/
/*Global function declaration*/

/*Static function declaration*/
static Uart_Rx_Msg   Uart_RecMsg;/*接收数据结构体成员*/
static Uart_TX_Msg   Uart_TxMsg;/*发送数据结构体成员*/
static uint8 		 SaUartCmn_u_RxBuff[UARTCMN_RX_PCKT_LNG];/*接收报文缓存区*/
/*******************************************************
description： global variable definitions
*******************************************************/

/*******************************************************
description： static variable definitions
*******************************************************/
static void UartCmn_u_RxMsgBuff(void);
static uint8 GetUartCmn_u_XOR(void);
/******************************************************
description： function code
******************************************************/
/******************************************************
*函数名：void InitUartCmn_parameter(void)

*形  参：void

*返回值：void

*描  述：初始化

*备  注：
******************************************************/
void InitUartCmn_parameter(void)
{
	Uart_TxMsg.ucTxFlg = 0U;/*初始化置数据发送标志无效*/
	Uart_TxMsg.ucTxCnt = 0U;
	Uart_RecMsg.RxBusyFlg = 0U;/*初始化置数据接收忙标志无效*/
}

/******************************************************
*函数名：UartCmn_Rx_Msg

*形  参：

*返回值：

*描  述：串口接收

*备  注：串口接收中断调用
******************************************************/
void UartCmn_Rx_Msg(void)
{   
    unsigned char Buff;/* 接受数据缓存 */
         
    if (UART1_GetFlagStatus(UART1_FLAG_OR) || UART1_GetFlagStatus(UART1_FLAG_FE))/* 帧错误标志位 或者 数据溢出标志位 */
    {
        Buff = UART1_ReceiveData8();/* 清除Break段数据及帧错误数据 */         
    }
	else if (UART1_GetFlagStatus(UART1_FLAG_RXNE))/* 接受数据寄存器满标志位 */
    {
		Uart_RecMsg.RxBusyFlg = 1U;/*置数据接收忙标志有效*/
        Buff = UART1_ReceiveData8();/*读取数据寄存器数据*/        
        switch(Uart_RecMsg.UartHeaderFlag) 
        {
			case 0U:/*接收帧头*/                           		
				Uart_RecMsg.UartRx.Pckt.UartHeader[0] = Buff;
				if(Uart_RecMsg.UartRx.Pckt.UartHeader[0] == UARTCMN_RX_HEADER)   /*判断帧头是否正确*/
				{
					Uart_RecMsg.UartHeaderFlag=1U; /*启动数据与帧尾接收*/
				} 
				else 
				{
					/*帧头错误，重新接收帧头*/
				}
			break;		
			case 1U:/*接收包号*/
				Uart_RecMsg.UartRx.Pckt.UartSeqnr[0] = Buff;
				Uart_RecMsg.UartHeaderFlag = 2;
			break;
			case 2U:/*接收命令字节*/
				Uart_RecMsg.UartRx.Pckt.UartCmd[0] = Buff;
				Uart_RecMsg.UartHeaderFlag = 3;
			break;
			case 3U:/*接收有效数据长度表示字节*/
				Uart_RecMsg.UartRx.Pckt.UartRxDataLng[0] = Buff;
				if(Uart_RecMsg.UartRx.Pckt.UartRxDataLng[0] <= UARTCMN_RX_PCKTDATA_LNG)
				{/*数据长度有效*/
					if(Uart_RecMsg.UartRx.Pckt.UartRxDataLng[0] != 0U)
					{
						Uart_RecMsg.UartHeaderFlag = 4;
					}
					else
					{
						Uart_RecMsg.UartHeaderFlag = 5;
					}
				}
				else/*数据长度错误*/
				{
					Uart_RecMsg.UartHeaderFlag = 0;
				}
			break;
			case 4U:/*接收有效数据*/ 
				Uart_RecMsg.UartRx.Pckt.UartRxData[Uart_RecMsg.UartRxNm++]=Buff;
				if(Uart_RecMsg.UartRxNm >= Uart_RecMsg.UartRx.Pckt.UartRxDataLng[0])/*有效数据接收完成*/
				{
					Uart_RecMsg.UartRxNm = 0U;/*接收有效数据计数器清零*/
					Uart_RecMsg.UartHeaderFlag = 5U;	
				}
				else
				{
					/*有效数据接收中*/
				}
			break;
			case 5U:/*接收校验和字节*/
				Uart_RecMsg.UartRx.Pckt.UartCheck[0] = Buff;
				Uart_RecMsg.UartHeaderFlag = 6;
			break;
			case 6U:/*接收结束字节*/
				Uart_RecMsg.UartRx.Pckt.UartETX[0] = Buff;
				if(Uart_RecMsg.UartRx.Pckt.UartETX[0] == UARTCMN_RX_ETC)/*整帧报文接收完成*/
				{
					Uart_RecMsg.UartRXFlag = 1U;/*接收成功标志*/
					Uart_RecMsg.RxBusyFlg = 0U;/*置数据接收忙效*/
					Uart_RecMsg.UartHeaderFlag = 0;
				}
				else/*报文终止符有误*/
				{
					Uart_RecMsg.UartHeaderFlag = 0;
				}
				
			break;
			default:
				Uart_RecMsg.UartHeaderFlag = 0U;
			break;
        }
    }
	else
	{}
	
	if(1U == Uart_RecMsg.UartRXFlag)
	{
		Uart_RecMsg.UartRXFlag = 0U;
		UartCmn_u_RxMsgBuff();/*接收数据缓存*/
	}
}


/******************************************************
*函数名：UartCmn_Tx_Msg

*形  参：

*返回值：

*描  述：串口发送

*备  注：
******************************************************/
void UartCmn_Tx_Msg(void)
{
	uint32 Le_dw_Timer = 0xffffffff; 
	if(1U == Uart_TxMsg.ucTxFlg)
	{
		if(UART1_GetFlagStatus(UART1_FLAG_TXE))/*发送寄存器空*/
		{
			if(Uart_TxMsg.ucTxCnt < Uart_TxMsg.ucLength)
			{    
				UART1_SendData8(Uart_TxMsg.ucTxData[Uart_TxMsg.ucTxCnt]) ;/* 发送数据场 */
				Uart_TxMsg.ucTxCnt++;		
			}
			else if(Uart_TxMsg.ucTxCnt >= Uart_TxMsg.ucLength)
			{
				while(!(UART1_GetFlagStatus(UART1_FLAG_TC)) && (Le_dw_Timer--));
				Uart_TxMsg.ucTxCnt = 0U;/*清发送计数值*/
				Uart_TxMsg.ucTxFlg = 0U;/*清发送标志*/
				DISABLE_TIEN;/* 禁止发送寄存器空中断 */
				DISABLE_TEN;  /* 禁止发送 */
				//ENABLE_RIEN; /* 接收中断请求 */
				//ENABLE_REN; /* 允许接收 */	
			}
			else
			{}
		}  		
	}
}


/******************************************************
*函数名：UartCmn_u_RxMsgBuff

*形  参：

*返回值：

*描  述：接收数据缓存

*备  注：
******************************************************/
static void UartCmn_u_RxMsgBuff(void)
{ 
	uint8 LeUartCmn_u_Index;
	for(LeUartCmn_u_Index = 0U;LeUartCmn_u_Index < UARTCMN_RX_PCKT_LNG; LeUartCmn_u_Index++)
	{
		SaUartCmn_u_RxBuff[LeUartCmn_u_Index] = Uart_RecMsg.UartRx.UartPckt[LeUartCmn_u_Index];
	}
	Uart_RecMsg.UartNewFlag =1U;
}


/******************************************************
*函数名：GetUartCmn_u_RxMsgRenew

*形  参：

*返回值：

*描  述：获取接收数据更新标志

*备  注：9600波特率，10ms调度周期；115200波特率，5ms调度周期
******************************************************/
uint8 GetUartCmn_u_RxMsgRenew(void)
{
	uint8 LeUartCmn_u_Flg = 0U;
	if(Uart_RecMsg.UartNewFlag == 1U)/*接收数据缓存区更新*/
	{
		Uart_RecMsg.UartNewFlag = 0U;
		if(1U == GetUartCmn_u_XOR())/*校验通过*/
		{
			LeUartCmn_u_Flg =1U;/*接收数据更新标志置有效*/
		}
	}
	return LeUartCmn_u_Flg;
}


/******************************************************
*函数名：GetUartCmn_u_XOR

*形  参：

*返回值：

*描  述：异或取反校验

*备  注：
******************************************************/
static uint8 GetUartCmn_u_XOR(void)
{
	uint8 LeUartCmn_u_i;
	uint8 LeUartCmn_u_Lng;
	uint8 LeUartCmn_u_ok = 0U;
	uint8 LeUartCmn_u_Xor = 0U;
	LeUartCmn_u_Lng = SaUartCmn_u_RxBuff[3] + 3;
	for(LeUartCmn_u_i = 0U; LeUartCmn_u_i < LeUartCmn_u_Lng;LeUartCmn_u_i++)
	{
		LeUartCmn_u_Xor ^= SaUartCmn_u_RxBuff[UARTCMN_RX_SEQNR_STRTBYTE + LeUartCmn_u_i];
	}
	LeUartCmn_u_Xor = (~LeUartCmn_u_Xor);
	if(LeUartCmn_u_Xor == SaUartCmn_u_RxBuff[60])/*校验通过*/
	{
		LeUartCmn_u_ok = 1U;
	}
	return LeUartCmn_u_ok;
}

/******************************************************
*函数名：GetUartCmn_u_RxMsg

*形  参：

*返回值：

*描  述：获取接收数据

*备  注：
******************************************************/
void GetUartCmn_u_RxMsg(uint8* LeUartCmn_RxData)
{ 
	uint8 LeUartCmn_u_Index;
	for(LeUartCmn_u_Index = 0U;LeUartCmn_u_Index < UARTCMN_RX_SCLD_LNG; LeUartCmn_u_Index++)
	{
		LeUartCmn_RxData[LeUartCmn_u_Index] = SaUartCmn_u_RxBuff[UARTCMN_RX_PCKTHEAD_LNG+LeUartCmn_u_Index];
	}
}


/******************************************************
*函数名：GetUartCmn_u_TxIdle

*形  参：

*返回值： 1--空闲；0--忙

*描  述：获取发送是否空闲:1--空闲；0--忙

*备  注：
******************************************************/
uint8 GetUartCmn_u_TxIdle(void)
{
	if(0U == Uart_TxMsg.ucTxFlg)
	{
		return 1U;
	}
	else
	{
		return 0U;
	}
}

/******************************************************
*函数名：GetUartCmn_u_TxIdle

*形  参：

*返回值： 1--空闲；0--忙

*描  述：获取数据接收是否空闲:1--空闲；0--忙

*备  注：
******************************************************/
uint8 GetUartCmn_u_RxIdle(void)
{
	if(0U == Uart_RecMsg.RxBusyFlg)
	{
		return 1U;
	}
	else
	{
		return 0U;
	}
}

/******************************************************
*函数名：SetUartCmn_TxMsg

*形  参：LeUartCmn_u_TxData[]   发送数据
		LeUartCmn_u_Lng		   发送数据帧长度

*返回值：

*描  述：设置发送报文并启动发送

*备  注：
******************************************************/
void SetUartCmn_TxMsg(uint8* LeUartCmn_u_TxData,uint8 LeUartCmn_u_Lng)
{
	uint8 LeUartCmn_u_Index;
	Uart_TxMsg.ucTxData[0U] = UARTCMN_TX_HEADER;
	for(LeUartCmn_u_Index = 0U;LeUartCmn_u_Index < LeUartCmn_u_Lng;LeUartCmn_u_Index++)
	{
		Uart_TxMsg.ucTxData[1+LeUartCmn_u_Index] = LeUartCmn_u_TxData[LeUartCmn_u_Index];
	}
	Uart_TxMsg.ucTxData[1+LeUartCmn_u_Lng] = UARTCMN_TX_ETC;
	Uart_TxMsg.ucLength = LeUartCmn_u_Lng +2U;
	Uart_TxMsg.ucTxFlg = 1U;/*置发送标志有效*/
	//DISABLE_RIEN;/* 关闭接收中断请求 */
	//DISABLE_REN; /* 禁止接收 */
	ENABLE_TEN; /* 允许发送 */
	ENABLE_TIEN;/* 使能发送寄存器空中断 */		
}


/******************************************************
*函数名：Uart_Send

*形  参：void

*返回值：void

*描  述：

*备  注：
******************************************************/
void Uart_Send(uint8_t* Data,uint8_t Length)
{
	uint8_t LeUart_u_Len;
	DISABLE_RIEN;/* 关闭接收中断请求 */
	DISABLE_REN; /* 禁止接收 */
    ENABLE_TEN;
	Uart_TxMsg.ucTxFlg = 1U;/*置发送标志有效*/
	while((UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET));	
	UART1_SendData8(UARTCMN_TX_HEADER);
	while((UART1_GetFlagStatus(UART1_FLAG_TC)==RESET));
	
	for(LeUart_u_Len = 0;LeUart_u_Len < Length;LeUart_u_Len++)
	{
		while((UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET));	
		UART1_SendData8(Data[LeUart_u_Len]);
		while((UART1_GetFlagStatus(UART1_FLAG_TC)==RESET));
	}
	while((UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET));	
	UART1_SendData8(UARTCMN_TX_ETC);
	while((UART1_GetFlagStatus(UART1_FLAG_TC)==RESET));	
	Uart_TxMsg.ucTxFlg = 0U;/*置发送标志有效*/
	
    DISABLE_TEN;
	ENABLE_RIEN; /* 接收中断请求 */
	ENABLE_REN; /* 允许接收 */
}

/******************************************************
*函数名：Uart_PrintStr

*形  参：void

*返回值：void

*描  述：打印字符串

*备  注：
******************************************************/
void Uart_PrintStr(uint8_t* Str)
{
    ENABLE_TEN;
	while(*Str)
	{
		while((UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET));	
		UART1_SendData8(*(Str++));
		while((UART1_GetFlagStatus(UART1_FLAG_TC)==RESET));
	}
    DISABLE_TEN;
}
