/*
 * MidLoraCom.h
 *
 *  Created on: Oct 28, 2023
 *      Author: DINH KHANH
 */

#ifndef MID_MIDLORACOM_H_
#define MID_MIDLORACOM_H_

#include "DevUART.h"
#include "SystemLib.h"
#include "SysTimer.h"

#define LORA_COMM(nSize,pRXdService)    DevSetUARTService(UART_CHANEL_1,nSize,pRXdService)
#define LORA_TRANSMIT(pRXdService)

extern PUBLIC void (*TransmitDataLora)(U08*, U16);
PUBLIC void MidLoraInit(void);
PUBLIC void MidLoraCommLoop(void);
PUBLIC void SetDisplayText(U08 u08Data);
PUBLIC void SetSound(U08 u08Data);



#endif /* MID_MIDLORACOM_H_ */
