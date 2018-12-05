//#include "at89x52.h"
//#include "intrins.h"

//#include "fm17xx.h"
#include "15693.h"
//#include "main.h"
//#include "uart.h"
 unsigned char rfid[8];
 unsigned char ISO15693_Init(void);
 unsigned char ISO15693_Stayquite(void);
 unsigned char ISO15693_Inventory(unsigned char *rece_len,unsigned char *buff,unsigned char *card_uid,unsigned char *slot_num);
 unsigned char ISO15693_Select(unsigned char *card_uid,unsigned char *rece_len,unsigned char *buff);
 unsigned char ISO15693_Read(unsigned char block,unsigned char *rece_len,unsigned char *buff);
 unsigned char ISO15693_Write(unsigned char card_type,unsigned char block, unsigned char *block_data,unsigned char *rece_len,unsigned char *buff);
 unsigned char ISO15693_Getinfo(unsigned char *rece_len,unsigned char *buff);
 unsigned char ISO15693_Inventory_16slot(unsigned char *card_num,unsigned char *card_uid);
 unsigned char ISO15693_Mult_Read(unsigned char block1,unsigned char block2,unsigned char *rece_len,unsigned char *buff);
/*****************************************************************************************/
/*名称：ISO15693_Init																	 */
/*功能：设置通信协议为ISO15693															 */
/*输入：N/A																				 */
/*输出：OK：成功																		 */
/*****************************************************************************************/
 unsigned char ISO15693_Init(void)
{
	SPIWrite(ModConductance_Reg,0x08);
	SPIWrite(CoderControl_Reg,0x2f);
	SPIWrite(ModWidth_Reg,0x3f);
	SPIWrite(Rxcontrol1_Reg,0x8b);
	SPIWrite(DecoderControl_Reg,0x14);
	SPIWrite(RxThreshold_Reg,0xf7);
	SPIWrite(RxControl2_Reg,0x41);
	SPIWrite(ChannelRedundancy_Reg,0x2e);
	SPIWrite(CRCPresetLSB_Reg,0xff);
	SPIWrite(CRCPresetMSB_Reg,0xff);
	SPIWrite(TxControl_Reg,0x4b);
	//SPIWrite(TimeSlotPeriod_Reg,0x00);
	//SPIWrite(MFOUTSelect_Reg,0x00);
	return OK;
}
/*****************************************************************************************/
/*名称：ISO15693_Stayquite																 */
/*功能：设置卡片为停止状态																 */
/*输入：																				 */
/*输出： OK:成功，ERROR：失败															 */
/*****************************************************************************************/
unsigned char ISO15693_Stayquite(void)
{
	unsigned char data i,ret,rece_len;
	unsigned char send_byte[10],buff[1];
	SPIWrite(0x14,0x2f);
	SetTime_Delay(5);
 	send_byte[0] = 0x22;
 	send_byte[1] = 0x02;  //stayquite
 	for(i=0;i<8;i++)
  	{
    	send_byte[i+2] = rfid[i];  //UID
 	}  
   	ret = Command_Send(10, send_byte,&(rece_len),buff, Transmit);
	return ret;
}
/************************************************************************************************************/
/*名称：ISO15693_Inventory								 													*/
/*功能：15693卡片寻卡									 													*/
/*输入：N/A										 															*/
/*输出：rece_len:接收的数据长度;buff：接收的数据指针；card_uid卡片的UID指针；slot_num 卡片的slot编号		*/
/************************************************************************************************************/
unsigned char ISO15693_Inventory(unsigned char *rece_len,unsigned char *buff,unsigned char *card_uid,unsigned char *slot_num)
{
	unsigned char data i,j,ret,send_len,mask_len,mask_pos,round,slot_mark;
	unsigned char send_byte[11], mask_value[8];
	mask_len=0;
	mask_pos=0;

	for(i=0;i<8;i++)
	{
		card_uid[i]=0;
		mask_value[i]=0;
	}

	for(round=0;round<16;round++)
	{
		slot_mark=0;//寻卡标记
		*slot_num=0;//slot编号
	  
		send_byte[0] = 0x06;
		send_byte[1] = 0x01;    //Inventory
	  	send_byte[2] = mask_len;//MASK位长度
		for(i=0;i<8;i++)
		{
		   send_byte[3+i]=mask_value[i];
		}
	
	switch (round)
	{
		 case 0:send_len=3;break;//MASK位长度=0bit
		 case 1:send_len=4;break;//MASK位长度=4bit
		 case 2:send_len=4;break;//MASK位长度=8bit
		 case 3:send_len=5;break;//MASK位长度=12bit
		 case 4:send_len=5;break;//MASK位长度=16bit
		 case 5:send_len=6;break;//MASK位长度=20bit
		 case 6:send_len=6;break;//MASK位长度=24bit
		 case 7:send_len=7;break;//MASK位长度=28bit
		 case 8:send_len=7;break;//MASK位长度=32bit
		 case 9:send_len=8;break;//MASK位长度=36bit
		 case 10:send_len=8;break;//MASK位长度=40bit
		 case 11:send_len=9;break;//MASK位长度=44bit
		 case 12:send_len=9;break;//MASK位长度=48bit
		 case 13:send_len=10;break;//MASK位长度=52bit
		 case 14:send_len=10;break;//MASK位长度=56bit
		 case 15:send_len=11;break;//MASK位长度=60bit
	}//设置发送的命令长度


		SetTime_Delay(5);
		ret = Command_Send(send_len, send_byte,&(*rece_len),buff, Transceive);
		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)|0x80));
	
	 	for(j=0;j<16;j++)
			  {
			   *slot_num=j;//本次发送slot编号  
			    if (ret==OK)
			    {
					slot_mark=1;//收到卡片应答标记
				  	if((SPIRead(ErrorFlag_Reg)&0x0F)==0x00)//判断接收的CRC是否正确
					    {  
						 	for(i=0;i<8;i++)
							      {
							        card_uid[i]=buff[i+2];
							      }
						   	SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
					      	return OK;
						 }
					else
						{
						  	mask_len=mask_len+4;//MASK长度增加4bit
						   		 if (round%2==0)
								 	{
									 	mask_value[mask_pos]= *slot_num;//将slot编号作为下次发送的mask低4位
									}
								 else
								 	{
										mask_value[mask_pos]= *slot_num<<4+mask_value[mask_pos];//将slot编号作为下次发送的mask高4位
										mask_pos++;//mask数组偏移量加1
									}
					  	break;//退出当前round的Inventory操作,进入round+1的Inventory操作
						}
				}
			
				SetTime_Delay(5);
				ret = Command_Send(0, send_byte,&(*rece_len),buff, Transceive);
				if ((*slot_num==15)&(slot_mark==0))
					{
						SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
						return ERROR; //16个slot内均未收到任何应答，返回错误信息
					}
			  }

		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
		
	}
  	return ERROR;//16个round内均未收到正确的卡片应答，返回错误信息
}

