//#include "at89x52.h"
//#include "intrins.h"
//#include "pin.h"
#include "psam.h"
//#include "fm17xx.h"
#include "psam.h"
//#include "main.h"
//#include "uart.h"
//#include <string.h>

 unsigned char sam_byte_read(unsigned char *sam_data);
 unsigned char sam_byte_write(unsigned char sam_data);
 unsigned char sam_write(unsigned char data_len,unsigned char *sam_data);
 unsigned char sam_read(unsigned char *rece_len,unsigned char *rece_buff);
 unsigned char sam_command(unsigned char data_len,unsigned char *data_buff,unsigned char *rece_len,unsigned char *rece_buff);
 unsigned char sam_get_response(unsigned char response_length,unsigned char *rece_len,unsigned char *buff);
 unsigned char sam_get_challenge(unsigned char *rece_len,unsigned char *buff);
// unsigned char sam_ex_authentication(unsigned char *key_buff,unsigned char *rece_len,unsigned char *buff);
 unsigned char sam_reset(unsigned char *rece_len,unsigned char *buff);

/*************************/
/*�������ܣ�	SAM ��ȡ
/*���������	���������ַ
/*���������	����������
/*����ֵ��		OK	:У����ȷ
/*				ERROR:У������ʱ
/*ռ����Դ��	��
/*************************/
unsigned char sam_read(unsigned char *rece_len,unsigned char *rece_buff)
{
unsigned int  k,j;
unsigned char i,ret;

	sam_io=1;
	j=0xffff;//������ʱ����	
	k=0xffff;//������ʱ����
	while(sam_io==1)
	{
		j--;
		if(j==0)
		{
			k--;
			j=1;
			if(k==0)
			{
			return ERROR;
			}
		}
	}


	for(i=0;i<128;i++)
	{
		ret=sam_byte_read(&(*(rece_buff+i)));

		if(ret==ERROR)
		{
		*rece_len=i;
		goto End_sam_read;
		}
	}
	End_sam_read:

	return OK;
}
/*************************/
/*�������ܣ�	SAM ��ȡһ���ֽ�
/*���������	���������ַ
/*���������	����������
/*����ֵ��		OK	:У����ȷ
/*				ERROR:У������ʱ
/*ռ����Դ��	��
/*************************/
unsigned char sam_byte_read(unsigned char *sam_data)
{
	unsigned char  i,read_temp,read_verify;
	unsigned int  j;

	j=0xFF;//������ʱ����	

	while(sam_io==1)
		{
		j--;
			if(j==0)
			{
			read_verify=ERROR;//����
			read_temp=0;
			goto End_sam_byte_read;
			}
	 	}


  	TR0=1;//������ʱ��
	sam_timer_flag=0;
	read_temp=0; 
	read_verify=0;
	while(!sam_timer_flag);//0.5ETU

	for(i=0;i<8;i++)	
	{
  	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU	
	read_temp=read_temp>>1;
	if(sam_io==1)
		{
		read_temp=read_temp|0x80;
		read_verify=read_verify+0x01;
		}
	read_verify=read_verify&0x01;
	}

  	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU


	if(read_verify==sam_io)
	{
		read_verify=OK;//��ȷ
	}
	else
	{
		read_verify=ERROR;//����
		read_temp=0;
	}

  	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	TR0=0;//�رն�ʱ��

	End_sam_byte_read:
	*sam_data=read_temp;

return read_verify;
}

/*************************/
/*�������ܣ�	SAM д��һ���ֽ�
/*���������	����
/*���������	��
/*����ֵ��		
/*ռ����Դ��	��
/*************************/
unsigned char sam_byte_write(unsigned char sam_data)
{	unsigned char write_temp,i,write_verify;
	write_temp=sam_data;
	write_verify=0;

	sam_io=0;	//֡ͷ
	TR0=1;//������ʱ��
  	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	for(i=0;i<8;i++)
	{
	if((write_temp&0x1)==0x1)
		{
		sam_io=1;
		write_verify=write_verify+1;
		}
	else
		sam_io=0;
	write_temp=write_temp>>1;
	write_verify=write_verify&0x1;

	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	}
	
	sam_io=write_verify;

	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU

	sam_io=1;//֡β
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	if (sam_io==0)
		write_verify=ERROR;
	else
		write_verify=OK;
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU
	sam_timer_flag=0;
	while(!sam_timer_flag);//0.5ETU

	TR0=0;//�رն�ʱ��
	return write_verify;
}
/*************************/
/*�������ܣ�	SAM д�����ֽ�
/*���������	���ݣ����ݳ���
/*���������	��
/*����ֵ��		
/*ռ����Դ��	��
/*************************/
unsigned char sam_write(unsigned char data_len,unsigned char *sam_data)
{
	unsigned char i,ret;
	for(i=0;i<data_len;i++)
	{
		ret=sam_byte_write(sam_data[i]);
	}
	return ret;
}
/*************************/
/*�������ܣ�	SAM ָ���
/*���������	���ݣ����ݳ���
/*���������	����
/*����ֵ��		���ݳ���
/*ռ����Դ��	��
/*************************/

