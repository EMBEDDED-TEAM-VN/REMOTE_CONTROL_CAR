#include "stm32f10x_usart.h"
#include "Portmap.h"

#define HAL_SET_BUFFER_UART1(DATA)			USART_SendData(USART1,DATA)
#define HAL_IS_BUFFER_UART1_EMPTY()			USART_GetFlagStatus(USART1,USART_FLAG_TXE)
#define HAL_GET_BUFFER_UART1()				USART_ReceiveData(USART1)

void HalUART1PortInit(void);
void HalUART1Init(void);