/*****************************************************************************************/
/*名称：ISO15693_Select																	 */
/*功能：根据指定卡号选择卡片															 */
/*输入：card_uid，待选择的卡号															 */
/*输出：rece_len，返回的数据长度；buff，返回的数据指针									 */										 
/*****************************************************************************************/
unsigned char ISO15693_Select(unsigned char *card_uid,unsigned char *rece_len,unsigned char *buff)
{

unsigned char data ret,i;
unsigned char send_byte[10];

 	SPIWrite(0x14,0x2f);
	SetTime_Delay(5);
	send_byte[0] = 0x22;
	send_byte[1] = 0x25;  //select
	for(i=0;i<8;i++)
	{
    	send_byte[i+2] = card_uid[i];  //UID
	}  
	ret = Command_Send(10, send_byte,&(*rece_len),buff, Transceive);
return ret;
}
/*****************************************************************************************/
/*名称：ISO15693_Read																	 */
/*功能：卡片读取																		 */
/*输入：block，读取的块号																 */
/*输出：rece_len，读取数据的长度，buff，读取的数据指针									 */
/*****************************************************************************************/
unsigned char ISO15693_Read(unsigned char block,unsigned char *rece_len,unsigned char *buff)
{
	unsigned char data ret;
	unsigned char send_byte[3];
	SPIWrite(0x14,0x2f);
	SetTime_Delay(10);
	send_byte[0] = 0x12;
  	send_byte[1] = 0x20;
  	send_byte[2] = block;
  	ret = Command_Send(3, send_byte,&(*rece_len),buff, Transceive);
  	return ret;
}
/*****************************************************************************************/
/*名称：ISO15693_Write																	 */
/*功能：卡片写入																		 */
/*输入：card_type，卡片类型（0：1302T，1：1302T）；										 */
/*		block，写入的块号；block_data,写入的数据指针									 */										
/*输出：rece_len，返回的数据长度；buff，返回的数据指针									 */
/*****************************************************************************************/
unsigned char ISO15693_Write(unsigned char card_type,unsigned char block, unsigned char *block_data,unsigned char *rece_len,unsigned char *buff)
{
	unsigned char data ret;
	unsigned char send_byte[7];
	SPIWrite(0x14,0x2f);
	SetTime_Delay(10);
	if (card_type==0)//1302N
	{
  		send_byte[0] = 0x02;
	}
	if (card_type==1)//1302T
	{
	 	send_byte[0] = 0x42;
	}
  	send_byte[1] = 0x21;//Write Block
  	send_byte[2] = block;//Block number
  	send_byte[3] = block_data[0];	
  	send_byte[4] = block_data[1];	
  	send_byte[5] = block_data[2];
  	send_byte[6] = block_data[3];
 	ret = Command_Send(7, send_byte,&(*rece_len),buff, Transceive);
	if (card_type==1)//1302T
	{
		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)|0x80));
		SetTime_Delay(10);
		ret=Command_Send(0, send_byte,&(*rece_len),buff, Transceive);
		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
	//	SPIWrite(Command_Reg,0x00);
	}

  	return ret;
}
/*****************************************************************************************/
/*名称：ISO15693_Getinfo																 */
/*功能：获取卡片信息																	 */
/*输入：N/A																				 */
/*输出：rece_len,返回的数据长度;buff,返回的数据指针										 */
/*****************************************************************************************/
unsigned char ISO15693_Getinfo(unsigned char *rece_len,unsigned char *buff)
{
	unsigned char data ret,send_byte[2];
	SPIWrite(0x14,0x2f);
	SetTime_Delay(10);
	send_byte[0] = 0x12;
	send_byte[1] = 0x2B;
	ret = Command_Send(2,send_byte,&(*rece_len),buff, Transceive);
    return ret;
}

