/******************************************************
�ļ�����	UartCmn

������	��˫������ͨ��	TX522B	
Data			Vasion			author
2018/1/10		V1.0			liujian
*******************************************************/

/*******************************************************
description�� include the header file
*******************************************************/
#include "UartCmn.h"

/*******************************************************
description�� function declaration
*******************************************************/
/*Global function declaration*/

/*Static function declaration*/
static Uart_Rx_Msg   Uart_RecMsg;/*�������ݽṹ���Ա*/
static Uart_TX_Msg   Uart_TxMsg;/*�������ݽṹ���Ա*/
static uint8 		 SaUartCmn_u_RxBuff[UARTCMN_RX_PCKT_LNG];/*���ձ��Ļ�����*/
/*******************************************************
description�� global variable definitions
*******************************************************/

/*******************************************************
description�� static variable definitions
*******************************************************/
static void UartCmn_u_RxMsgBuff(void);
static uint8 GetUartCmn_u_XOR(void);
/******************************************************
description�� function code
******************************************************/
/******************************************************
*��������void InitUartCmn_parameter(void)

*��  �Σ�void

*����ֵ��void

*��  ������ʼ��

*��  ע��
******************************************************/
void InitUartCmn_parameter(void)
{
	Uart_TxMsg.ucTxFlg = 0U;/*��ʼ�������ݷ��ͱ�־��Ч*/
	Uart_TxMsg.ucTxCnt = 0U;
	Uart_RecMsg.RxBusyFlg = 0U;/*��ʼ�������ݽ���æ��־��Ч*/
}

/******************************************************
*��������UartCmn_Rx_Msg

*��  �Σ�

*����ֵ��

*��  �������ڽ���

*��  ע�����ڽ����жϵ���
******************************************************/
void UartCmn_Rx_Msg(void)
{   
    unsigned char Buff;/* �������ݻ��� */
         
    if (UART1_GetFlagStatus(UART1_FLAG_OR) || UART1_GetFlagStatus(UART1_FLAG_FE))/* ֡�����־λ ���� ���������־λ */
    {
        Buff = UART1_ReceiveData8();/* ���Break�����ݼ�֡�������� */         
    }
	else if (UART1_GetFlagStatus(UART1_FLAG_RXNE))/* �������ݼĴ�������־λ */
    {
		Uart_RecMsg.RxBusyFlg = 1U;/*�����ݽ���æ��־��Ч*/
        Buff = UART1_ReceiveData8();/*��ȡ���ݼĴ�������*/        
        switch(Uart_RecMsg.UartHeaderFlag) 
        {
			case 0U:/*����֡ͷ*/                           		
				Uart_RecMsg.UartRx.Pckt.UartHeader[0] = Buff;
				if(Uart_RecMsg.UartRx.Pckt.UartHeader[0] == UARTCMN_RX_HEADER)   /*�ж�֡ͷ�Ƿ���ȷ*/
				{
					Uart_RecMsg.UartHeaderFlag=1U; /*����������֡β����*/
				} 
				else 
				{
					/*֡ͷ�������½���֡ͷ*/
				}
			break;		
			case 1U:/*���հ���*/
				Uart_RecMsg.UartRx.Pckt.UartSeqnr[0] = Buff;
				Uart_RecMsg.UartHeaderFlag = 2;
			break;
			case 2U:/*���������ֽ�*/
				Uart_RecMsg.UartRx.Pckt.UartCmd[0] = Buff;
				Uart_RecMsg.UartHeaderFlag = 3;
			break;
			case 3U:/*������Ч���ݳ��ȱ�ʾ�ֽ�*/
				Uart_RecMsg.UartRx.Pckt.UartRxDataLng[0] = Buff;
				if(Uart_RecMsg.UartRx.Pckt.UartRxDataLng[0] <= UARTCMN_RX_PCKTDATA_LNG)
				{/*���ݳ�����Ч*/
					if(Uart_RecMsg.UartRx.Pckt.UartRxDataLng[0] != 0U)
					{
						Uart_RecMsg.UartHeaderFlag = 4;
					}
					else
					{
						Uart_RecMsg.UartHeaderFlag = 5;
					}
				}
				else/*���ݳ��ȴ���*/
				{
					Uart_RecMsg.UartHeaderFlag = 0;
				}
			break;
			case 4U:/*������Ч����*/ 
				Uart_RecMsg.UartRx.Pckt.UartRxData[Uart_RecMsg.UartRxNm++]=Buff;
				if(Uart_RecMsg.UartRxNm >= Uart_RecMsg.UartRx.Pckt.UartRxDataLng[0])/*��Ч���ݽ������*/
				{
					Uart_RecMsg.UartRxNm = 0U;/*������Ч���ݼ���������*/
					Uart_RecMsg.UartHeaderFlag = 5U;	
				}
				else
				{
					/*��Ч���ݽ�����*/
				}
			break;
			case 5U:/*����У����ֽ�*/
				Uart_RecMsg.UartRx.Pckt.UartCheck[0] = Buff;
				Uart_RecMsg.UartHeaderFlag = 6;
			break;
			case 6U:/*���ս����ֽ�*/
				Uart_RecMsg.UartRx.Pckt.UartETX[0] = Buff;
				if(Uart_RecMsg.UartRx.Pckt.UartETX[0] == UARTCMN_RX_ETC)/*��֡���Ľ������*/
				{
					Uart_RecMsg.UartRXFlag = 1U;/*���ճɹ���־*/
					Uart_RecMsg.RxBusyFlg = 0U;/*�����ݽ���æЧ*/
					Uart_RecMsg.UartHeaderFlag = 0;
				}
				else/*������ֹ������*/
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
		UartCmn_u_RxMsgBuff();/*�������ݻ���*/
	}
}


/******************************************************
*��������UartCmn_Tx_Msg

*��  �Σ�

*����ֵ��

*��  �������ڷ���

*��  ע��
******************************************************/
void UartCmn_Tx_Msg(void)
{
	uint32 Le_dw_Timer = 0xffffffff; 
	if(1U == Uart_TxMsg.ucTxFlg)
	{
		if(UART1_GetFlagStatus(UART1_FLAG_TXE))/*���ͼĴ�����*/
		{
			if(Uart_TxMsg.ucTxCnt < Uart_TxMsg.ucLength)
			{    
				UART1_SendData8(Uart_TxMsg.ucTxData[Uart_TxMsg.ucTxCnt]) ;/* �������ݳ� */
				Uart_TxMsg.ucTxCnt++;		
			}
			else if(Uart_TxMsg.ucTxCnt >= Uart_TxMsg.ucLength)
			{
				while(!(UART1_GetFlagStatus(UART1_FLAG_TC)) && (Le_dw_Timer--));
				Uart_TxMsg.ucTxCnt = 0U;/*�巢�ͼ���ֵ*/
				Uart_TxMsg.ucTxFlg = 0U;/*�巢�ͱ�־*/
				DISABLE_TIEN;/* ��ֹ���ͼĴ������ж� */
				DISABLE_TEN;  /* ��ֹ���� */
				//ENABLE_RIEN; /* �����ж����� */
				//ENABLE_REN; /* ������� */	
			}
			else
			{}
		}  		
	}
}


/******************************************************
*��������UartCmn_u_RxMsgBuff

*��  �Σ�

*����ֵ��

*��  �����������ݻ���

*��  ע��
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
*��������GetUartCmn_u_RxMsgRenew

*��  �Σ�

*����ֵ��

*��  ������ȡ�������ݸ��±�־

*��  ע��9600�����ʣ�10ms�������ڣ�115200�����ʣ�5ms��������
******************************************************/
uint8 GetUartCmn_u_RxMsgRenew(void)
{
	uint8 LeUartCmn_u_Flg = 0U;
	if(Uart_RecMsg.UartNewFlag == 1U)/*�������ݻ���������*/
	{
		Uart_RecMsg.UartNewFlag = 0U;
		if(1U == GetUartCmn_u_XOR())/*У��ͨ��*/
		{
			LeUartCmn_u_Flg =1U;/*�������ݸ��±�־����Ч*/
		}
	}
	return LeUartCmn_u_Flg;
}


/******************************************************
*��������GetUartCmn_u_XOR

*��  �Σ�

*����ֵ��

*��  �������ȡ��У��

*��  ע��
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
	if(LeUartCmn_u_Xor == SaUartCmn_u_RxBuff[60])/*У��ͨ��*/
	{
		LeUartCmn_u_ok = 1U;
	}
	return LeUartCmn_u_ok;
}

