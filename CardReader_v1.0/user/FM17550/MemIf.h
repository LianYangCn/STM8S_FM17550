/******************************************************
文件名：	MemIf.h

描述�	

Data			  Vasion			author
2018/1/13		  V1.0			    liujian
*******************************************************/
#ifndef		MEMIF_H
#define		MEMIF_H
/*******************************************************
description�include the header file
*******************************************************/
#include "MemIf_cfg.h"


/*******************************************************
description�macro definitions
*******************************************************/
/**********宏开关定�********/

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

/*******************************************************
description�function External declaration
*******************************************************/
extern uint8 MemIf_ReadEE(uint8 Le_u_Object,uint8* Le_u_Data,uint8 Le_u_Lng);
extern uint8 MemIf_WriteEE(uint8 Le_u_Object,uint8* Le_u_Data,uint8 Le_u_Lng);

#endif
