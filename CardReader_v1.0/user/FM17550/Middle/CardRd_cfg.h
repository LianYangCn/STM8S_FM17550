/******************************************************
æ–‡ä»¶åï¼š	CardRd_cfg.h

æè¿°ï¼	

Data			  Vasion			author
2018/1/4		  V1.0			    liujian
*******************************************************/
#ifndef		CARDRD_CFG_H
#define		CARDRD_CFG_H
/*******************************************************
descriptionï¼include the header file
*******************************************************/
#include "Include.h"
#include "stm8s.h"

/*******************************************************
descriptionï¼macro definitions
*******************************************************/
/**********å®å¼€å…³å®šä¹********/
#define  CARDRD_DFULT_OPERATE    CardRd_e_AutoDtctn/*ÉÏµçÄ¬ÈÏ²Ù×÷*/

/**********å®å¸¸é‡å®šä¹********/



/***********å®å‡½æ•**********/
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
descriptionï¼struct definitions
*******************************************************/

/*******************************************************
descriptionï¼typedef definitions
*******************************************************/
/*****struct definitions*****/

/******enum definitions******/
typedef enum
{
	CardRd_e_AutoDtctn = 0,/*×Ô¶¯¼ì²â¿¨Æ¬*/
	CardRd_e_Activate = 1,/*¿¨Æ¬¼¤»î*/
	CardRd_e_MiAuth = 2,/*¿¨Æ¬ÈÏÖ¤*/	
	CardRd_e_RdBlock = 3,/*¿¨Æ¬¶Á¿é*/	
	CardRd_e_WrBlock = 4/*¿¨Æ¬Ğ´¿é*/		
}CardRdCfg_Operation;/*¿¨Æ¬²Ù×÷*/
/******union definitions*****/

/*******************************************************
descriptionï¼variable External declaration
*******************************************************/

/*******************************************************
descriptionï¼function External declaration
*******************************************************/



#endif
