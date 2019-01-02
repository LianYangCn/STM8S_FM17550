/******************************************************
Êñá‰ª∂ÂêçÔºö	fm175xx_cfg.h

ÊèèËø∞Ôº	

Data			  Vasion			author
2018/1/4		  V1.0			    liujian
*******************************************************/
#ifndef		FM175XX_CFG_H
#define		FM175XX_CFG_H
/*******************************************************
descriptionÔºinclude the header file
*******************************************************/
#include "Include.h"
#include "stm8s.h"

/*******************************************************
descriptionÔºmacro definitions
*******************************************************/
/**********ÂÆèÂºÄÂÖ≥ÂÆö‰π********/

#define FM175XX_CFG_TEST   			0
#define FM175XX_CFG_STM8S0030F    TRUE /*µ±«∞ π”√Stm8s0030F∆ΩÃ®*/

/**********ÂÆèÂ∏∏ÈáèÂÆö‰π********/



/***********ÂÆèÂáΩÊï**********/
#define CD_ClrNPD		GPIO_WriteLow(GPIOC,GPIO_PIN_4)
#define CD_SetNPD		GPIO_WriteHigh(GPIOC,GPIO_PIN_4)


/*******************************************************
descriptionÔºstruct definitions
*******************************************************/

/*******************************************************
descriptionÔºtypedef definitions
*******************************************************/
/*****struct definitions*****/

/******enum definitions******/

/******union definitions*****/

/*******************************************************
descriptionÔºvariable External declaration
*******************************************************/

/*******************************************************
descriptionÔºfunction External declaration
*******************************************************/
extern void fm17550_cfg_SpiInit(void);
extern uint8_t spi_SetReg(uint8_t ucRegAddr, uint8_t ucRegVal);
extern uint8_t spi_GetReg(uint8_t ucRegAddr);

#endif
