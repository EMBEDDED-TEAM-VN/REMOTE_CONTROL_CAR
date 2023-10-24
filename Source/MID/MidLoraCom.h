#include "DevUART.h"
#include "SystemLib.h"
#include "Macro.h"

#define LORA_COMM(nSize,pRXdService)    DevSetUARTService(UART_CHANEL_1,nSize,pRXdService)

PUBLIC void MidLoraInit(void);
PUBLIC void MidLoraCommLoop(void);
