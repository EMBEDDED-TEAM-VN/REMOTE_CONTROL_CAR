#include "HalUART.h"


void HalUART1PortInit(void)
{
	PORT_SET_TYPE(PMAP_ONC_PA09,PORT_ALTF);
	PORT_SET_TYPE(PMAP_ONC_PA10,PORT_IN);
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

	USART_Init(USART1, &USART_InitStructure);

	// Cho phép ngắt truyền/nhận dữ liệu UART
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	// Cho phép UART
	USART_Cmd(USART1, ENABLE);

	// Cấu hình ngắt UART
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

