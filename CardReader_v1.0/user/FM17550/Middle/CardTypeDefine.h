// ======================================================================================================
//  Copyright (c) 2011 Guangzhou Zhiyuan Electronics Co., Ltd. All rights reserved. 
//  http://www.zlg.cn
//! @file       CardTypeDefine.h
//! @author     ZengBenSen
//! @date       2013.01.24
//! @version    V1.00
//! @brief      �����Ͷ���          
//!					- V1.00	2013.01.24	����ɭ	�����ļ�
// ======================================================================================================
#ifndef __CARD_TYPE_DEFINE_H
#define __CARD_TYPE_DEFINE_H

//============= �������� ================================================================================
// ������
#define CARD_TYPE_ISO14443A				0x3F		//!< ISO14443A
#define CARD_TYPE_ISO14443B				0x5F		//!< ISO14443B
#define CARD_TYPE_ISO115693				0x7F		//!< ISO115693
#define CARD_TYPE_ISO7816_3				0x9F		//!< ISO7816_3
#define CARD_TYPE_INVALID				0xFF        // ��Ч��/��Ч��SAK
// 000 0 0xxx  MF0ϵ��
#define CARD_TYPE_MF0					0x00        // MF0ϵ�п�
#define CARD_TYPE_UL					0x01        // 
#define CARD_TYPE_ULC					0x02
// 000 0 1xxx  MF1ϵ��		
#define CARD_TYPE_MF1					0x08        // MF1ϵ�п�        
#define CARD_TYPE_MINI					0x09
#define CARD_TYPE_S50					0x0A
#define CARD_TYPE_S70					0x0B
// 000 1 0xxx  MF3ϵ��		
#define CARD_TYPE_MF3					0x10        // MF3ϵ�п�
#define CARD_TYPE_D20					0x11
#define CARD_TYPE_D21					0x12
#define CARD_TYPE_D40					0x13
#define CARD_TYPE_D41					0x14
#define CARD_TYPE_D80					0x15
#define CARD_TYPE_D81					0x16
// 000 1 1xxx  PLUS CPU ϵ��		
#define CARD_TYPE_MFP					0x18        // PLUS CPU ϵ�п�
#define CARD_TYPE_MFP2_SL2				0x19        // PLUS CPU 2K(SL2)
#define CARD_TYPE_MFP4_SL2				0x1A        // PLUS CPU 4K(SL2)
#define CARD_TYPE_MFPS_SL3				0x1B        // PLUS S     2/4K(SL3)
#define CARD_TYPE_MFPX_SL3				0x1C        // PLUS X     2/4K(SL3)
// 001 0 xxxx  ISO14443-4 TypeA ϵ��
#define CARD_TYPE_ISO14443A_4			0x20        //!< ISO14443-4 TypeA ϵ�п�
#define CARD_TYPE_FM1208				0x21		//!< ����΢����FM1208CPU��
#define CARD_TYPE_FM12AG08				0x22		//!< ����΢����FM12AG08 ����CPU��
//=======================================================================================================
#endif				// __CARD_TYPE_DEFINE_H











