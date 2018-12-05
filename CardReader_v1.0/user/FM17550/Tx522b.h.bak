/******************************************************
文件名：	TX522B.h

描述：	全双工串口通信	

Data			  Vasion			author
2018/01/10		   V1.0			    liujian
*******************************************************/
#ifndef		_TX522B_H
#define		_TX522B_H
/*******************************************************
description： include the header file
*******************************************************/
#include "Tx522b_cfg.h"

/*******************************************************
description： macro definitions
*******************************************************/
/**********宏开关定义*********/

/**********宏常量定义*********/
/*定义指令集*/
#define LoadKey     	0x20/*装载密钥指令*/
#define GetCardSnr  	0x21/*激活卡片并获取卡号*/
#define	ReadBlock		0x22/*读块*/
#define WriteBlock		0x23/*写块*/
#define ReadSector		0x24/*读扇区*/
#define	DetectCard		0x25/*自动寻卡*/

#define	SetBaudRate		0x2f/*设置波特率*/

/*定义返回状态*/
#define COMM_OK 	0 //函数调用成功
#define NO_TAG_ERR 	1 //在有效区域内没有卡
#define	CRC_ERR 	2 //从卡中接收到了错误的 CRC 校验和
#define	EMPTY 		3 //值溢出
#define	AUTH_ERR 	4 //不能验证
#define	PARITY_ERR 	5 //从卡中接收到了错误的校验位
#define	CODE_ERR 	6 //通信错误
#define	SENDR_ERR	8 //在防冲突时读到了错误的串行码
#define	KEY_ERR 	9 //证实密码错
#define	NOT_AUTH_ERR 	0x0a //卡没有验证
#define	BIT_COUNT_ERR 	0x0b //从卡中接收到了错误数量的位
#define	BYTE_COUNT_ERR 	0x0c //从卡中接收了错误数量的字节
#define	TRANS_ERR 		0x0e //调用 Transfer 函数出错
#define	WRITE_ERR 		0x0f //调用 Write 函数出错
#define	INCR_ERR 		0x10 //调用 Increment 函数出错
#define	DECR_ERR 		0x11 //调用 Decrment 函数出错
#define	READ_ERR 		0x12 //调用 Read 函数出错
#define	COLL_ERR 		0x18 //冲突错
#define	ACCESS_TIMEOUT 	0x1b //访问超时
#define	QUIT 			0x1e //上一次了送命令时被打断
#define	CHK_WR_OK 		0 //Check Write 正确
#define	CHK_WR_FAILED 	1 //Check Write 出错
#define	CHK_WR_COMP_ERR 2 //Check Write:写出错（比较出错）
#define	COMM_ERR 		0xff //串行通信错误
#define	MI_WRONG_VALUE 	0x7b //值块格式错误


/***********宏函数***********/

/*******************************************************
description： struct definitions
*******************************************************/

/*******************************************************
description： typedef definitions
*******************************************************/
/*****struct definitions*****/
typedef struct 
{		
	union
	{
		unsigned char Block[59];/*接收数据数*/
		struct
		{
			unsigned char Seqnr;/* 接收帧包号*/
			unsigned char Cmd;/* 接收帧命令*/
			unsigned char DtLng;/* 接收有效数据段长度表示*/
			unsigned char ValidDt[56];/* 接收的有效数据段：按最大长度定义存储空间*/
		}DtSrt;
	}Dt;
}Tx522b_RxMsg; /*报文接收结构体*/ 


typedef struct 
{		
	unsigned char NewFlag;/* 发送数据有效标志*/
	unsigned char Lng;/* 发送数据长度*/
	unsigned char Dt[30U];/* 发送数据缓冲区*/
}Tx522b_TxMsg; /*报文发送结构体*/
/******enum definitions******/

/******union definitions*****/

/*******************************************************
description： variable External declaration
*******************************************************/

/*******************************************************
description： function External declaration
*******************************************************/
extern void InitTx522b_parameter(void);
extern void Tx522b_MainFunction(void);

#endif 
