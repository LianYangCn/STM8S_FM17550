/******************************************************
æ–‡ä»¶åï¼š	fm175xx_cfg.h

æè¿°ï¼	

Data			  Vasion			author
2018/1/4		  V1.0			    liujian
*******************************************************/
#ifndef		FM175XX_CFG_H
#define		FM175XX_CFG_H
/*******************************************************
descriptionï¼include the header file
*******************************************************/
#include "Include.h"
#include "stm8s.h"

/*******************************************************
descriptionï¼macro definitions
*******************************************************/
/**********å®å¼€å…³å®šä¹********/

#define FM175XX_CFG_TEST   			0
#define FM175XX_CFG_STM8S0030F    TRUE /*µ±Ç°Ê¹ÓÃStm8s0030FÆ½Ì¨*/

/**********å®å¸¸é‡å®šä¹********/



/***********å®å‡½æ•**********/

/*******************************************************
descriptionï¼struct definitions
*******************************************************/

/*******************************************************
descriptionï¼typedef definitions
*******************************************************/
/*****struct definitions*****/

/******enum definitions******/

/******union definitions*****/

/*******************************************************
descriptionï¼variable External declaration
*******************************************************/

/*******************************************************
descriptionï¼function External declaration
*******************************************************/
extern void fm17550_cfg_SpiInit(void);
extern uint8_t spi_SetReg(uint8_t ucRegAddr, uint8_t ucRegVal);
extern uint8_t spi_GetReg(uint8_t ucRegAddr);

#endif
