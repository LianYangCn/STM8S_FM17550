/******************************************************
�ļ�����	Mcu_Init.c

������		
Data			Vasion			author
2018/1/4		V1.0			liujian
*******************************************************/

/*******************************************************
description�� include the header file
*******************************************************/
#include "Mcu_Init.h"


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
//static SeMcu_Init_BaudRate;
static void Mcu_Init_GPIOConfig(void);

/******************************************************
description�� function code
******************************************************/
/******************************************************
*��������Mcu_Init

*��  �Σ�void

*����ֵ��void

*��  ����Mcu�ײ��ʼ��

*��  ע��
******************************************************/
void Mcu_Init(void)
{
	/* ʱ�ӳ�ʼ������ */
	CLK_DeInit();/*�ڲ������ʼ��*/
	CLK_HSICmd(ENABLE);/*���û�ر��ڲ�����������HSI��*/
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);/*16Mz*/
	
	/* GPIO��ʼ�� */
	Mcu_Init_GPIOConfig();
	
	FM175X_HardReset();//FM17550Ӳ��λ
	
	/* uart��ʼ�� */
	UART1_DeInit();
	UART1_Init((uint32_t)9600,UART1_WORDLENGTH_8D,UART1_STOPBITS_1,UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,UART1_MODE_TXRX_ENABLE);
    UART1->CR2 &= (uint8_t)(~0x80);/* ��ֹ���ͼĴ������ж� */
	UART1->CR2 &= (uint8_t)(~UART1_CR2_TEN);/* ��ֹ���� */
	UART1->CR2 |= (uint8_t)0x20; /* �����ж����� */
	UART1->CR2 |= (uint8_t)UART1_CR2_REN; /* ������� */
	UART1_Cmd(ENABLE);	/* Enable the UART1*/

	/* SPI��ʼ�� */
	SPI_DeInit();
	/* Initialize SPI in MASTER mode  */
	SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_HIGH,SPI_CLOCKPHASE_2EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT,(uint8_t)0x07);/*spi 4Mz*/
	SPI_Cmd(ENABLE);
	
	/* stm8s�������Ź����� */
    IWDG_Enable();//ʹ�ܿ��Ź� 
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//ͬ������������Ź�
    IWDG_SetPrescaler(IWDG_Prescaler_256);//���Ź�Ԥ��Ƶ
    IWDG_SetReload(80);//���ÿ��Ź���λʱ��320ms
    IWDG_ReloadCounter();//ι��
       
   	enableInterrupts();/*ȫ�����ж�*/
}

/*
	GPIO ����
*/
static void Mcu_Init_GPIOConfig(void)
{
	//GPIO_DeInit(GPIOA);
	//GPIO_DeInit(GPIOB);
	//GPIO_DeInit(GPIOC);
	//GPIO_DeInit(GPIOD);
	GPIO_Init(GPIOC,GPIO_PIN_3,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(GPIOC,GPIO_PIN_4,GPIO_MODE_OUT_PP_HIGH_FAST);
	//GPIO_Init(GPIOC,GPIO_PIN_5,GPIO_MODE_OUT_PP_HIGH_FAST);//spi SCK
	//GPIO_Init(GPIOC,GPIO_PIN_6,GPIO_MODE_OUT_PP_HIGH_FAST);//spi MOSI
	//GPIO_Init(GPIOC,GPIO_PIN_7,GPIO_MODE_IN_FL_NO_IT);//spi MISO
	
	GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_OUT_PP_HIGH_FAST);//uart Tx
	GPIO_Init(GPIOD,GPIO_PIN_6,GPIO_MODE_IN_FL_NO_IT);//uart Rx
	
	//GPIOC->CR2 = 0x00;
	//GPIOC->ODR = 0x18;
	//GPIOC->DDR = 0x18;
	//GPIOC->CR1 = 0x18;	
	//GPIOD->CR2 = 0x00;
	//GPIOD->ODR = 0x22;
	//GPIOD->DDR = 0x22;
	//GPIOD->CR1 = 0x62;
	
	/**************** δʹ�����Ŵ��� ****************/
	GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_IN_PU_NO_IT);//PA1 ����Ϊ��������
	GPIO_Init(GPIOA,GPIO_PIN_2,GPIO_MODE_IN_PU_NO_IT);//PA2 ����Ϊ��������
	//GPIO_Init(GPIOA,GPIO_PIN_3,GPIO_MODE_IN_PU_NO_IT);//PA3 ����Ϊ��������
	
	GPIO_Init(GPIOB,GPIO_PIN_4,GPIO_MODE_IN_PU_NO_IT);//PB4 ����Ϊ��������
	GPIO_Init(GPIOB,GPIO_PIN_5,GPIO_MODE_IN_PU_NO_IT);//PB5 ����Ϊ��������
	
	CFG->GCR = 0x01;/*��ʼ��SWD��̿�Ϊ��ͨI/O��*/
	GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_IN_PU_NO_IT);//PD1 ����Ϊ��������
	/*********************************************/	
}


/*
	���ò�����
*/
void Mcu_Init_SetBaudRtae(uint32 BaudRate)
{
	uint32 BaudRate_Mantissa = 0, BaudRate_Mantissa100 = 0;
	
	/* Clear the LSB mantissa of UART1DIV  */
	UART1->BRR1 &= (uint8)(~UART1_BRR1_DIVM);  
	/* Clear the MSB mantissa of UART1DIV  */
	UART1->BRR2 &= (uint8)(~UART1_BRR2_DIVM);  
	/* Clear the Fraction bits of UART1DIV */
	UART1->BRR2 &= (uint8)(~UART1_BRR2_DIVF);  
	/* Set the UART1 BaudRates in BRR1 and BRR2 registers according to UART1_BaudRate value */
	BaudRate_Mantissa    = ((uint32)CLK_GetClockFreq() / (BaudRate << 4));
	BaudRate_Mantissa100 = (((uint32)CLK_GetClockFreq() * 100) / (BaudRate << 4));
	/* Set the fraction of UART1DIV  */
	UART1->BRR2 |= (uint8)((uint8)(((BaudRate_Mantissa100 - (BaudRate_Mantissa * 100)) << 4) / 100) & (uint8)0x0F); 
	/* Set the MSB mantissa of UART1DIV  */
	UART1->BRR2 |= (uint8)((BaudRate_Mantissa >> 4) & (uint8)0xF0); 
	/* Set the LSB mantissa of UART1DIV  */
	UART1->BRR1 |= (uint8)BaudRate_Mantissa;	
}

