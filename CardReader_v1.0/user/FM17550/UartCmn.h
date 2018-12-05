/******************************************************
�ļ�����	UartCmn

������	��˫������ͨ��	

Data			  Vasion			author
2018/01/10		   V1.0			    liujian
*******************************************************/
#ifndef		_UARTCMN_H
#define		_UARTCMN_H
/*******************************************************
description�� include the header file
*******************************************************/
#include "Include.h"

/*******************************************************
description�� macro definitions
*******************************************************/
/**********�꿪�ض���*********/

/**********�곣������*********/
/*���պ궨��*/
/*TX522BЭ��֡*/
#define   UARTCMN_RX_HEADER    	    	0x20/*���ձ���ͷ��ʼ��*/
#define   UARTCMN_RX_PCKTHEAD_LNG       1U/*����ͷ���ȣ���λ���ֽڣ�*/

#define   UARTCMN_RX_PCKTHEAD_SEQNR     1U/*���ĺų��ȣ���λ���ֽڣ�*/
#define   UARTCMN_RX_PCKTHEAD_CMD     	1U/*���������֣���λ���ֽڣ�*/
#define   UARTCMN_RX_DATALNG_LNG        1U/*��Ч���ݳ��ȱ�ʾ�ֽ�:�ޣ�����0*/
#define   UARTCMN_RX_PCKTDATA_LNG       56U/*������Ч������󳤶�*/
#define   UARTCMN_RX_CHECK_LNG          1U/*����У���ֽڳ���*/
#define   UARTCMN_RX_ETX_LNG            1U/*���Ľ����ֽڳ���*/
#define   UARTCMN_RX_ETC    	    	0x03/*���ձ�����ֹ��*/


#define   UARTCMN_RX_SEQNR_STRTBYTE		UARTCMN_RX_PCKTHEAD_LNG 
#define   UARTCMN_RX_DATALNG_STRTBYTE	(UARTCMN_RX_PCKTHEAD_LNG + UARTCMN_RX_PCKTHEAD_SEQNR + UARTCMN_RX_PCKTHEAD_CMD)/*������Ч���ݳ��ȱ�ʾ�ֽڿ�ʼ�ֽ�*/
#define   UARTCMN_RX_DATA_STRTBYTE      (UARTCMN_RX_PCKTHEAD_LNG + UARTCMN_RX_PCKTHEAD_SEQNR + UARTCMN_RX_PCKTHEAD_CMD + UARTCMN_RX_DATALNG_LNG)/*������Ч���ݿ�ʼ�ֽ�*/
#define   UARTCMN_RX_CHCK_STRTBYTE      (UARTCMN_RX_PCKTHEAD_LNG + UARTCMN_RX_PCKTHEAD_SEQNR + UARTCMN_RX_PCKTHEAD_CMD + UARTCMN_RX_DATALNG_LNG + UARTCMN_RX_PCKTDATA_LNG)     /*����У���ֽ���ʼλ*/
#define   UARTCMN_RX_SCLD_LNG           (UARTCMN_RX_PCKTHEAD_SEQNR + UARTCMN_RX_PCKTHEAD_CMD +UARTCMN_RX_DATALNG_LNG + UARTCMN_RX_PCKTDATA_LNG)/*����+����+��Ч���ݳ����ֽ�+��Ч����*/
#define   UARTCMN_RX_PCKT_LNG           (UARTCMN_RX_CHCK_STRTBYTE + UARTCMN_RX_CHECK_LNG + UARTCMN_RX_ETX_LNG)/*�����ܳ�*/
/*���ͺ궨��*/
#define   UARTCMN_TX_HEADER    	    	0x20/*����ͷ��ʼ��*/
#define   UARTCMN_TX_ETC    	    	0x03/*������ֹ��*/
#define   UARTCMN_TX_PCKT_LNG           62U/*���ͱ����ܳ���󳤶�*/




/*SCIͨ������*/





/***********�꺯��***********/
#define  DISABLE_TIEN       (UART1->CR2 &= (uint8_t)(~0x80))/* ��ֹ���ͼĴ������ж� */
#define  ENABLE_TIEN	 	(UART1->CR2 |= (uint8_t)0x80)/* ʹ�ܷ��ͼĴ������ж� */	

#define  DISABLE_TEN    	(UART1->CR2 &= (uint8_t)(~UART1_CR2_TEN))/* ��ֹ���� */
#define  ENABLE_TEN		    (UART1->CR2 |= (uint8_t)UART1_CR2_TEN) /* ������ */

#define	 ENABLE_RIEN    	(UART1->CR2 |= (uint8_t)0x20) /* ʹ�ܽ����ж����� */
#define	 DISABLE_RIEN		(UART1->CR2 &= (uint8_t)(~0x20))/* �رս����ж����� */

#define	 ENABLE_REN			(UART1->CR2 |= (uint8_t)UART1_CR2_REN) /* ������� */	
#define  DISABLE_REN		(UART1->CR2 &= (uint8_t)(~UART1_CR2_REN)) /* ��ֹ���� */


/*******************************************************
description�� struct definitions
*******************************************************/

/*******************************************************
description�� typedef definitions
*******************************************************/
/*****struct definitions*****/
typedef struct 
{		
	unsigned char UartRxNm;/* ���������±� */
	unsigned char UartRXFlag;/* ������ɱ�־ */ 
	unsigned char RxBusyFlg;/* ���Ľ���æ��־ */
	unsigned char UartHeaderFlag;/* ��ͷ������ɱ�־ */
	unsigned char UartNewFlag;/* ���ܵ������ݱ�־ */
	union
	{
		unsigned char UartPckt[UARTCMN_RX_PCKT_LNG];/* �����ܳ�������ͷ+����+У��+֡���� */
		struct
		{
			unsigned char UartHeader[UARTCMN_RX_PCKTHEAD_LNG];/* ���ձ�ͷ */
			unsigned char UartSeqnr[UARTCMN_RX_PCKTHEAD_SEQNR];/* ����֡����*/
			unsigned char UartCmd[UARTCMN_RX_PCKTHEAD_CMD];/* ����֡����*/
			unsigned char UartRxDataLng[UARTCMN_RX_DATALNG_LNG];/* ������Ч���ݶγ��ȱ�ʾ*/
			unsigned char UartRxData[UARTCMN_RX_PCKTDATA_LNG];/* ���յ���Ч���ݶΣ�����󳤶ȶ���洢�ռ�*/
			unsigned char UartCheck[UARTCMN_RX_CHECK_LNG];/* ���ռ����ֽ� */
			unsigned char UartETX[UARTCMN_RX_ETX_LNG];/* ֡����*/
		}Pckt;
	}UartRx;
}Uart_Rx_Msg; /*���Ľ��սṹ��*/ 

typedef struct
{
    uint8  ucTxData[UARTCMN_TX_PCKT_LNG];/* ���ͱ��Ļ��� */
    uint8  ucLength;/* ���ĳ��� */
    uint8  ucTxCnt;/*���ͼ���*/
	uint8  ucTxFlg;/*���ͱ�־��1����������Ҫ�����ڷ��ͣ�0����û�����ݷ���*/
}Uart_TX_Msg;/*���ķ��ͽṹ��*/

/******enum definitions******/

/******union definitions*****/

/*******************************************************
description�� variable External declaration
*******************************************************/

/*******************************************************
description�� function External declaration
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
