/******************************************************
�ļ�����	TX522B.h

������	ȫ˫������ͨ��	

Data			  Vasion			author
2018/01/10		   V1.0			    liujian
*******************************************************/
#ifndef		_TX522B_H
#define		_TX522B_H
/*******************************************************
description�� include the header file
*******************************************************/
#include "Tx522b_cfg.h"

/*******************************************************
description�� macro definitions
*******************************************************/
/**********�꿪�ض���*********/

/**********�곣������*********/
/*����ָ�*/
#define LoadKey     	0x20/*װ����Կָ��*/
#define GetCardSnr  	0x21/*���Ƭ����ȡ����*/
#define	ReadBlock		0x22/*����*/
#define WriteBlock		0x23/*д��*/
#define ReadSector		0x24/*������*/
#define	DetectCard		0x25/*�Զ�Ѱ��*/

#define	SetBaudRate		0x2f/*���ò�����*/

/*���巵��״̬*/
#define COMM_OK 	0 //�������óɹ�
#define NO_TAG_ERR 	1 //����Ч������û�п�
#define	CRC_ERR 	2 //�ӿ��н��յ��˴���� CRC У���
#define	EMPTY 		3 //ֵ���
#define	AUTH_ERR 	4 //������֤
#define	PARITY_ERR 	5 //�ӿ��н��յ��˴����У��λ
#define	CODE_ERR 	6 //ͨ�Ŵ���
#define	SENDR_ERR	8 //�ڷ���ͻʱ�����˴���Ĵ�����
#define	KEY_ERR 	9 //֤ʵ�����
#define	NOT_AUTH_ERR 	0x0a //��û����֤
#define	BIT_COUNT_ERR 	0x0b //�ӿ��н��յ��˴���������λ
#define	BYTE_COUNT_ERR 	0x0c //�ӿ��н����˴����������ֽ�
#define	TRANS_ERR 		0x0e //���� Transfer ��������
#define	WRITE_ERR 		0x0f //���� Write ��������
#define	INCR_ERR 		0x10 //���� Increment ��������
#define	DECR_ERR 		0x11 //���� Decrment ��������
#define	READ_ERR 		0x12 //���� Read ��������
#define	COLL_ERR 		0x18 //��ͻ��
#define	ACCESS_TIMEOUT 	0x1b //���ʳ�ʱ
#define	QUIT 			0x1e //��һ����������ʱ�����
#define	CHK_WR_OK 		0 //Check Write ��ȷ
#define	CHK_WR_FAILED 	1 //Check Write ����
#define	CHK_WR_COMP_ERR 2 //Check Write:д�����Ƚϳ���
#define	COMM_ERR 		0xff //����ͨ�Ŵ���
#define	MI_WRONG_VALUE 	0x7b //ֵ���ʽ����


/***********�꺯��***********/

/*******************************************************
description�� struct definitions
*******************************************************/

/*******************************************************
description�� typedef definitions
*******************************************************/
/*****struct definitions*****/
typedef struct 
{		
	union
	{
		unsigned char Block[59];/*����������*/
		struct
		{
			unsigned char Seqnr;/* ����֡����*/
			unsigned char Cmd;/* ����֡����*/
			unsigned char DtLng;/* ������Ч���ݶγ��ȱ�ʾ*/
			unsigned char ValidDt[56];/* ���յ���Ч���ݶΣ�����󳤶ȶ���洢�ռ�*/
		}DtSrt;
	}Dt;
}Tx522b_RxMsg; /*���Ľ��սṹ��*/ 


typedef struct 
{		
	unsigned char NewFlag;/* ����������Ч��־*/
	unsigned char Lng;/* �������ݳ���*/
	unsigned char Dt[30U];/* �������ݻ�����*/
}Tx522b_TxMsg; /*���ķ��ͽṹ��*/
/******enum definitions******/

/******union definitions*****/

/*******************************************************
description�� variable External declaration
*******************************************************/

/*******************************************************
description�� function External declaration
*******************************************************/
extern void InitTx522b_parameter(void);
extern void Tx522b_MainFunction(void);

#endif 
