/******************************************************
文件名：	fm175xx_cfg.h

描述�	

Data			  Vasion			author
2018/1/4		  V1.0			    liujian
*******************************************************/
#ifndef		FM175XX_CFG_H
#define		FM175XX_CFG_H
/*******************************************************
description�include the header file
*******************************************************/
#include "Include.h"
#include "stm8s.h"

/*******************************************************
description�macro definitions
*******************************************************/
/**********宏开关定�********/

#define FM175XX_CFG_TEST   			0
#define FM175XX_CFG_STM8S0030F    TRUE /*��ǰʹ��Stm8s0030Fƽ̨*/

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
extern void fm17550_cfg_SpiInit(void);
extern uint8_t spi_SetReg(uint8_t ucRegAddr, uint8_t ucRegVal);
extern uint8_t spi_GetReg(uint8_t ucRegAddr);

#endif