/******************************************************
*��������GetUartCmn_u_RxMsg

*��  �Σ�

*����ֵ��

*��  ������ȡ��������

*��  ע��
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
*��������GetUartCmn_u_TxIdle

*��  �Σ�

*����ֵ�� 1--���У�0--æ

*��  ������ȡ�����Ƿ����:1--���У�0--æ

*��  ע��
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
*��������GetUartCmn_u_TxIdle

*��  �Σ�

*����ֵ�� 1--���У�0--æ

*��  ������ȡ���ݽ����Ƿ����:1--���У�0--æ

*��  ע��
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
*��������SetUartCmn_TxMsg

*��  �Σ�LeUartCmn_u_TxData[]   ��������
		LeUartCmn_u_Lng		   ��������֡����

*����ֵ��

*��  �������÷��ͱ��Ĳ���������

*��  ע��
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
	Uart_TxMsg.ucTxFlg = 1U;/*�÷��ͱ�־��Ч*/
	//DISABLE_RIEN;/* �رս����ж����� */
	//DISABLE_REN; /* ��ֹ���� */
	ENABLE_TEN; /* ������ */
	ENABLE_TIEN;/* ʹ�ܷ��ͼĴ������ж� */		
}


/******************************************************
*��������Uart_Send

*��  �Σ�void

*����ֵ��void

*��  ����

*��  ע��
******************************************************/
void Uart_Send(uint8_t* Data,uint8_t Length)
{
	uint8_t LeUart_u_Len;
	DISABLE_RIEN;/* �رս����ж����� */
	DISABLE_REN; /* ��ֹ���� */
    ENABLE_TEN;
	Uart_TxMsg.ucTxFlg = 1U;/*�÷��ͱ�־��Ч*/
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
	Uart_TxMsg.ucTxFlg = 0U;/*�÷��ͱ�־��Ч*/
	
    DISABLE_TEN;
	ENABLE_RIEN; /* �����ж����� */
	ENABLE_REN; /* ������� */
}

/******************************************************
*��������Uart_PrintStr

*��  �Σ�void

*����ֵ��void

*��  ������ӡ�ַ���

*��  ע��
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
