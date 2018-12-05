// =======================================================================================
//  Copyright (c) 2011 Guangzhou Zhiyuan Electronics Co., Ltd. All rights reserved. 
//  http://www.zlg.cn
//! @file       StatusCode.h
//! @author     ZengBenSen
//! @date       2012.10.18
//! @version    V1.13
//! @brief		״̬�붨��
//!                 - V1.13 2012.01.07  ��Զǿ  ����ģ��I2C��UART״̬�궨�壬�����������״̬
//!					- V1.12 2012.10.18	����ɭ	����STATUS_IDLE
//!					- V1.11 2012.06.26	����ɭ  ����STATUS_POWER_SHORTAGE �� STATUS_HANDLE_ERROR
//!					- V1.10 2012.03.14	����ɭ  ��֤��NY���ǡ�NOT YET������д�����ԡ�STATUS_NY_IMPLEMENTED (0xD9)��
//!						�͡�STATUS_NY_IMPLEMENTED_ERROR (0xF5)�������ظ�����ɾ����STATUS_NY_IMPLEMENTED (0xD9)����
//!						����ʹ��ϰ�߼���STATUS_IMPLEMENTED_FAILED (0xD0)����Ϊ��STATUS_EXECUTE_FAILED��
//!					- V1.02 2011.05.01	����ɭ	��ISO14443��PLUS CPU����ר�ô�����ȥ���������Σ���Ϊͨ�ô�����
//!					- V1.01	2009.06.24	����ɭ	���з�������Ϊ�޷�����
//!					- V1.00	2008.01.09	����ɭ	�����ĵ�
// ======================================================================================================
#ifndef __STATUS_CODE_H
#define __STATUS_CODE_H

