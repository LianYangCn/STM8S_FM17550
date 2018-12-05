/******************************************************
文件名：	CardRd_cfg.h

描述�	

Data			  Vasion			author
2018/1/4		  V1.0			    liujian
*******************************************************/
#ifndef		CARDRD_CFG_H
#define		CARDRD_CFG_H
/*******************************************************
description�include the header file
*******************************************************/
#include "Include.h"
#include "stm8s.h"

/*******************************************************
description�macro definitions
*******************************************************/
/**********宏开关定�********/
#define  CARDRD_DFULT_OPERATE    CardRd_e_AutoDtctn/*�ϵ�Ĭ�ϲ���*/

/**********宏常量定�********/



/***********宏函�**********/
#define CardRd_TypeA_CardActive(picc_atqa,picc_uid,uidLng,picc_sak) \
				TypeA_CardActive(picc_atqa,picc_uid,uidLng,picc_sak)

#define CardRd_Mifare_Auth(CardType,Block,PDfultKey,picc_uid,uidLng) \
				Mifare_Auth(CardType,Block,PDfultKey,picc_uid,uidLng)
#define CardRd_Mifare_Blockwrite(Block,Data) Mifare_Blockwrite(Block,Data)
#define	CardRd_Mifare_Blockread(Block,Data)  Mifare_Blockread(Block,Data)
		 
#define	CardRd_TypeB_WUP(RxBitLen,Data,PUPI) TypeB_WUP(RxBitLen,Data,PUPI)
		 
#define	CardRd_TypeB_Select(PUPI,RxBitLen,Data)  TypeB_Select(PUPI,RxBitLen,Data)
#define	CardRd_TypeB_GetUID(RxBitLen,Data) TypeB_GetUID(RxBitLen,Data)
/*******************************************************
description�struct definitions
*******************************************************/

/*******************************************************
description�typedef definitions
*******************************************************/
/*****struct definitions*****/

/******enum definitions******/
typedef enum
{
	CardRd_e_AutoDtctn = 0,/*�Զ���⿨Ƭ*/
	CardRd_e_Activate = 1,/*��Ƭ����*/
	CardRd_e_MiAuth = 2,/*��Ƭ��֤*/	
	CardRd_e_RdBlock = 3,/*��Ƭ����*/	
	CardRd_e_WrBlock = 4/*��Ƭд��*/		
}CardRdCfg_Operation;/*��Ƭ����*/
/******union definitions*****/

/*******************************************************
description�variable External declaration
*******************************************************/

/*******************************************************
description�function External declaration
*******************************************************/



#endif
