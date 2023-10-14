#include "HalUART.h"

void HalUART1PortInit(void)
{
	PORT_SET_TYPE();
	PORT_SET_TYPE();
}

void HalUART1Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	HalUART1PortInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitStructure.USART_BaudRate = 9600; // Tốc độ baud rate
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // Độ dài word là 8 bit
	USART_InitStructure.USART_StopBits = USART_StopBits_1; // 1 stop bit
	USART_InitStructure.USART_Parity = USART_Parity_No; // Không sử dụng kiểm tra chẵn lẻ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Không sử dụng điều khiển cứng
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // Chế độ nhận và truyền

	USART_Init(USARTx, &USART_InitStructure);
}