unsigned char sam_command(unsigned char data_len,unsigned char *data_buff,unsigned char *rece_len,unsigned char *rece_buff)
{
	unsigned char ret,Lc,Le;
	if(data_len<4)
	{
	  	ret=sam_write(data_len,data_buff);
		ret=sam_read(&(*rece_len),rece_buff);
	}

	if(data_len==4)		//���1
	{
			ret=sam_write(data_len,data_buff);
			ret=sam_read(&(*rece_len),rece_buff);
			return ret;
	}
	 
	if(data_len==5)		//���2
	{
			Le=data_buff[4];
			ret=sam_write(4,data_buff);
			//delay_100us(1);
			ret=sam_write(1,&Le);
			ret=sam_read(&(*rece_len),rece_buff);
			return ret;
	}
	
	if(data_len>5)	
	{
			Lc=data_buff[4];
		
			if((Lc+5)==data_len)	//���3
			{
				ret=sam_write(5,data_buff);
				ret=sam_read(&(*rece_len),rece_buff);
					if(ret==ERROR)
					{
						return ret;
					}
			ret=sam_write(Lc,&data_buff[5]);
			ret=sam_read(&(*rece_len),rece_buff);
			return ret;
			}

	if((Lc+6)==data_len)	//���4
	{
			ret=sam_write(5,data_buff);
			ret=sam_read(&(*rece_len),rece_buff);
			if(ret==ERROR)
				{
					return ret;
				}
			ret=sam_write(Lc+1,&data_buff[5]);
			ret=sam_read(&(*rece_len),rece_buff);
			return ret;
	}
}
		  	return ret;
}
/*************************/
/*�������ܣ�	SAM reset
/*���������	���ݣ����ݳ���
/*���������	����
/*����ֵ��		���ݳ���
/*ռ����Դ��	��
/*************************/

unsigned char sam_reset(unsigned char *rece_len,unsigned char *buff)
{
	unsigned char ret;
	sam_rst=0;
	Delay_100us(50);
	sam_rst=1;
	ret=sam_read(&(*rece_len),buff);
	return(ret);
}


/*************************/
/*�������ܣ�	SAM Get Response
/*���������	��Ӧ���ݳ���
/*����ֵ��		���ݳ���
/*				��������	
/*ռ����Դ��	��
/*************************/

unsigned char sam_get_response(unsigned char response_length,unsigned char *rece_len,unsigned char *buff)
{
	unsigned char send_byte[5],ret;
	send_byte[0]=0x00;
	send_byte[1]=0xc0;
	send_byte[2]=0x00;
	send_byte[3]=0x00;
	send_byte[4]=response_length;
	ret=sam_command(5,send_byte,&(*rece_len),buff);
	return(ret);
}
/*************************/
/*�������ܣ�	SAM Get Challenge
/*���������
/*���������	���ݳ���
/*����ֵ��		��������
/*ռ����Դ��	��
/*************************/

unsigned char sam_get_challenge(unsigned char *rece_len,unsigned char *buff)
{
	unsigned char send_byte[5],ret;
	send_byte[0]=0x00;
	send_byte[1]=0x84;
	send_byte[2]=0x00;
	send_byte[3]=0x00;
	send_byte[4]=0x04;
	ret=sam_command(5,send_byte,&(*rece_len),buff);
	return ret;
}

/*************************/
/*�������ܣ�	SAM ex Authentication
/*���������	16�ֽ���֤��Կ����
/*����ֵ��		���ݳ���
/*				��������
/*ռ����Դ��	��
/*************************/

//unsigned char sam_ex_authentication(unsigned char *key_buff,unsigned char *rece_len,unsigned char *buff)
//{
//		unsigned char send_byte[13],rece_buff[7],temp,Random_data[8],ret,des_buff[8],i;
//		ret=sam_get_challenge(&temp,rece_buff);
//		if (ret==ERROR)
//			return ret;
//		for(i=0;i<4;i++)
//			Random_data[i]=rece_buff[i+1];
//		for(i=4;i<8;i++)
//			Random_data[i]=0x00;
//
//		Tdes(ENCRY,Random_data,key_buff,des_buff);
//					 
//		send_byte[0]=0x00;//CLA
//		send_byte[1]=0x82;//INS
//		send_byte[2]=0x00;//P1
//		send_byte[3]=0x00;//P2
//		send_byte[4]=0x08;//Lc
//		for(i=0;i<8;i++)
//			send_byte[i+5]= des_buff[i];
//		ret=sam_command(13,send_byte,&(*rece_len),buff);
//		return(ret);
//}

