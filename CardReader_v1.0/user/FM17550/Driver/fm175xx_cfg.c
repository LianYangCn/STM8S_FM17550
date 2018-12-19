/******************************************************
�ļ�����	fm175xx_cfg.c

������		
Data			Vasion			author
2018/1/4		V1.0			liujian
*******************************************************/

/*******************************************************
description�� include the header file
*******************************************************/
#include "fm175xx_cfg.h"


/*******************************************************
description�� global variable definitions
*******************************************************/


/*******************************************************
description�� static variable definitions
*******************************************************/


/*******************************************************
description�� function declaration
*******************************************************/
/*Global function declaration*/


/*Static function declaration*/


/*********************************************************************************************************
** �������ƣ�fm17550_cfg_SpiInit
** ����������SPI��ʼ��
** �����������
** ����ֵ  ����
*********************************************************************************************************/
void fm17550_cfg_SpiInit(void)
{
	//SPI_DeInit();
	//SPI_Init();
}

/*********************************************************************************************************
** �������ƣ�spi_SetReg
** ����������
** �����������
** ����ֵ  ��
** ˵����
*********************************************************************************************************/
uint8_t spi_SetReg(uint8_t ucRegAddr, uint8_t ucRegVal)
{
#if(TRUE == FM175XX_CFG_STM8S0030F)
	uint8_t ucReturnVal;
	Delay100us(5);
	GPIO_WriteLow(GPIOC, GPIO_PIN_3);  //!< SPI ͨ��NSS ʹ�ܣ����㣩
	ucReturnVal = SPI_ReceiveData();//�����ȶ�ȡһ��,��ֹ���ջ����д�������  
	while(!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x02));
	SPI_SendData((ucRegAddr << 1));
	while (!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x01));
	ucReturnVal = SPI_ReceiveData();
 
	while(!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x02));
	SPI_SendData(ucRegVal);
	while (!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x01));
	ucReturnVal = SPI_ReceiveData();
	GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //!< SPI ͨ��NSS ��ֹ����λ�� 
    return ucReturnVal;
 #endif
}

uint8_t spi_GetReg(uint8_t ucRegAddr)
{
#if(TRUE == FM175XX_CFG_STM8S0030F)
    unsigned char ucRegVal;
	Delay100us(5);
	GPIO_WriteLow(GPIOC, GPIO_PIN_3);  //!< SPI ͨ��NSS ʹ�ܣ����㣩
	ucRegVal = SPI_ReceiveData();//�����ȶ�ȡһ��,��ֹ���ջ����д�������  
	while(!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x02));
	SPI_SendData((0x80|(ucRegAddr << 1)));
	while (!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x01));
	ucRegVal = SPI_ReceiveData();

	while(!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x02));
	SPI_SendData(0x00);
	while (!SPI_GetFlagStatus((SPI_Flag_TypeDef)0x01));
	ucRegVal = SPI_ReceiveData();
	GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //!< SPI ͨ��NSS ��ֹ����λ�� 
    return ucRegVal;
#endif
}
