 #include "fm175xx.h"
// #include "des.h"
 #include "cpu_card.h"
// #include "main.h"
// #include <string.h>
 unsigned char  PCB,CID;
  
 
/****************************************************************/
/*名称: Rats 													*/
/*功能: 该函数实现转入APDU命令格式处理	CPU card reset			*/
/*输入: param1 byte :PCB 									    */
/*		param2 byte bit8-bit5：FSDI, bit4-bit0 ：CID  			*/
/*输出:															*/
/*		rece_len：接收的数据长度								*/
/*		buff：接收的数据指针									*/
/* OK: 应答正确													*/
/* ERROR: 应答错误												*/
/****************************************************************/
unsigned char CPU_Rats(unsigned char param1,unsigned char param2,unsigned char *rece_len,unsigned char *buff)
{
	unsigned char  ret,send_byte[2];
	unsigned int  rece_bitlen;
	Pcd_SetTimer(100);
	send_byte[0] = 0xE0;//Start byte
	send_byte[1] = param2;
	CID = param2 & 0x0f;
    PCB = param1;
	Clear_FIFO();
	ret=Pcd_Comm(Transceive,send_byte,2,buff,&rece_bitlen);
	if (ret==OK)
		*rece_len=rece_bitlen/8;
	else
		*rece_len=0;
	return ret;	
}
/****************************************************************/
/*名称: PPS 													*/
/*功能: 														*/
/*输入: PPSS byte, PPS0 byte, PPS1 byte							*/
/*输出:															*/
/*		rece_len：接收的数据长度								*/
/*		buff：接收的数据指针									*/
/* OK: 应答正确													*/
/* ERROR: 应答错误												*/
/****************************************************************/
unsigned char CPU_PPS(unsigned char pps0,unsigned char pps1,unsigned char *rece_len,unsigned char *buff)
{
	unsigned char data ret,send_byte[3];
	unsigned int data rece_bitlen;
	Pcd_SetTimer(50);
	send_byte[0] = 0xD0|CID;//ppss byte
	send_byte[1] = pps0;	//pps0 byte
	Clear_FIFO();
	if ((pps0&0x10)==0x10)
	{
		send_byte[2]=pps1; 	//pps1 byte
		ret = Pcd_Comm(Transceive,send_byte,3,buff,&rece_bitlen );
	}
	else
	{	
		ret = Pcd_Comm(Transceive,send_byte,2,buff,&rece_bitlen );
	}
	if (ret==OK)
		*rece_len=rece_bitlen/8;
	else
		*rece_len=0;
	return ret;	
}

