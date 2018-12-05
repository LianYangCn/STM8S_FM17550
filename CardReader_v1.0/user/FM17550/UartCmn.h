/******************************************************
文件名：	UartCmn

描述：	半双工串口通信	

Data			  Vasion			author
2018/01/10		   V1.0			    liujian
*******************************************************/
#ifndef		_UARTCMN_H
#define		_UARTCMN_H
/*******************************************************
description： include the header file
*******************************************************/
#include "Include.h"

/*******************************************************
description： macro definitions
*******************************************************/
/**********宏开关定义*********/

/**********宏常量定义*********/
/*接收宏定义*/
/*TX522B协议帧*/
#define   UARTCMN_RX_HEADER    	    	0x20/*接收报文头起始符*/
#define   UARTCMN_RX_PCKTHEAD_LNG       1U/*报文头长度（单位：字节）*/

#define   UARTCMN_RX_PCKTHEAD_SEQNR     1U/*报文号长度（单位：字节）*/
#define   UARTCMN_RX_PCKTHEAD_CMD     	1U/*报文命令字（单位：字节）*/
#define   UARTCMN_RX_DATALNG_LNG        1U/*有效数据长度表示字节:无，配置0*/
#define   UARTCMN_RX_PCKTDATA_LNG       56U/*报文有效数据最大长度*/
#define   UARTCMN_RX_CHECK_LNG          1U/*报文校验字节长度*/
#define   UARTCMN_RX_ETX_LNG            1U/*报文结束字节长度*/
#define   UARTCMN_RX_ETC    	    	0x03/*接收报文终止符*/


#define   UARTCMN_RX_SEQNR_STRTBYTE		UARTCMN_RX_PCKTHEAD_LNG 
#define   UARTCMN_RX_DATALNG_STRTBYTE	(UARTCMN_RX_PCKTHEAD_LNG + UARTCMN_RX_PCKTHEAD_SEQNR + UARTCMN_RX_PCKTHEAD_CMD)/*报文有效数据长度表示字节开始字节*/
#define   UARTCMN_RX_DATA_STRTBYTE      (UARTCMN_RX_PCKTHEAD_LNG + UARTCMN_RX_PCKTHEAD_SEQNR + UARTCMN_RX_PCKTHEAD_CMD + UARTCMN_RX_DATALNG_LNG)/*报文有效数据开始字节*/
#define   UARTCMN_RX_CHCK_STRTBYTE      (UARTCMN_RX_PCKTHEAD_LNG + UARTCMN_RX_PCKTHEAD_SEQNR + UARTCMN_RX_PCKTHEAD_CMD + UARTCMN_RX_DATALNG_LNG + UARTCMN_RX_PCKTDATA_LNG)     /*报文校验字节起始位*/
#define   UARTCMN_RX_SCLD_LNG           (UARTCMN_RX_PCKTHEAD_SEQNR + UARTCMN_RX_PCKTHEAD_CMD +UARTCMN_RX_DATALNG_LNG + UARTCMN_RX_PCKTDATA_LNG)/*包号+命令+有效数据长度字节+有效数据*/
#define   UARTCMN_RX_PCKT_LNG           (UARTCMN_RX_CHCK_STRTBYTE + UARTCMN_RX_CHECK_LNG + UARTCMN_RX_ETX_LNG)/*报文总长*/
/*发送宏定义*/
#define   UARTCMN_TX_HEADER    	    	0x20/*报文头起始符*/
#define   UARTCMN_TX_ETC    	    	0x03/*报文终止符*/
#define   UARTCMN_TX_PCKT_LNG           62U/*发送报文总长最大长度*/




/*SCI通道设置*/





/***********宏函数***********/
#define  DISABLE_TIEN       (UART1->CR2 &= (uint8_t)(~0x80))/* 禁止发送寄存器空中断 */
#define  ENABLE_TIEN	 	(UART1->CR2 |= (uint8_t)0x80)/* 使能发送寄存器空中断 */	

#define  DISABLE_TEN    	(UART1->CR2 &= (uint8_t)(~UART1_CR2_TEN))/* 禁止发送 */
#define  ENABLE_TEN		    (UART1->CR2 |= (uint8_t)UART1_CR2_TEN) /* 允许发送 */

#define	 ENABLE_RIEN    	(UART1->CR2 |= (uint8_t)0x20) /* 使能接收中断请求 */
#define	 DISABLE_RIEN		(UART1->CR2 &= (uint8_t)(~0x20))/* 关闭接收中断请求 */

#define	 ENABLE_REN			(UART1->CR2 |= (uint8_t)UART1_CR2_REN) /* 允许接收 */	
#define  DISABLE_REN		(UART1->CR2 &= (uint8_t)(~UART1_CR2_REN)) /* 禁止接收 */


/*******************************************************
description： struct definitions
*******************************************************/

/*******************************************************
description： typedef definitions
*******************************************************/
/*****struct definitions*****/
typedef struct 
{		
	unsigned char UartRxNm;/* 接收数据下标 */
	unsigned char UartRXFlag;/* 接收完成标志 */ 
	unsigned char RxBusyFlg;/* 报文接收忙标志 */
	unsigned char UartHeaderFlag;/* 报头接收完成标志 */
	unsigned char UartNewFlag;/* 接受到新数据标志 */
	union
	{
		unsigned char UartPckt[UARTCMN_RX_PCKT_LNG];/* 报文总长：报文头+数据+校验+帧结束 */
		struct
		{
			unsigned char UartHeader[UARTCMN_RX_PCKTHEAD_LNG];/* 接收报头 */
			unsigned char UartSeqnr[UARTCMN_RX_PCKTHEAD_SEQNR];/* 接收帧包号*/
			unsigned char UartCmd[UARTCMN_RX_PCKTHEAD_CMD];/* 接收帧命令*/
			unsigned char UartRxDataLng[UARTCMN_RX_DATALNG_LNG];/* 接收有效数据段长度表示*/
			unsigned char UartRxData[UARTCMN_RX_PCKTDATA_LNG];/* 接收的有效数据段：按最大长度定义存储空间*/
			unsigned char UartCheck[UARTCMN_RX_CHECK_LNG];/* 接收检验字节 */
			unsigned char UartETX[UARTCMN_RX_ETX_LNG];/* 帧结束*/
		}Pckt;
	}UartRx;
}Uart_Rx_Msg; /*报文接收结构体*/ 

typedef struct
{
    uint8  ucTxData[UARTCMN_TX_PCKT_LNG];/* 发送报文缓冲 */
    uint8  ucLength;/* 报文长度 */
    uint8  ucTxCnt;/*发送计数*/
	uint8  ucTxFlg;/*发送标志：1—有数据需要或正在发送；0——没有数据发送*/
}Uart_TX_Msg;/*报文发送结构体*/

/******enum definitions******/

/******union definitions*****/

/*******************************************************
description： variable External declaration
*******************************************************/

/*******************************************************
description： function External declaration
*******************************************************/
extern void  InitUartCmn_parameter(void);
extern void  UartCmn_Rx_Msg(void);
extern void  UartCmn_Tx_Msg(void);
extern void  SetUartCmn_TxMsg(uint8* LeUartCmn_u_TxData,uint8 LeUartCmn_u_Lng);
extern uint8 GetUartCmn_u_RxMsgRenew(void);
extern void  GetUartCmn_u_RxMsg(uint8* LeUartCmn_RxData);
extern uint8 GetUartCmn_u_TxIdle(void);
extern uint8 GetUartCmn_u_RxIdle(void);
extern void Uart_Send(uint8* Data,uint8 Length);
extern void Uart_PrintStr(uint8* Str);
#endif 
