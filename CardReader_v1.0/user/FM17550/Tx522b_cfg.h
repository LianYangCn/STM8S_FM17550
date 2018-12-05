/******************************************************
�ļ�����	TX522B.h

������	ȫ˫������ͨ��	

Data			  Vasion			author
2018/01/10		   V1.0			    liujian
*******************************************************/
#ifndef		_TX522B_CFG_H
#define		_TX522B_CFG_H
/*******************************************************
description�� include the header file
*******************************************************/
#include "Include.h"

/*******************************************************
description�� macro definitions
*******************************************************/
/**********�꿪�ض���*********/

/**********�곣������*********/
#define TXBUFF_NUM    3U

#define TX522B_OK    			1U
#define TX522B_BUFF_OVERFLOW    2U


/*TX522B �⺯��״ֵ̬�б�*/

/***********�꺯��***********/

#define TX522B_LED_ON		GPIO_WriteLow(GPIOD, GPIO_PIN_1)  //��LED
#define TX522B_LED_OFF  	GPIO_WriteHigh(GPIOD, GPIO_PIN_1)  //��LED
/*******************************************************
description�� struct definitions
*******************************************************/

/*******************************************************
description�� typedef definitions
*******************************************************/
/*****struct definitions*****/

/******enum definitions******/
typedef enum 
{
	Tx522bCfg_AutoDectFlg = 0U,/*��Ƭ�Զ�����־ֵ*/
	Tx522bCfg_Key = 1U,/*��Կ*/
	Tx522bCfg_BaudRate = 2U/*���ڲ�����*/
}Tx522bCfg_StrgObject;
/******union definitions*****/

/*******************************************************
description�� variable External declaration
*******************************************************/

/*******************************************************
description�� function External declaration
*******************************************************/
extern uint8 GetTx522bCfg_u_RxMsgRenew(void);
extern void  GetTx522bCfg_u_RxMsg(uint8* Le_u_RxData);
extern uint8 Tx522bCfg_WriteEE(uint8 Object,uint8* Le_u_Data,uint8 Le_u_Lng);
extern uint8 Tx522bCfg_ReadEE(uint8 Object,uint8* Le_u_Data,uint8 Le_u_Lng);
extern void  SetTx522bCfg_TxMsg(uint8* Le_u_TxData,uint8 Le_u_Lng);
extern uint8 GetTx522bCfg_u_BlockData(uint8 Le_u_Block,uint8 *Le_u_Data);
extern uint8 GetTx522bCfg_u_ACardSnr(uint8 ReqCode, uint8  *TagType, uint8  *Sak,uint8  *SnrLen, uint8  *Snr);
extern uint8 GetTx522bCfg_u_BCardSnr( uint8  *Snr,uint8 *SnrLen);
extern uint8 Tx522bCfg_u_WriteBlock(uint8 Block,uint8 *Data);
extern uint8 GetTx522bCfg_u_TxIdle(void);
extern void SetTx522bCfg_BaudRtae(uint32 BaudRate);
#endif 