void CPU_PCB(void)
{
//PCB bit0=~(bit0)
	PCB=PCB^0x01;//设置块号变换
return;
}
/****************************************************************/
/*名称: 随机数													*/
/*功能: 														*/
/*输入: N/A 													*/
/*输出:															*/
/*		rece_len：接收的数据长度								*/
/*		buff：接收的数据指针									*/
/* 		OK: 应答正确											*/
/* 		ERROR: 应答错误											*/
/****************************************************************/
unsigned char CPU_Random(unsigned char *rece_len,unsigned char *buff)
{
	unsigned char data ret,send_byte[5];
	memcpy(send_byte,"\x00\x84\x00\x00\x08",5);
	ret=CPU_I_Block(5,send_byte,&(*rece_len),buff);
	return ret;	
}
/****************************************************************/
/*名称: 外部认证												*/
/*功能: 														*/
/*输入: N/A 													*/
/*输出:															*/
/* OK: 应答正确													*/
/* ERROR: 应答错误												*/
/****************************************************************/
//unsigned char CPU_auth(unsigned char *key_buff,unsigned char *rece_len,unsigned char *buff)
//{
//	unsigned char i,ret,send_byte[15],rece_byte[16],Random_data[8],des_buff[8],temp;
//
//	ret=CPU_random(&temp,rece_byte);
//	if (ret==ERROR)
//		return ret;
//	for (i=0;i<4;i++)
//	Random_data[i]=rece_byte[i+2];
//	for (i=4;i<8;i++)
//	Random_data[i]=0;
//	Tdes(ENCRY,Random_data,key_buff,des_buff);
//	//CPU_PCB();
//	//send_byte[0] = PCB;
//	//send_byte[1] = CID;
//	send_byte[0] = 0x00;
//	send_byte[1] = 0x82;
//	send_byte[2] = 0x00;
//	send_byte[3] = 0x00;
//	send_byte[4] = 0x08;
//	for(i=0;i<8;i++)
//	send_byte[i+5]= des_buff[i];
//	ret=CPU_command(1,13,send_byte,&(*rece_len),buff);
//	return ret;	
//	
//}
/****************************************************************/
/*名称: CPU_command 	cpu card operation						*/
/*功能: CPU命令操作												*/
/*输入:															*/
/*																*/
/*		send_len:发送的指令长度 								*/
/*		send_buff:发送的指令数据指针	 						*/
/*																*/
/*输出:响应长度													*/
/*		rece_len：接收的数据长度								*/
/*		rece_buff：接收的数据指针								*/
/* 		OK: 应答正确											*/
/* 		ERROR: 应答错误											*/
/****************************************************************/
unsigned char CPU_TPDU(unsigned char send_len,unsigned char *send_buff,unsigned char *rece_len,unsigned char *rece_buff)
{	unsigned char data ret;
	unsigned int data rece_bitlen;

	Pcd_SetTimer(100);
	ret=Pcd_Comm(Transceive,send_buff,send_len,rece_buff,&rece_bitlen);
	if (ret==OK)
			*rece_len=rece_bitlen/8;
		else
			*rece_len=0;
	return ret;
}
/****************************************************************/
/*名称: I Block 	cpu card operation							*/
/*功能: CPU命令操作(I block)									*/
/*输入:															*/
/*																*/
/*		send_len:发送的指令长度 								*/
/*		send_buff:发送的指令数据指针	 						*/
/*																*/
/*输出:响应长度													*/
/*		rece_len：接收的数据长度								*/
/*		rece_buff：接收的数据指针								*/
/* 		OK: 应答正确											*/
/* 		ERROR: 应答错误											*/
/****************************************************************/
 unsigned char CPU_I_Block(unsigned char send_len,unsigned char *send_buff,unsigned char *rece_len,unsigned char *rece_buff)
 {
		unsigned char data ret;
		unsigned int data rece_bitlen;
		Pcd_SetTimer(500);
		Clear_FIFO();
 		if (PCB&0x08)//判断是否有CID字节
		{
			Write_FIFO(1,&PCB);
			Write_FIFO(1,&CID);
		}
		else
		{
			Write_FIFO(1,&PCB);
		}
		ret=Pcd_Comm(Transceive,send_buff,send_len,rece_buff,&rece_bitlen);
		if (ret==OK)
		{
			PCB=*rece_buff;
			CPU_PCB();
			*rece_len=rece_bitlen/(unsigned int)8;
		}
		else
			*rece_len=0;
		return ret;
 }
/****************************************************************/
/*名称: R Block 	cpu card operation							*/
/*功能: CPU命令操作(R block)									*/
/*输入:															*/
/*																*/
/*																*/
/*输出:响应长度													*/
/*		rece_len：接收的数据长度								*/
/*		rece_buff：接收的数据指针								*/
/* 		OK: 应答正确											*/
/* 		ERROR: 应答错误											*/
/****************************************************************/

 unsigned char CPU_R_Block(unsigned char *rece_len,unsigned char *rece_buff)
 {
 	unsigned char data send_buff[2],ret;
	unsigned int data rece_bitlen;
	Pcd_SetTimer(100);
	Clear_FIFO();
	if (PCB&0x08)//判断是否有CID字节
		{
  		send_buff[0] = (PCB&0x0F)|0xA0;
		send_buff[1] = CID;
		ret=Pcd_Comm(Transceive,send_buff,2,rece_buff,&rece_bitlen);
		}
	else
		{
		send_buff[0] = (PCB&0x0F)|0xA0;
		ret=Pcd_Comm(Transceive,send_buff,1,rece_buff,&rece_bitlen);
		}
	if (ret==OK)
		{
			PCB=*rece_buff;
			CPU_PCB();
			*rece_len=rece_bitlen/8;
		}
	else
			*rece_len=0;
	return ret;
 }
