#include "stdint.h"
#include "Keyword.h"
#include "HalUART.h"


PUBLIC void DevUARTInit(void);
PUBLIC void DevMainLoodUART(void);
PUBLIC void DevUART1ReceiveData(void);
PUBLIC void DevUART1TransmitData(void);
PUBLIC void DevSetUART1TransmitData(U08* pu08Data, U16 u16DataSize);
PUBLIC void DevSetUARTService(U08 u08Chanel, U08 u08ServiceSize, void (*pReceiveService)(void *));
