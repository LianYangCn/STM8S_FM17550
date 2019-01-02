/******************************************************
文件名：	Mcu_Init.c

描述：		
Data			Vasion			author
2018/1/4		V1.0			liujian
*******************************************************/

/*******************************************************
description： include the header file
*******************************************************/
#include "Mcu_Init.h"


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
//static SeMcu_Init_BaudRate;
static void Mcu_Init_GPIOConfig(void);

/******************************************************
description： function code
******************************************************/
/******************************************************
*函数名：Mcu_Init

*形  参：void

*返回值：void

*描  述：Mcu底层初始化

*备  注：
******************************************************/
void Mcu_Init(void)
{
	/* 时钟初始化配置 */
	CLK_DeInit();/*内部晶振初始化*/
	CLK_HSICmd(ENABLE);/*启用或关闭内部高速振荡器（HSI）*/
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);/*16Mz*/
	
	/* GPIO初始化 */
	Mcu_Init_GPIOConfig();
	
	FM175X_HardReset();//FM17550硬复位
	
	/* uart初始化 */
	UART1_DeInit();
	UART1_Init((uint32_t)9600,UART1_WORDLENGTH_8D,UART1_STOPBITS_1,UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,UART1_MODE_TXRX_ENABLE);
    UART1->CR2 &= (uint8_t)(~0x80);/* 禁止发送寄存器空中断 */
	UART1->CR2 &= (uint8_t)(~UART1_CR2_TEN);/* 禁止发送 */
	UART1->CR2 |= (uint8_t)0x20; /* 接收中断请求 */
	UART1->CR2 |= (uint8_t)UART1_CR2_REN; /* 允许接收 */
	UART1_Cmd(ENABLE);	/* Enable the UART1*/

	/* SPI初始化 */
	SPI_DeInit();
	/* Initialize SPI in MASTER mode  */
	SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_HIGH,SPI_CLOCKPHASE_2EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT,(uint8_t)0x07);/*spi 4Mz*/
	SPI_Cmd(ENABLE);
	
	/* stm8s独立看门狗配置 */
    IWDG_Enable();//使能看门狗 
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//同意操作独立看门狗
    IWDG_SetPrescaler(IWDG_Prescaler_256);//看门狗预分频
    IWDG_SetReload(80);//设置看门狗复位时间320ms
    IWDG_ReloadCounter();//喂狗
       
   	enableInterrupts();/*全局总中断*/
}

/*
	GPIO 配置
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
	
	/**************** 未使用引脚处理 ****************/
	GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_IN_PU_NO_IT);//PA1 设置为上拉输入
	GPIO_Init(GPIOA,GPIO_PIN_2,GPIO_MODE_IN_PU_NO_IT);//PA2 设置为上拉输入
	//GPIO_Init(GPIOA,GPIO_PIN_3,GPIO_MODE_IN_PU_NO_IT);//PA3 设置为上拉输入
	
	GPIO_Init(GPIOB,GPIO_PIN_4,GPIO_MODE_IN_PU_NO_IT);//PB4 设置为上拉输入
	GPIO_Init(GPIOB,GPIO_PIN_5,GPIO_MODE_IN_PU_NO_IT);//PB5 设置为上拉输入
	
	CFG->GCR = 0x01;/*初始化SWD编程口为普通I/O口*/
	GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_IN_PU_NO_IT);//PD1 设置为上拉输入
	/*********************************************/	
}


/*
	设置波特率
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

