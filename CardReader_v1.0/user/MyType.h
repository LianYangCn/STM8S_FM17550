/******************************************************
鏂囦欢鍚嶏細	Mytype.h

鎻忚堪锛

Data			  Vasion			author
2018/1/4		  V1.0			    liujian
*******************************************************/
#ifndef		MYTYPE_H
#define		MYTYPE_H
/*******************************************************
description锛歩nclude the header file
*******************************************************/

/*******************************************************
description锛歮acro definitions
*******************************************************/
/**********瀹忓紑鍏冲畾涔*******/

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
description：Often use of macro definitions
*******************************************************/
/************表示开/关状态***************/
#ifndef   STD_ON
#define		STD_ON		  1
#endif

#ifndef   STD_OFF
#define		STD_OFF		0
#endif
/***********表示电平的高/低**************/
#ifndef   STD_HIGH
#define		STD_HIGH		1
#endif

#ifndef   STD_LOW
#define		STD_LOW		0
#endif

/***********表示有效/无效***************/
#ifndef   STD_ACTIVE
#define		STD_ACTIVE		  1
#endif

#ifndef   STD_INACTIVE
#define		STD_INACTIVE		0
#endif

/***********表示真/假***************/
#ifndef   STD_TRUE
#define		STD_TRUE			1
#endif

#ifndef   STD_FALSE
#define		STD_FALSE		0
#endif

/***********表示清0***************/
#ifndef   STD_NULL
#define		STD_NULL		0
#endif

/***********空指针***************/
#ifndef   STD_NULL_PTR
#define   STD_NULL_PTR   ((void*)0)
#endif


/**********瀹忓父閲忓畾涔*******/



/***********瀹忓嚱鏁*********/

/*******************************************************
description锛歴truct definitions
*******************************************************/

/*******************************************************
description锛歵ypedef definitions
*******************************************************/
/*****struct definitions*****/

/******enum definitions******/

/******union definitions*****/

/*******************************************************
description锛歷ariable External declaration
*******************************************************/

/*******************************************************
description锛歠unction External declaration
*******************************************************/

#endif
