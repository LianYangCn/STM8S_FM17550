#include "fm175xx.h"
#include "type_b.h"
#include "Utility.h"
//#include "cpu_card.h"
#include <string.h>

unsigned char PUPI[4];	


/*****************************************************************************************/
/*名称：TypeB_Halt																		 */
/*功能：设置TYPE B卡片进入停止状态														 */
/*输入：card_sn：卡片的PUPI																 */
/*输出：																				 */
/*	   	TRUE：操作成功																	 */
/*		ERROR：操作失败																	 */
/*****************************************************************************************/
unsigned char TypeB_Halt(unsigned char *card_sn)
{
	unsigned char  ret,send_byte[5],rece_byte[1],i;
	unsigned int  rece_len;
	Pcd_SetTimer(10);
	send_byte[0] = 0x50;
	for(i = 0; i < 4; i++)
	{
		send_byte[i + 1] =card_sn[i];
	}
	ret=Pcd_Comm(Transceive,send_byte,5,rece_byte,&rece_len);
	return (ret);
}
/*****************************************************************************************/
/*名称：TypeB_WUP																		 */
/*功能：TYPE B卡片唤醒																	 */
/*输入：N/A																				 */
/*输出：																				 */
/*		rece_len:卡片应答的数据长度；buff：卡片应答的数据指针							 */
/*		card_sn:卡片的PUPI字节															 */
/*	   	TRUE：操作成功																	 */
/*		ERROR：操作失败																	 */
/*****************************************************************************************/
unsigned char TypeB_WUP(unsigned int *rece_len,unsigned char *buff,unsigned char *card_sn)
{						
	unsigned char  ret,send_byte[3];
	Pcd_SetTimer(10);
	send_byte[0]=0x05;//APf
	send_byte[1]=0x00;//AFI (00:for all cards)
	send_byte[2]=0x08;//PARAM(WUP,Number of slots =0)
	ret=Pcd_Comm(Transceive,send_byte,3,buff,&(*rece_len));
	if (ret==TRUE)
		memcpy(card_sn,&buff[1],4);		
	return (ret);
}
/*****************************************************************************************/
/*名称：TypeB_Request																	 */
/*功能：TYPE B卡片选卡																	 */
/*输入：																				 */
/*输出：																				 */
/*	   	TRUE：操作成功																	 */
/*		ERROR：操作失败																	 */
/*****************************************************************************************/
unsigned char TypeB_Request(unsigned int *rece_len,unsigned char *buff,unsigned char *card_sn)
{			
	unsigned char  ret,send_byte[5];
	Pcd_SetTimer(10);
	send_byte[0]=0x05;	//APf
	send_byte[1]=0x00;	//AFI (00:for all cards)
	send_byte[2]=0x00;	//PARAM(REQB,Number of slots =0)
	ret=Pcd_Comm(Transceive,send_byte,3,buff,rece_len);
	if (ret==TRUE)	
		memcpy(card_sn,buff+1,4);
	return (ret);
}		
/*****************************************************************************************/
/*名称：TypeB_Select																	 */
/*功能：TYPE B卡片选卡																	 */
/*输入：card_sn：卡片PUPI字节（4字节）													 */
/*输出：																				 */
/*		rece_len：应答数据的长度														 */
/*		buff：应答数据的指针															 */
/*	   	TRUE：操作成功																	 */
/*		ERROR：操作失败																	 */
/*****************************************************************************************/
unsigned char TypeB_Select(unsigned char *card_sn,unsigned int *rece_len,unsigned char *buff)
{
	unsigned char  ret,send_byte[9],i;
	Pcd_SetTimer(20);
	send_byte[0] = 0x1d;
	for(i = 0; i < 4; i++)
	{
		send_byte[i + 1] =card_sn[i];
	}
	send_byte[5] = 0x00;  //------Param1
	send_byte[6] = 0x08;  //01--24，08--256------Param2
	send_byte[7] = 0x01;  //COMPATIBLE WITH 14443-4------Param3
	send_byte[8] = 0x02;  //CID：01 ------Param4
	 
	ret=Pcd_Comm(Transceive,send_byte,9,buff,&(*rece_len));
	return (ret);
}	
/*****************************************************************************************/
/*名称：TypeB_GetUID																	 */
/*功能：身份证专用指令																	 */
/*输入：N/A																				 */
/*输出：rece_len：返回数据的长度														 */
/*		buff：返回数据的指针															 */
/*	   	TRUE：操作成功																	 */
/*		ERROR：操作失败																	 */
/*****************************************************************************************/
unsigned char TypeB_GetUID(unsigned int *rece_len,unsigned char *buff)
{
	unsigned char  ret,send_byte[5];
	Pcd_SetTimer(15);
	send_byte[0]=0x00;
	send_byte[1]=0x36;
	send_byte[2]=0x00;
	send_byte[3]=0x00;
	send_byte[4]=0x08;
	ret=Pcd_Comm(Transceive,send_byte,5,buff,&(*rece_len));
	return (ret);
}	
