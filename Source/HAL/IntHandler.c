#include "HalUART.h"
#include "DevUART.h"

void USART1_IRQHandler(void)
{
    // Kiểm tra ngắt nhận dữ liệu (RXNE)
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        // Xử lý việc nhận dữ liệu
    	DevUART1ReceiveData();
        // Xử lý dữ liệu nhận được ở đây
    }

    // Kiểm tra ngắt truyền dữ liệu (TXE)
    if (USART_GetITStatus(USART1, USART_IT_TXE) == SET)
    {
        // Xử lý việc truyền dữ liệu
    	DevUART1TransmitData();
        // Ghi dữ liệu vào thanh ghi DR để truyền

    }
}

void USART2_IRQHandler(void)
{

}

void USART3_IRQHandler(void)
{

}

void UART4_IRQHandler(void)
{

}

void UART5_IRQHandler(void)
{

}



