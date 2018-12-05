// =======================================================================================
//  Copyright (c) 2011 Guangzhou Zhiyuan Electronics Co., Ltd. All rights reserved. 
//  http://www.zlg.cn
//! @file       StatusCode.h
//! @author     ZengBenSen
//! @date       2012.10.18
//! @version    V1.13
//! @brief		状态码定义
//!                 - V1.13 2012.01.07  韩远强  增加模块I2C、UART状态宏定义，增加其它相关状态
//!					- V1.12 2012.10.18	曾本森	增加STATUS_IDLE
//!					- V1.11 2012.06.26	曾本森  增加STATUS_POWER_SHORTAGE 和 STATUS_HANDLE_ERROR
//!					- V1.10 2012.03.14	曾本森  查证‘NY’是‘NOT YET’的缩写，所以‘STATUS_NY_IMPLEMENTED (0xD9)’
//!						和‘STATUS_NY_IMPLEMENTED_ERROR (0xF5)’定义重复，则删除‘STATUS_NY_IMPLEMENTED (0xD9)’；
//!						根据使用习惯见‘STATUS_IMPLEMENTED_FAILED (0xD0)’改为‘STATUS_EXECUTE_FAILED’
//!					- V1.02 2011.05.01	曾本森	将ISO14443和PLUS CPU卡的专用错误码去掉类型修饰，变为通用错误码
//!					- V1.01	2009.06.24	曾本森	将有符号数改为无符号数
//!					- V1.00	2008.01.09	曾本森	创建文档
// ======================================================================================================
#ifndef __STATUS_CODE_H
#define __STATUS_CODE_H

