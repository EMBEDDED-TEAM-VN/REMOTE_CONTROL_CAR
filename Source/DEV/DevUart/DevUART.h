#include "String.h"
#include "Keyword.h"
#include "HalUART.h"
#include "Macro.h"
#include <stdio.h>

#define UART_CHANEL_1			1
#define UART_CHANEL_2			2
#define UART_CHANEL_3			3
#define UART_CHANEL_4			4
#define UART_CHANEL_5			5

PUBLIC void DevUARTInit(void);
PUBLIC void DevMainLoodUART(void);
PUBLIC void DevUART1ReceiveData(void);
PUBLIC void DevUART1TransmitData(void);
PUBLIC void DevSetUART1TransmitData(U08* pu08Data, U16 u16DataSize);
PUBLIC void DevSetUARTService(U08 u08Chanel, U08 u08ServiceSize, void (*pReceiveService)(void *));