#ifdef __cplusplus
	extern "C" {
#endif

//! ״̬�붨��
#define STATUS_SUCCESS                  (0)		//!< �����ɹ�
#define STATUS_COMM_OK					0x00	//!< �ɹ�
#define STATUS_COMM_TIMEOUT				0x01	//!< ͨ�ų�ʱ
#define STATUS_COMM_DVC_NOT_ONLINE		0x02	//!< �豸������
#define STATUS_COMM_ERROR				0x03	//!< ͨ�Ŵ���
#define STATUS_CMD_ERROR				0x04	//!< �������
#define STATUS_FAIL                     0x05    //!< ����ʧ�ܣ���֡����
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
//! ģ��״̬ 
#define STATUS_I2CMODE                  0x10    //!< ģ����I2CͨѶģʽ
#define STATUS_UARTMODE                 0x11    //!< ģ����UARTͨѶģʽ
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
// 0x40 - 0x7F�û��Զ�����������岻�ڴ˽���
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
#define STATUS_IDLE						0x8A	//!< ����
#define STATUS_ABORT					0x8B	//!< ��ֹ��������ֹͣ��
#define STATUS_BUSY						0x8C	//!< æ������ִ���������
#define STATUS_EXECUTING				0x8D	//!< ����ִ�У�����δִ���꣩
#define STATUS_SENDING					0x8E	//!< ���ڷ��ͣ�����δ�����꣩
#define STATUS_RECEIVING				0x8F	//!< ���ڽ��գ�δ��ʱ������δ�����꣩
		
#define STATUS_RFU90					0x90	//!< RFU 0x90
#define STATUS_RFU91					0x91	//!< RFU 0x91	
#define STATUS_RFU92					0x92	//!< RFU 0x92
#define STATUS_SEQ_ERROR				0x93	//!< ���ݷְ�����
#define STATUS_ADR_ERROR				0x94	//!< ���Ǳ�����ַ�����ӵ�ַ����	
#define STATUS_RCV_LENGTH_ERR			0x95	//!< ���յĳ�������
#define STATUS_MAC_ERR					0x96	//!< MACУ������
#define STATUS_USER_DATA_LEN_ERR		0x97	//!< �û��������ݳ�������
#define STATUS_USER_PARAMETER_ERR		0x98	//!< �û�����Ĳ�������
#define STATUS_USER_DATA_TOO_MANY		0x99	//!< �û����ݹ���
#define STATUS_USER_BUF_TOO_SMALL		0x9A	//!< �û�������̫С
#define STATUS_FUNCTION_ERR				0x9B	//!< ���ܴ��� 
#define STATUS_INVALID_COMMAND			0x9C	//!< ��Ч����/��֧�ֵ�����
#define STATUS_NOT_SAME_CARD			0x9D	//!< ����ͬһ�ſ�				
#define STATUS_TRAN_NOT_COMPLETED		0x9E	//!< ����δ���
#define STATUS_APP_NOT_ENABLED_ERR		0x9F	//!< Ӧ��δ����

#define STATUS_CARD_TYPE_ERR			0xA0	//!< �����ʹ���
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
#define STATUS_IID_ERROR				0xAC	//!< IID����(��֧�ֵ�IID)
#define STATUS_VPC_TIMEOUT				0xAD	//!< �����м̹���
#define STATUS_NOT_SUPPORT_VC			0xAE	//!< ��֧�����⿨����
#define STATUS_PCD_CAP_ERROR			0xAF	//!< PCD��������

#define STATUS_RFUB0					0xB0	//!< RFU 0xB0
#define STATUS_RFUB1					0xB1	//!< RFU 0xB1
#define STATUS_RFUB2					0xB2	//!< RFU 0xB2
#define STATUS_RFUB3					0xB3	//!< RFU 0xB3
#define STATUS_RFUB4					0xB4	//!< RFU 0xB4
#define STATUS_RFUB5					0xB5	//!< RFU 0xB5
#define STATUS_AUTH_ERROR				0xB6	//!< ��֤����
#define STATUS_CMD_OVERFLOW				0xB7	//!< ����(����)���
#define STATUS_INVALID_MAC				0xB8	//!< ��Ч��MAC
#define STATUS_INVALID_BLOCK			0xB9	//!< ��Ч�Ŀ�
#define STATUS_INEXISTENT_BLOCK			0xBA	//!< �����ڵĿ�
#define STATUS_NOT_SATISFIED			0xBB	//!< ��ȫ�ȼ����� Security level is insufficient
#define STATUS_MORE_THAN_RETRIES		0xBC	//!< �������Դ���
#define STATUS_HANDLE_ERROR				0xBD	//!< �������	
#define STATUS_INTERNAL_COMM_ERRPR		0xBE	//!< �豸�ڲ�ͨ�Ŵ���
#define STATUS_GENERAL_ERROR			0xBF	//!< ��ͨ��������

#define STATUS_NO_DATA_ERROR			0xC0	//!< �����ݴ���(��Ҫ��������ʱ,FIFO��������)
#define STATUS_INTEG_ERROR				0xC1	//!< ���������Դ���(����CRC����żУ�����)
#define STATUS_NAD_ERROR				0xC2	//!< NAD����
#define STATUS_INVALID_VALUE			0xC3	//!< ֵ���ʽ����
#define STATUS_PERORM_ERROR				0xC4	//!< ����ִ�н������
#define STATUS_EDC_ERROR				0xC5	//!< У���ֽ�����(ͨ��У��)
#define STATUS_APDU_ERROR				0xC6	//!< APDU�������
#define STATUS_SEND_ERROR				0xC7	//!< ���ʹ���
#define STATUS_LENGTH_ERROR				0xC8	//!< ���ȴ���
#define STATUS_NAK_ERROR				0xC9	//!< NAK����
#define STATUS_PCB_ERROR				0xCA	//!< PCB����
#define STATUS_CID_ERROR  			    0xCB	//!< CID����
#define STATUS_BLOCK_FORMAT_ERROR       0xCC	//!< ����֡��ʽ���� 
#define STATUS_PPS_ERROR  			    0xCD	//!< PPSS����
#define STATUS_ATS_ERROR			    0xCE	//!< ATS����(ISO14443-4); ��λӦ���(ISO7816-3)
#define STATUS_CARD_COMM_ERROR			0xCF	//!< �뿨Ƭ֮���ͨ�ų���

#define STATUS_EXECUTE_FAILED			0xD0	//!< ִ��ʧ��
#define STATUS_COMPARE_ERROR			0xD1	//!< �Ƚϴ���
#define STATUS_ACCESS_BANNED			0xD2	//!< ��ֹ����
#define STATUS_ACCESS_ERROR				0xD3 	//!< �洢�����ʴ���
#define STATUS_BCC_ERROR	            0xD4 	//!< BCCУ�����
#define STATUS_NO_TARGET                0xD5   	//!< ��Ŀ��
#define STATUS_UNDEFINE_ERROR			0xD6	//!< δ����Ĵ���
#define STATUS_NO_RF_FIELD	            0xD7   	//!< ��RF������
#define STATUS_ACCESS_TIMEOUT			0xD8	//!< ���ʳ�ʱ
#define STATUS_POWER_SHORTAGE			0xD9	//!< ���ʲ���
#define STATUS_SERNR_ERROR				0xDA	//!< ��֧�ֵķ���ײ�ȼ�
#define STATUS_NO_BITWISE_ANTICOLL		0xDB	//!< ��֧��Bit֡����ͻ
#define STATUS_INIT_ERROR				0xDC	//!< ��ʼ������
#define STATUS_TEMP_ERROR        	    0xDD	//!< �¶�����
#define STATUS_INVALID_DEVICE_STATE     0xDE	//!< ��������
#define STATUS_INSUFFICIENT_RESOURCES   0xDF	//!< ϵͳ��Դ����

#define STATUS_OTHER_ERROR              0xE0	//!< ��������
#define STATUS_NO_ID_AVAILABLE          0xE1	//!< �޿���ID����
#define STATUS_ID_NOT_IN_USE            0xE2	//!< ָ����ID����ʹ��
#define STATUS_INSTANCE_ALREADY_IN_USE  0xE3	//!< INSTANCE �ѱ�ʹ��
#define STATUS_ID_ALREADY_IN_USE        0xE4	//!< ID�ѱ�ʹ��
#define STATUS_SLOT_ALREADY_IN_USE		0xE4	//!< �����ѱ�ʹ��
#define STATUS_WRONG_HALT_FORMAT        0xE5	//!< �����ʽ����
#define STATUS_WRONG_UID_CHECKBYTE      0xE6	//!< Ŀ��UID������
#define STATUS_TARGET_RESET_TOX         0xE7	//!< Ŀ�긴λ
#define STATUS_TARGET_SET_TOX           0xE8	//!< Ŀ�����ó�ʱ
#define STATUS_TARGET_DEADLOCKED        0xE9	//!< Ŀ������
#define STATUS_BLOCKNR_NOT_EQUAL        0xEA	//!< ͨ�ſ����
#define STATUS_ACK_SUPPOSED             0xEB	//!< ACK����
#define STATUS_AUTHENT_ERROR            0xEC	//!< ��֤����
#define STATUS_INTERFACE_NOT_ENABLED    0xED	//!< �ӿ�δ����
#define STATUS_INVALID_FORMAT           0xEE	//!< ��Ч��ʽ
#define STATUS_INTERFACE_ERROR          0xEF	//!< �����ӿڴ���

#define STATUS_UNSUPPORTED_COMMAND      0xF0	//!< ��֧�ֵ�����
#define STATUS_UNSUPPORTED_PARAMETER    0xF1	//!< ��֧�ֵĲ���
#define STATUS_INVALID_PARAMETER        0xF2	//!< ��Ч����
#define STATUS_USER_BUFFER_FULL         0xF3	//!< �û���������
#define STATUS_FIFO_WRITE_ERROR         0xF4	//!< FIFOд����
#define STATUS_NOT_YET_IMPLEMENTED		0xF5	//!< ��δ��Ч
#define STATUS_PROTOCOL_ERROR           0xF6	//!< Э������
#define STATUS_BUFFER_OVERFLOW          0xF7	//!< BUF�������
#define STATUS_FIFO_OVERFLOW			0xF7	//!< FIFO�������
#define STATUS_ACCESS_DENIED            0xF8	//!< д��ֹ
#define STATUS_BUFFER_TOO_SMALL         0xF9	//!< ��������С
#define STATUS_COLLISION_ERROR          0xFA	//!< λ��ͻ����
#define STATUS_FRAMING_ERROR            0xFB	//!< ֡����
#define STATUS_BIT_COUNT_ERROR			0xFC	//!< ����λ����������
#define STATUS_PARITY_ERROR             0xFD	//!< ��żУ�����
#define STATUS_CRC_ERROR                0xFE	//!< CRCУ�����
#define STATUS_IO_TIMEOUT               0xFF	//!< ��Ӧ�����
// =======================================================================================
#ifdef __cplusplus
	}
#endif
#endif          // __STATUS_CODE_H


 



