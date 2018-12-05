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
/*���ƣ�ISO15693_Init																	 */
/*���ܣ�����ͨ��Э��ΪISO15693															 */
/*���룺N/A																				 */
/*�����OK���ɹ�																		 */
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
/*���ƣ�ISO15693_Stayquite																 */
/*���ܣ����ÿ�ƬΪֹͣ״̬																 */
/*���룺																				 */
/*����� OK:�ɹ���ERROR��ʧ��															 */
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
/*���ƣ�ISO15693_Inventory								 													*/
/*���ܣ�15693��ƬѰ��									 													*/
/*���룺N/A										 															*/
/*�����rece_len:���յ����ݳ���;buff�����յ�����ָ�룻card_uid��Ƭ��UIDָ�룻slot_num ��Ƭ��slot���		*/
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
		slot_mark=0;//Ѱ�����
		*slot_num=0;//slot���
	  
		send_byte[0] = 0x06;
		send_byte[1] = 0x01;    //Inventory
	  	send_byte[2] = mask_len;//MASKλ����
		for(i=0;i<8;i++)
		{
		   send_byte[3+i]=mask_value[i];
		}
	
	switch (round)
	{
		 case 0:send_len=3;break;//MASKλ����=0bit
		 case 1:send_len=4;break;//MASKλ����=4bit
		 case 2:send_len=4;break;//MASKλ����=8bit
		 case 3:send_len=5;break;//MASKλ����=12bit
		 case 4:send_len=5;break;//MASKλ����=16bit
		 case 5:send_len=6;break;//MASKλ����=20bit
		 case 6:send_len=6;break;//MASKλ����=24bit
		 case 7:send_len=7;break;//MASKλ����=28bit
		 case 8:send_len=7;break;//MASKλ����=32bit
		 case 9:send_len=8;break;//MASKλ����=36bit
		 case 10:send_len=8;break;//MASKλ����=40bit
		 case 11:send_len=9;break;//MASKλ����=44bit
		 case 12:send_len=9;break;//MASKλ����=48bit
		 case 13:send_len=10;break;//MASKλ����=52bit
		 case 14:send_len=10;break;//MASKλ����=56bit
		 case 15:send_len=11;break;//MASKλ����=60bit
	}//���÷��͵������


		SetTime_Delay(5);
		ret = Command_Send(send_len, send_byte,&(*rece_len),buff, Transceive);
		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)|0x80));
	
	 	for(j=0;j<16;j++)
			  {
			   *slot_num=j;//���η���slot���  
			    if (ret==OK)
			    {
					slot_mark=1;//�յ���ƬӦ����
				  	if((SPIRead(ErrorFlag_Reg)&0x0F)==0x00)//�жϽ��յ�CRC�Ƿ���ȷ
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
						  	mask_len=mask_len+4;//MASK��������4bit
						   		 if (round%2==0)
								 	{
									 	mask_value[mask_pos]= *slot_num;//��slot�����Ϊ�´η��͵�mask��4λ
									}
								 else
								 	{
										mask_value[mask_pos]= *slot_num<<4+mask_value[mask_pos];//��slot�����Ϊ�´η��͵�mask��4λ
										mask_pos++;//mask����ƫ������1
									}
					  	break;//�˳���ǰround��Inventory����,����round+1��Inventory����
						}
				}
			
				SetTime_Delay(5);
				ret = Command_Send(0, send_byte,&(*rece_len),buff, Transceive);
				if ((*slot_num==15)&(slot_mark==0))
					{
						SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
						return ERROR; //16��slot�ھ�δ�յ��κ�Ӧ�𣬷��ش�����Ϣ
					}
			  }

		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
		
	}
  	return ERROR;//16��round�ھ�δ�յ���ȷ�Ŀ�ƬӦ�𣬷��ش�����Ϣ
}

