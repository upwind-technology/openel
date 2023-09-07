/*
 * openEL_registryConfig.c
 *
 *  Created on: 2023/09/07
 *      Author: OpenEL-WG
 */

#include "openEL.h"
#include "openEL_registry.h"

#include "openEL_TempSensor.h" /* デバイスベンダーから提供される定義ファイル */

/** デバイスを登録する */
const HAL_REG_T HalRegTbl[] = {
/*		DevKind		Vendor		Product			function table		component size								*/
		{0x0008,	0x0000000C,	0x00000001,		&HalTempSen001Tbl,	sizeof(HALSENSOR_T)		},
};

const int32_t hal_szRegTbl = sizeof(HalRegTbl)/sizeof(HAL_REG_T);