/****************************************************************/
/*名称: S Block 	cpu card operation							*/
/*功能: CPU命令操作(S block)									*/
/*输入:															*/
/*																*/
/*		pcb_byte:设置PCB字节									*/
/*																*/
/*输出:响应长度													*/
/*		rece_len：接收的数据长度								*/
/*		rece_buff：接收的数据指针								*/
/* 		OK: 应答正确											*/
/* 		ERROR: 应答错误											*/
/****************************************************************/
 unsigned char CPU_S_Block(unsigned char pcb_byte,unsigned char *rece_len,unsigned char *rece_buff)
 {
   unsigned char data send_buff[3],ret;
   unsigned int data rece_bitlen;
   Pcd_SetTimer(500);
   Clear_FIFO();
   send_buff[0] =0xC0|pcb_byte;

   if ((PCB&0x08)==0x08)//判断是否有CID字节
   {
	   if ((pcb_byte&0xF0)==0xF0) //WTX
	   {
		  	send_buff[1] = CID;
			send_buff[2] = 0x01;
			ret=Pcd_Comm(Transceive,send_buff,3,rece_buff,&rece_bitlen);
		}
		else  //DESELECT
		{
			send_buff[1] = CID;
			ret=Pcd_Comm(Transceive,send_buff,2,rece_buff,&rece_bitlen);
		}
	}
	else
	{
		if ((pcb_byte&0xF0)==0xF0) //WTX
	   {
		  	send_buff[1] = 0x01;
			ret=Pcd_Comm(Transceive,send_buff,2,rece_buff,&rece_bitlen);
		}
		else   //DESELECT
		{
			send_buff[1] = 0x00;
			ret=Pcd_Comm(Transceive,send_buff,2,rece_buff,&rece_bitlen);
		}
	}
	if (ret==OK)
		{
			PCB=*rece_buff;
			CPU_PCB();
			*rece_len=rece_bitlen/8;
		}
	else
			*rece_len=0;
	return ret;
 }

/****************************************************************/
/*名称: CPU_baud_rate_change									*/
/*功能: 调整通信波特率											*/
/*输入:															*/
/*		mode=0 接收发送波特率106kbps							*/
/*		mode=1 接收发送波特率212kbps							*/
/*		mode=2 接收发送波特率424kbps	 						*/
/*																*/
/*输出:响应长度													*/
/* 		OK: 应答正确											*/
/* 		ERROR: 应答错误											*/
/****************************************************************/
unsigned char CPU_BaudRate_Set(unsigned char mode) //mode=0:106Kbps;1:212Kpbs;2:424Kpbs
{
	Clear_BitMask(TxModeReg,0x70);
	Clear_BitMask(RxModeReg,0x70);
  switch (mode)
  {
  case 0:	  //106kbps
 		Set_BitMask(TxModeReg,0x00);
		Set_BitMask(RxModeReg,0x00);
		break;
  case 1:	  //212kbps
		Set_BitMask(TxModeReg,0x10);
		Set_BitMask(RxModeReg,0x10);
		break;
  case 2:	  //424kbps
		Set_BitMask(TxModeReg,0x20);
		Set_BitMask(RxModeReg,0x20);
		break;
  case 3:	  //848kbps
		Set_BitMask(TxModeReg,0x30);
		Set_BitMask(RxModeReg,0x30);
		break;
  }
return OK;
}