#ifdef __cplusplus
	extern "C" {
#endif

//! 状态码定义
#define STATUS_SUCCESS                  (0)		//!< 操作成功
#define STATUS_COMM_OK					0x00	//!< 成功
#define STATUS_COMM_TIMEOUT				0x01	//!< 通信超时
#define STATUS_COMM_DVC_NOT_ONLINE		0x02	//!< 设备不在线
#define STATUS_COMM_ERROR				0x03	//!< 通信错误
#define STATUS_CMD_ERROR				0x04	//!< 命令错误
#define STATUS_FAIL                     0x05    //!< 操作失败，无帧数据
// #define STATUS_RFU06
// #define STATUS_RFU07
// #define STATUS_RFU08
// #define STATUS_RFU09
// #define STATUS_RFU0A
// #define STATUS_RFU0B
// #define STATUS_RFU0C
// #define STATUS_RFU0D
// #define STATUS_RFU0E
// #define STATUS_RFU0F
//! 模块状态 
#define STATUS_I2CMODE                  0x10    //!< 模块是I2C通讯模式
#define STATUS_UARTMODE                 0x11    //!< 模块是UART通讯模式
// #define STATUS_RFU12
// #define STATUS_RFU13
// #define STATUS_RFU14
// #define STATUS_RFU15
// #define STATUS_RFU16
// #define STATUS_RFU17
// #define STATUS_RFU18
// #define STATUS_RFU19
// #define STATUS_RFU1A
// #define STATUS_RFU1B
// #define STATUS_RFU1C
// #define STATUS_RFU1D
// #define STATUS_RFU1E
// #define STATUS_RFU1F
// 
// #define STATUS_RFU20
// #define STATUS_RFU21
// #define STATUS_RFU22
// #define STATUS_RFU23
// #define STATUS_RFU24
// #define STATUS_RFU25
// #define STATUS_RFU26
// #define STATUS_RFU27
// #define STATUS_RFU28
// #define STATUS_RFU29
// #define STATUS_RFU2A
// #define STATUS_RFU2B
// #define STATUS_RFU2C
// #define STATUS_RFU2D
// #define STATUS_RFU2E
// #define STATUS_RFU2F
// 
// #define STATUS_RFU30
// #define STATUS_RFU31
// #define STATUS_RFU32
// #define STATUS_RFU33
// #define STATUS_RFU34
// #define STATUS_RFU35
// #define STATUS_RFU36
// #define STATUS_RFU37
// #define STATUS_RFU38
// #define STATUS_RFU39
// #define STATUS_RFU3A
// #define STATUS_RFU3B
// #define STATUS_RFU3C
// #define STATUS_RFU3D
// #define STATUS_RFU3E
// #define STATUS_RFU3F
// 
// 0x40 - 0x7F用户自定义错误，其意义不在此解释
// #define STATUS_RFU40
// #define STATUS_RFU41
// #define STATUS_RFU42
// #define STATUS_RFU43
// #define STATUS_RFU44
// #define STATUS_RFU45
// #define STATUS_RFU46
// #define STATUS_RFU47
// #define STATUS_RFU48
// #define STATUS_RFU49
// #define STATUS_RFU4A
// #define STATUS_RFU4B
// #define STATUS_RFU4C
// #define STATUS_RFU4D
// #define STATUS_RFU4E
// #define STATUS_RFU4F
// 
// #define STATUS_RFU50
// #define STATUS_RFU51
// #define STATUS_RFU52
// #define STATUS_RFU53
// #define STATUS_RFU54
// #define STATUS_RFU55
// #define STATUS_RFU56
// #define STATUS_RFU57
// #define STATUS_RFU58
// #define STATUS_RFU59
// #define STATUS_RFU5A
// #define STATUS_RFU5B
// #define STATUS_RFU5C
// #define STATUS_RFU5D
// #define STATUS_RFU5E
// #define STATUS_RFU5F
// 
// #define STATUS_RFU60
// #define STATUS_RFU61
// #define STATUS_RFU62
// #define STATUS_RFU63
// #define STATUS_RFU64
// #define STATUS_RFU65
// #define STATUS_RFU66
// #define STATUS_RFU67
// #define STATUS_RFU68
// #define STATUS_RFU69
// #define STATUS_RFU6A
// #define STATUS_RFU6B
// #define STATUS_RFU6C
// #define STATUS_RFU6D
// #define STATUS_RFU6E
// #define STATUS_RFU6F
// 
// #define STATUS_RFU70
// #define STATUS_RFU71
// #define STATUS_RFU72
// #define STATUS_RFU73
// #define STATUS_RFU74
// #define STATUS_RFU75
// #define STATUS_RFU76
// #define STATUS_RFU77
// #define STATUS_RFU78
// #define STATUS_RFU79
// #define STATUS_RFU7A
// #define STATUS_RFU7B
// #define STATUS_RFU7C
// #define STATUS_RFU7D
// #define STATUS_RFU7E
// #define STATUS_RFU7F
// 
// #define STATUS_RFU80
// #define STATUS_RFU81
// #define STATUS_RFU82
// #define STATUS_RFU83
// #define STATUS_RFU84
// #define STATUS_RFU85
// #define STATUS_RFU86
// #define STATUS_RFU87
// #define STATUS_RFU88
// #define STATUS_RFU89
#define STATUS_IDLE						0x8A	//!< 空闲
#define STATUS_ABORT					0x8B	//!< 中止（非正常停止）
#define STATUS_BUSY						0x8C	//!< 忙（正在执行其他命令）
#define STATUS_EXECUTING				0x8D	//!< 正在执行（命令未执行完）
#define STATUS_SENDING					0x8E	//!< 正在发送（数据未发送完）
#define STATUS_RECEIVING				0x8F	//!< 正在接收（未超时，数据未接收完）
		
#define STATUS_RFU90					0x90	//!< RFU 0x90
#define STATUS_RFU91					0x91	//!< RFU 0x91	
#define STATUS_RFU92					0x92	//!< RFU 0x92
#define STATUS_SEQ_ERROR				0x93	//!< 数据分包错误
#define STATUS_ADR_ERROR				0x94	//!< 不是本机地址，或子地址错误	
#define STATUS_RCV_LENGTH_ERR			0x95	//!< 接收的长度有误
#define STATUS_MAC_ERR					0x96	//!< MAC校验有误
#define STATUS_USER_DATA_LEN_ERR		0x97	//!< 用户输入数据长度有误
#define STATUS_USER_PARAMETER_ERR		0x98	//!< 用户输入的参数有误
#define STATUS_USER_DATA_TOO_MANY		0x99	//!< 用户数据过多
#define STATUS_USER_BUF_TOO_SMALL		0x9A	//!< 用户缓冲区太小
#define STATUS_FUNCTION_ERR				0x9B	//!< 功能错误 
#define STATUS_INVALID_COMMAND			0x9C	//!< 无效命令/不支持的命令
#define STATUS_NOT_SAME_CARD			0x9D	//!< 不是同一张卡				
#define STATUS_TRAN_NOT_COMPLETED		0x9E	//!< 交易未完成
#define STATUS_APP_NOT_ENABLED_ERR		0x9F	//!< 应用未启用

#define STATUS_CARD_TYPE_ERR			0xA0	//!< 卡类型错误
#define STATUS_RFUA1					0xA1	//!< RFU 0xA1
#define STATUS_RFUA2					0xA2	//!< RFU 0xA2
#define STATUS_RFUA3					0xA3	//!< RFU 0xA3
#define STATUS_RFUA4					0xA4	//!< RFU 0xA4
#define STATUS_RFUA5					0xA5	//!< RFU 0xA5
#define STATUS_RFUA6					0xA6	//!< RFU 0xA6
#define STATUS_RFUA7					0xA7	//!< RFU 0xA7
#define STATUS_RFUA8					0xA8	//!< RFU 0xA8
#define STATUS_RFUA9					0xA9	//!< RFU 0xA9
#define STATUS_RFUAA					0xAA	//!< RFU 0xAA
#define STATUS_RFUAB					0xAB	//!< RFU 0xAB
#define STATUS_IID_ERROR				0xAC	//!< IID错误(不支持的IID)
#define STATUS_VPC_TIMEOUT				0xAD	//!< 存在中继攻击
#define STATUS_NOT_SUPPORT_VC			0xAE	//!< 不支持虚拟卡操作
#define STATUS_PCD_CAP_ERROR			0xAF	//!< PCD能力有误

#define STATUS_RFUB0					0xB0	//!< RFU 0xB0
#define STATUS_RFUB1					0xB1	//!< RFU 0xB1
#define STATUS_RFUB2					0xB2	//!< RFU 0xB2
#define STATUS_RFUB3					0xB3	//!< RFU 0xB3
#define STATUS_RFUB4					0xB4	//!< RFU 0xB4
#define STATUS_RFUB5					0xB5	//!< RFU 0xB5
#define STATUS_AUTH_ERROR				0xB6	//!< 验证错误
#define STATUS_CMD_OVERFLOW				0xB7	//!< 命令(数据)溢出
#define STATUS_INVALID_MAC				0xB8	//!< 无效的MAC
#define STATUS_INVALID_BLOCK			0xB9	//!< 无效的块
#define STATUS_INEXISTENT_BLOCK			0xBA	//!< 不存在的块
#define STATUS_NOT_SATISFIED			0xBB	//!< 安全等级不足 Security level is insufficient
#define STATUS_MORE_THAN_RETRIES		0xBC	//!< 超过重试次数
#define STATUS_HANDLE_ERROR				0xBD	//!< 句柄错误	
#define STATUS_INTERNAL_COMM_ERRPR		0xBE	//!< 设备内部通信错误
#define STATUS_GENERAL_ERROR			0xBF	//!< 普通操作错误

#define STATUS_NO_DATA_ERROR			0xC0	//!< 无数据错误(需要发送数据时,FIFO中无数据)
#define STATUS_INTEG_ERROR				0xC1	//!< 数据完整性错误(包括CRC或奇偶校验错误)
#define STATUS_NAD_ERROR				0xC2	//!< NAD错误
#define STATUS_INVALID_VALUE			0xC3	//!< 值块格式错误
#define STATUS_PERORM_ERROR				0xC4	//!< 命令执行结果错误
#define STATUS_EDC_ERROR				0xC5	//!< 校验字节有误(通信校验)
#define STATUS_APDU_ERROR				0xC6	//!< APDU命令错误
#define STATUS_SEND_ERROR				0xC7	//!< 发送错误
#define STATUS_LENGTH_ERROR				0xC8	//!< 长度错误
#define STATUS_NAK_ERROR				0xC9	//!< NAK错误
#define STATUS_PCB_ERROR				0xCA	//!< PCB错误
#define STATUS_CID_ERROR  			    0xCB	//!< CID错误
#define STATUS_BLOCK_FORMAT_ERROR       0xCC	//!< 分组帧格式错误 
#define STATUS_PPS_ERROR  			    0xCD	//!< PPSS错误
#define STATUS_ATS_ERROR			    0xCE	//!< ATS错误(ISO14443-4); 复位应答错(ISO7816-3)
#define STATUS_CARD_COMM_ERROR			0xCF	//!< 与卡片之间的通信出错

#define STATUS_EXECUTE_FAILED			0xD0	//!< 执行失败
#define STATUS_COMPARE_ERROR			0xD1	//!< 比较错误
#define STATUS_ACCESS_BANNED			0xD2	//!< 禁止访问
#define STATUS_ACCESS_ERROR				0xD3 	//!< 存储器访问错误
#define STATUS_BCC_ERROR	            0xD4 	//!< BCC校验错误
#define STATUS_NO_TARGET                0xD5   	//!< 无目标
#define STATUS_UNDEFINE_ERROR			0xD6	//!< 未定义的错误
#define STATUS_NO_RF_FIELD	            0xD7   	//!< 无RF场错误
#define STATUS_ACCESS_TIMEOUT			0xD8	//!< 访问超时
#define STATUS_POWER_SHORTAGE			0xD9	//!< 功率不足
#define STATUS_SERNR_ERROR				0xDA	//!< 不支持的防碰撞等级
#define STATUS_NO_BITWISE_ANTICOLL		0xDB	//!< 不支持Bit帧防冲突
#define STATUS_INIT_ERROR				0xDC	//!< 初始化错误
#define STATUS_TEMP_ERROR        	    0xDD	//!< 温度有误
#define STATUS_INVALID_DEVICE_STATE     0xDE	//!< 驱动错误
#define STATUS_INSUFFICIENT_RESOURCES   0xDF	//!< 系统资源不足

#define STATUS_OTHER_ERROR              0xE0	//!< 其他错误
#define STATUS_NO_ID_AVAILABLE          0xE1	//!< 无空闲ID可用
#define STATUS_ID_NOT_IN_USE            0xE2	//!< 指定的ID不在使用
#define STATUS_INSTANCE_ALREADY_IN_USE  0xE3	//!< INSTANCE 已被使用
#define STATUS_ID_ALREADY_IN_USE        0xE4	//!< ID已被使用
#define STATUS_SLOT_ALREADY_IN_USE		0xE4	//!< 卡座已被使用
#define STATUS_WRONG_HALT_FORMAT        0xE5	//!< 挂起格式错误
#define STATUS_WRONG_UID_CHECKBYTE      0xE6	//!< 目标UID检测错误
#define STATUS_TARGET_RESET_TOX         0xE7	//!< 目标复位
#define STATUS_TARGET_SET_TOX           0xE8	//!< 目标设置超时
#define STATUS_TARGET_DEADLOCKED        0xE9	//!< 目标死锁
#define STATUS_BLOCKNR_NOT_EQUAL        0xEA	//!< 通信块错误
#define STATUS_ACK_SUPPOSED             0xEB	//!< ACK错误
#define STATUS_AUTHENT_ERROR            0xEC	//!< 验证错误
#define STATUS_INTERFACE_NOT_ENABLED    0xED	//!< 接口未激活
#define STATUS_INVALID_FORMAT           0xEE	//!< 无效格式
#define STATUS_INTERFACE_ERROR          0xEF	//!< 主机接口错误

#define STATUS_UNSUPPORTED_COMMAND      0xF0	//!< 不支持的命令
#define STATUS_UNSUPPORTED_PARAMETER    0xF1	//!< 不支持的参数
#define STATUS_INVALID_PARAMETER        0xF2	//!< 无效参数
#define STATUS_USER_BUFFER_FULL         0xF3	//!< 用户缓冲区满
#define STATUS_FIFO_WRITE_ERROR         0xF4	//!< FIFO写错误
#define STATUS_NOT_YET_IMPLEMENTED		0xF5	//!< 尚未生效
#define STATUS_PROTOCOL_ERROR           0xF6	//!< 协议有误
#define STATUS_BUFFER_OVERFLOW          0xF7	//!< BUF溢出错误
#define STATUS_FIFO_OVERFLOW			0xF7	//!< FIFO溢出错误
#define STATUS_ACCESS_DENIED            0xF8	//!< 写禁止
#define STATUS_BUFFER_TOO_SMALL         0xF9	//!< 缓冲区过小
#define STATUS_COLLISION_ERROR          0xFA	//!< 位冲突错误
#define STATUS_FRAMING_ERROR            0xFB	//!< 帧错误
#define STATUS_BIT_COUNT_ERROR			0xFC	//!< 接收位计数器错误
#define STATUS_PARITY_ERROR             0xFD	//!< 奇偶校验错误
#define STATUS_CRC_ERROR                0xFE	//!< CRC校验错误
#define STATUS_IO_TIMEOUT               0xFF	//!< 无应答错误
// =======================================================================================
#ifdef __cplusplus
	}
#endif
#endif          // __STATUS_CODE_H


 



