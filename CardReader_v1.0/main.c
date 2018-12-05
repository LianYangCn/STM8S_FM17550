/*************************************************************/
//2014.06.03修改版
/*===========================================================*/
#include "Include.h"

//unsigned char   system_info[] = "FM17520 READER IC LPC1114/301 DEMO V1.0 2018/01/05";


//__root const uint8 SoftwareNewFlag@0x9FFF = 0x55;//参数放入指定地址rom

//__root static uint8 stuckTest@0x02AE = 0x55;//参数放入指定地址ram
/*****************************************************************************
*****************************************************************************/
int main(void)
{
 #if(1 == FM175XX_CFG_TEST)
	unsigned char statues;
#endif	
	Mcu_Init();
	InitUartCmn_parameter();
    InitTx522b_parameter();
	Delay100us(50);/*Stm8s0030f 16MZ晶振下大概100us*/
#if(1 == FM175XX_CFG_TEST)	                      
	statues = MCU_TO_PCD_TEST();	  //MCU与读卡芯片SPI通信测试，这里面做了寄存器读写测试 
	if(statues == 1)
	{
		Uart_PrintStr("Mcu to pcd test ok\n");
	}
#endif
	while(1)
	{
		Tx522b_MainFunction();
        IWDG_ReloadCounter();//喂狗 
	}
}






