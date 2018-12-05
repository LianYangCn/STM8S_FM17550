// ======================================================================================================
//  Copyright (c) 2011 Guangzhou Zhiyuan Electronics Co., Ltd. All rights reserved. 
//  http://www.zlg.cn
//! @file       Utility.c
//! @author     HanYuanQiang
//! @date       2013.01.07
//! @version    V1.01
//! @brief      公共函数
//!                 - V1.01 2012.01.07  韩远强  增加计算字节异或取反校验函数
//!					- V1.00 2012.04.17	曾本森 创建文档
// ======================================================================================================
#ifndef __UTILITY_H
#define __UTILITY_H

#include "stm8s.h"

#ifdef __cplusplus
	extern "C" {
#endif
// ======================================================================================================
//! @brief			计算字节累加和
//! @param[in]		*p		-- 计算的数据
//! @param[in]		nBytes	-- 字节数
//! @return			字节累加和
// ======================================================================================================
uint32_t GetByteSum(const void *p, uint32_t nBytes);

// ======================================================================================================
//! @brief          计算字节异或取反
//! @param[in]      *p      -- 计算的数据
//! @param[in]      nBytes  -- 字节数
//! @return         字节异或取反
// ======================================================================================================
uint8_t GetByteBCC(const void *p, uint32_t nBytes);

// ======================================================================================================
//! @brief			延迟（100us为单位）
//! @param[in]		_100us		-- 延迟时间
//! @note			基于LPC1114,48MHz
// ======================================================================================================
void Delay100us(uint32_t _100us);

// ======================================================================================================
#ifdef __cplusplus
	}
#endif
#endif				// __UTILITY_H



