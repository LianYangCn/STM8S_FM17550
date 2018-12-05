/******************************************************
文件名：	Mytype.h

描述�

Data			  Vasion			author
2018/1/4		  V1.0			    liujian
*******************************************************/
#ifndef		MYTYPE_H
#define		MYTYPE_H
/*******************************************************
description：include the header file
*******************************************************/

/*******************************************************
description：macro definitions
*******************************************************/
/**********宏开关定�*******/

typedef	unsigned  char			    uint8;
typedef	signed  char			      int8;
typedef	unsigned  int			      uint16;
typedef			      int			      int16;
typedef	unsigned  long int		  uint32;
typedef			      long int		  int32;

typedef signed char SC; 	
typedef unsigned char UC;	
typedef short SS;	
typedef unsigned short US;	
typedef long SL;	
typedef unsigned long UL;
typedef unsigned int UI;
typedef signed int SI;

/*******************************************************
description��Often use of macro definitions
*******************************************************/
/************��ʾ��/��״̬***************/
#ifndef   STD_ON
#define		STD_ON		  1
#endif

#ifndef   STD_OFF
#define		STD_OFF		0
#endif
/***********��ʾ��ƽ�ĸ�/��**************/
#ifndef   STD_HIGH
#define		STD_HIGH		1
#endif

#ifndef   STD_LOW
#define		STD_LOW		0
#endif

/***********��ʾ��Ч/��Ч***************/
#ifndef   STD_ACTIVE
#define		STD_ACTIVE		  1
#endif

#ifndef   STD_INACTIVE
#define		STD_INACTIVE		0
#endif

/***********��ʾ��/��***************/
#ifndef   STD_TRUE
#define		STD_TRUE			1
#endif

#ifndef   STD_FALSE
#define		STD_FALSE		0
#endif

/***********��ʾ��0***************/
#ifndef   STD_NULL
#define		STD_NULL		0
#endif

/***********��ָ��***************/
#ifndef   STD_NULL_PTR
#define   STD_NULL_PTR   ((void*)0)
#endif


/**********宏常量定�*******/



/***********宏函�*********/

/*******************************************************
description：struct definitions
*******************************************************/

/*******************************************************
description：typedef definitions
*******************************************************/
/*****struct definitions*****/

/******enum definitions******/

/******union definitions*****/

/*******************************************************
description：variable External declaration
*******************************************************/

/*******************************************************
description：function External declaration
*******************************************************/

#endif
