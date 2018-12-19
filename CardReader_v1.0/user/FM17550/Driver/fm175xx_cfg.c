/******************************************************
文件名：	fm175xx_cfg.c

描述：		
Data			Vasion			author
2018/1/4		V1.0			liujian
*******************************************************/

/*******************************************************
description： include the header file
*******************************************************/
#include "fm175xx_cfg.h"


/*******************************************************
description： global variable definitions
*******************************************************/


/*******************************************************
description： static variable definitions
*******************************************************/


/*******************************************************
description： function declaration
*******************************************************/
/*Global function declaration*/


/*Static function declaration*/


/*********************************************************************************************************
** 函数名称：fm17550_cfg_SpiInit
** 函数描述：SPI初始化
** 输入参数：无
** 返回值  ：无
*********************************************************************************************************/
void fm17550_cfg_SpiInit(void)
{
	//SPI_DeInit();
	//SPI_Init();
}

/*********************************************************************************************************
** 函数名称：spi_SetReg
** 函数描述：
** 输入参数：无
** 返回值  ：
** 说明：
*********************************************************************************************************/
uint8_t spi_SetReg(uint8_t ucRegAddr, uint8_t ucRegVal)
{
#if(TRUE == FM175XX_CFG_STM8S0030F)
	uint8_t ucReturnVal;
	Delay100us(5);
	GPIO_WriteLow(GPIOC, GPIO_PIN_3);  //!< SPI 通信NSS 使能（清零）
	ucReturnVal = SPI_ReceiveData();//必须先读取一下,防止接收缓存中存有数据  
	while(!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x02));
	SPI_SendData((ucRegAddr << 1));
	while (!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x01));
	ucReturnVal = SPI_ReceiveData();
 
	while(!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x02));
	SPI_SendData(ucRegVal);
	while (!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x01));
	ucReturnVal = SPI_ReceiveData();
	GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //!< SPI 通信NSS 禁止（置位） 
    return ucReturnVal;
 #endif
}

uint8_t spi_GetReg(uint8_t ucRegAddr)
{
#if(TRUE == FM175XX_CFG_STM8S0030F)
    unsigned char ucRegVal;
	Delay100us(5);
	GPIO_WriteLow(GPIOC, GPIO_PIN_3);  //!< SPI 通信NSS 使能（清零）
	ucRegVal = SPI_ReceiveData();//必须先读取一下,防止接收缓存中存有数据  
	while(!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x02));
	SPI_SendData((0x80|(ucRegAddr << 1)));
	while (!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x01));
	ucRegVal = SPI_ReceiveData();

	while(!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x02));
	SPI_SendData(0x00);
	while (!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x01));
	ucRegVal = SPI_ReceiveData();
	GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //!< SPI 通信NSS 禁止（置位） 
    return ucRegVal;
#endif
}