//void ISO15693_Send_EOF(void)
//{	
//	unsigned char send_byte[1],*rece_len,*buff;
//	SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)|0x80));
// 	Command_Send(0, send_byte,&(*rece_len),buff, Transceive);	
//
//	SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
//}

/************************************************************************************************************/
/*名称：ISO15693_Inventory								 													*/
/*功能：15693卡片寻卡									 													*/
/*输入：N/A										 															*/
/*输出：rece_len:接收的数据长度;buff：接收的数据指针；card_uid卡片的UID指针；slot_num 卡片的slot编号		*/
/************************************************************************************************************/
unsigned char ISO15693_Inventory_16slot(unsigned char *card_num,unsigned char *card_uid)
{
	unsigned char  i,j,ret,send_len,send_byte[11],mask_len,mask_value[8],mask_pos,round,slot_mark,card_mark,slot_num;
	unsigned char  *rece_len,buff[18];
	Rf_Off();
	Rf_On();
	mask_len=0;
	mask_pos=0;
	*card_num=0;
	slot_num=0;
	slot_mark=0;
	for(i=0;i<8;i++)
	{
		card_uid[i]=0;
		mask_value[i]=0;
	}

	for(round=0;round<16;round++)
	{
	
		slot_num=0;//slot编号
	  	
		//card_mark=0;
		send_byte[0] = 0x06;
		send_byte[1] = 0x01;    //Inventory
	  	send_byte[2] = mask_len;//MASK位长度
		for(i=0;i<8;i++)
		{
		   send_byte[3+i]=mask_value[i];
		}
	
	switch (round)
	{
		 case 0:send_len=3;break;//MASK位长度=0bit
		 case 1:send_len=4;break;//MASK位长度=4bit
		 case 2:send_len=4;break;//MASK位长度=8bit
		 case 3:send_len=5;break;//MASK位长度=12bit
		 case 4:send_len=5;break;//MASK位长度=16bit
		 case 5:send_len=6;break;//MASK位长度=20bit
		 case 6:send_len=6;break;//MASK位长度=24bit
		 case 7:send_len=7;break;//MASK位长度=28bit
		 case 8:send_len=7;break;//MASK位长度=32bit
		 case 9:send_len=8;break;//MASK位长度=36bit
		 case 10:send_len=8;break;//MASK位长度=40bit
		 case 11:send_len=9;break;//MASK位长度=44bit
		 case 12:send_len=9;break;//MASK位长度=48bit
		 case 13:send_len=10;break;//MASK位长度=52bit
		 case 14:send_len=10;break;//MASK位长度=56bit
		 case 15:send_len=11;break;//MASK位长度=60bit
	}//设置发送的命令长度
		
		SetTime_Delay(5);
		ret = Command_Send(send_len, send_byte,&(*rece_len),buff, Transceive);
		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)|0x80));
	
	 	for(j=0;j<16;j++)
			  {
					    slot_num=j;//本次发送slot编号  
					    if (ret==OK)
					    {
						   	
						  	if((SPIRead(ErrorFlag_Reg)&0x0F)==0x00)//判断接收的CRC是否正确
							    {  
							   		for(i=0;i<8;i++)
									      {
									        card_uid[i+((*card_num)*8)]=buff[i+2];
									      }
							   		(*card_num)++;
							   		 card_mark++;
								 }
							else
								{
								   	mask_len=mask_len+4;//MASK长度增加4bit
								   		 if (round%2==0)
										 	{
											 	mask_value[mask_pos]= slot_num;//将slot编号作为下次发送的mask低4位
											}
										 else
										 	{
												mask_value[mask_pos]= slot_num<<4+mask_value[mask_pos];//将slot编号作为下次发送的mask高4位
												mask_pos++;//mask数组偏移量加1
											}
							   		slot_mark=round+1;
							  //	break;//退出当前round的Inventory操作,进入round+1的Inventory操作
								}
						}
						SetTime_Delay(5);
						ret = Command_Send(0, send_byte,&(*rece_len),buff, Transceive);
						if (round==slot_mark+1)
					{
					   	SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
						return OK; //16个slot内均未收到任何应答，返回错误信息
					}
			  }

		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
		
	}
  	return ERROR;//
}
/************************************************************************************************************/
/*名称：ISO15693_Mult_Read								 													*/
/*功能：15693卡片读取多块								 													*/
/*输入：block1，起始块地址；block2，读取块的数量	 														*/
/*输出：rece_len:接收的数据长度;buff：接收的数据指针；														*/
/************************************************************************************************************/
unsigned char ISO15693_Mult_Read(unsigned char block1,unsigned char block2,unsigned char *rece_len,unsigned char *buff)
{
	unsigned char data ret;
	unsigned char send_byte[4];
	SPIWrite(0x14,0x2f);
	SetTime_Delay(10);
	send_byte[0] = 0x12;
  	send_byte[1] = 0x23;
  	send_byte[2] = block1;
	send_byte[3] = block2;
  	ret = Command_Send(4, send_byte,&(*rece_len),buff, Transceive);
  	return ret;
}
