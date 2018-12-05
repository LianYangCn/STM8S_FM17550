/******************************************************
文件名：	CardRd.h

描述�	

Data			  Vasion			author
2018/1/4		  V1.0			    liujian
*******************************************************/
#ifndef		CARDRD_H
#define		CARDRD_H
/*******************************************************
description�include the header file
*******************************************************/
#include "CardRd_cfg.h"


/*******************************************************
description�macro definitions
*******************************************************/
/**********宏开关定�********/
#define CARD_RD_TEST     0

/**********宏常量定�********/



/***********宏函�**********/

/*******************************************************
description�struct definitions
*******************************************************/

/*******************************************************
description�typedef definitions
*******************************************************/
/*****struct definitions*****/

/******enum definitions******/

/******union definitions*****/

/*******************************************************
description�variable External declaration
*******************************************************/
extern unsigned char  SaCardRd_u_PDfultKey[6];
/*******************************************************
description�function External declaration
*******************************************************/
extern void  CardRd_Init(void);
extern void  CardRd_MainFunction(void);
extern void  SetCardRd_CardOperation(uint8_t LeCardRd_u_Oprt);
extern uint8_t GetCardRd_CardOperation(void);
extern uint8_t GetCardRd_u_BlockData(uint8_t LeCardRd_u_Block,uint8_t* LaCardRd_u_Data);
extern uint8_t RdCardRd_u_MiCard_TyteA(uint8_t ReqCode, uint8_t  *TagType, uint8_t  *Sak,uint8_t  *SnrLen, uint8_t  *Snr);
extern uint8_t WrCardRd_MiCard_TyteA(uint8_t Block,uint8_t *Data);
extern uint8_t RdCardRd_u_Card_TyteB(uint8_t* Le_u_Data,uint8_t* Le_u_Lng);


#endif