/*****************************************************************************************/
/*���ƣ�ISO15693_Select																	 */
/*���ܣ�����ָ������ѡ��Ƭ															 */
/*���룺card_uid����ѡ��Ŀ���															 */
/*�����rece_len�����ص����ݳ��ȣ�buff�����ص�����ָ��									 */										 
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
/*���ƣ�ISO15693_Read																	 */
/*���ܣ���Ƭ��ȡ																		 */
/*���룺block����ȡ�Ŀ��																 */
/*�����rece_len����ȡ���ݵĳ��ȣ�buff����ȡ������ָ��									 */
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
/*���ƣ�ISO15693_Write																	 */
/*���ܣ���Ƭд��																		 */
/*���룺card_type����Ƭ���ͣ�0��1302T��1��1302T����										 */
/*		block��д��Ŀ�ţ�block_data,д�������ָ��									 */										
/*�����rece_len�����ص����ݳ��ȣ�buff�����ص�����ָ��									 */
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
/*���ƣ�ISO15693_Getinfo																 */
/*���ܣ���ȡ��Ƭ��Ϣ																	 */
/*���룺N/A																				 */
/*�����rece_len,���ص����ݳ���;buff,���ص�����ָ��										 */
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
/*���ƣ�ISO15693_Inventory								 													*/
/*���ܣ�15693��ƬѰ��									 													*/
/*���룺N/A										 															*/
/*�����rece_len:���յ����ݳ���;buff�����յ�����ָ�룻card_uid��Ƭ��UIDָ�룻slot_num ��Ƭ��slot���		*/
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
	
		slot_num=0;//slot���
	  	
		//card_mark=0;
		send_byte[0] = 0x06;
		send_byte[1] = 0x01;    //Inventory
	  	send_byte[2] = mask_len;//MASKλ����
		for(i=0;i<8;i++)
		{
		   send_byte[3+i]=mask_value[i];
		}
	
	switch (round)
	{
		 case 0:send_len=3;break;//MASKλ����=0bit
		 case 1:send_len=4;break;//MASKλ����=4bit
		 case 2:send_len=4;break;//MASKλ����=8bit
		 case 3:send_len=5;break;//MASKλ����=12bit
		 case 4:send_len=5;break;//MASKλ����=16bit
		 case 5:send_len=6;break;//MASKλ����=20bit
		 case 6:send_len=6;break;//MASKλ����=24bit
		 case 7:send_len=7;break;//MASKλ����=28bit
		 case 8:send_len=7;break;//MASKλ����=32bit
		 case 9:send_len=8;break;//MASKλ����=36bit
		 case 10:send_len=8;break;//MASKλ����=40bit
		 case 11:send_len=9;break;//MASKλ����=44bit
		 case 12:send_len=9;break;//MASKλ����=48bit
		 case 13:send_len=10;break;//MASKλ����=52bit
		 case 14:send_len=10;break;//MASKλ����=56bit
		 case 15:send_len=11;break;//MASKλ����=60bit
	}//���÷��͵������
		
		SetTime_Delay(5);
		ret = Command_Send(send_len, send_byte,&(*rece_len),buff, Transceive);
		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)|0x80));
	
	 	for(j=0;j<16;j++)
			  {
					    slot_num=j;//���η���slot���  
					    if (ret==OK)
					    {
						   	
						  	if((SPIRead(ErrorFlag_Reg)&0x0F)==0x00)//�жϽ��յ�CRC�Ƿ���ȷ
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
								   	mask_len=mask_len+4;//MASK��������4bit
								   		 if (round%2==0)
										 	{
											 	mask_value[mask_pos]= slot_num;//��slot�����Ϊ�´η��͵�mask��4λ
											}
										 else
										 	{
												mask_value[mask_pos]= slot_num<<4+mask_value[mask_pos];//��slot�����Ϊ�´η��͵�mask��4λ
												mask_pos++;//mask����ƫ������1
											}
							   		slot_mark=round+1;
							  //	break;//�˳���ǰround��Inventory����,����round+1��Inventory����
								}
						}
						SetTime_Delay(5);
						ret = Command_Send(0, send_byte,&(*rece_len),buff, Transceive);
						if (round==slot_mark+1)
					{
					   	SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
						return OK; //16��slot�ھ�δ�յ��κ�Ӧ�𣬷��ش�����Ϣ
					}
			  }

		SPIWrite(CoderControl_Reg,(SPIRead(CoderControl_Reg)&0x7F));
		
	}
  	return ERROR;//
}
/************************************************************************************************************/
/*���ƣ�ISO15693_Mult_Read								 													*/
/*���ܣ�15693��Ƭ��ȡ���								 													*/
/*���룺block1����ʼ���ַ��block2����ȡ�������	 														*/
/*�����rece_len:���յ����ݳ���;buff�����յ�����ָ�룻														*/
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
