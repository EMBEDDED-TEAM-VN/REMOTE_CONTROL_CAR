/*
 * DevI2C.h
 *
 *  Created on: Dec 5, 2023
 *      Author: DINH KHANH
 */

#ifndef DEV_DEVI2C_DEVI2C_H_
#define DEV_DEVI2C_DEVI2C_H_

#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Macro.h"
#include "Keyword.h"
#include "SysTimer.h"

PUBLIC void DevLCDInit(void);
PUBLIC void DevLCDSetCursor(U08 row, U08 col);
PUBLIC void DevLCDPrintString(char *str);
PUBLIC void DevLCDClear(void);


#endif /* DEV_DEVI2C_DEVI2C_H_ */
