#include "DevUART.h"

#define BUFFER_TRANSMIT_SIZE1   1000
#define BUFFER_RECEIVE_SIZE1    5
PRIVATE BOOL mbfTransmittingUART1;
PRIVATE BOOL mbfWritingTXBufferUART1;

PRIVATE U08 mau08BufferUART1ReceiveData[BUFFER_RECEIVE_SIZE1];
PRIVATE U08 mau08BufferUART1TransmitData[BUFFER_TRANSMIT_SIZE1];
PRIVATE U08 mu08ReceiveUART1Index;
PRIVATE U08 mu08ReceiveUART1ServiceSize;
PRIVATE U16 mu16TransmitPushIndex1;
PRIVATE U16 mu16TransmitPopIndex1;
PRIVATE U08 mu08TransmitData;
PRIVATE void (*mfpReceiveUART1Service)(void*);

PUBLIC void DevUARTInit(void)
{
	mbfTransmittingUART1 		= FALSE;
	mbfWritingTXBufferUART1 	= FALSE;
	mu08TransmitData 			= 0;
	mu16TransmitPushIndex1 		= 0;
	mu16TransmitPopIndex1  		= 0;
	mu08ReceiveUART1Index		= 0;
	mfpReceiveUART1Service  	= 0;
	mu08ReceiveUART1ServiceSize = 0;
	memset(mau08BufferUART1TransmitData, 0, BUFFER_TRANSMIT_SIZE1);
	memset(mau08BufferUART1ReceiveData, 0, BUFFER_RECEIVE_SIZE1);
	HalUART1Init();
}

PUBLIC void DevMainLoodUART(void)
{
	if((mu16TransmitPopIndex1 != mu16TransmitPushIndex1)&&(mbfTransmittingUART1 == FALSE))
	{
		if(HAL_IS_BUFFER_UART1_EMPTY() == TRUE)
		{
			mbfTransmittingUART1 = TRUE;
			mu08TransmitData = mau08BufferUART1TransmitData[mu16TransmitPopIndex1];
			if(mu16TransmitPopIndex1 < BUFFER_TRANSMIT_SIZE1 -1)
			{
				mu16TransmitPopIndex1++;
			}
			else
			{
				mu16TransmitPopIndex1 = 0;
			}
			HAL_SET_BUFFER_UART1(mu08TransmitData);
		}
	}
}

PUBLIC void DevSetUARTService(U08 u08Chanel, U08 u08ServiceSize, void (*pReceiveService)(void *))
{
	switch(u08Chanel)
	{
		case USART1:
			mfpReceiveUART1Service = pReceiveService;
			mu08ReceiveUART1ServiceSize = u08ServiceSize;
		break;
		case USART2:

		break;
		case USART3:

		break;
		case USART4:

		break;
		case USART5:

		break;
	}
}

PUBLIC void DevUART1ReceiveData(void)
{
	if(mu08ReceiveUART1Index < BUFFER_RECEIVE_SIZE1)
	{
		mau08BufferUART1ReceiveData[mu08ReceiveUART1Index] = HAL_GET_BUFFER_UART1();
		if(mu08ReceiveUART1Index < (BUFFER_RECEIVE_SIZE1-1))
		{
			mu08ReceiveUART1Index++;
		}
		else
		{
			mu08ReceiveUART1Index = 0;
		}
		if(mu08ReceiveUART1Index >= mu08ReceiveUART1ServiceSize)
		{
			if(mfpReceiveUART1Service != 0)
			{
				mfpReceiveUART1Service((void*)mau08BufferUART1ReceiveData);
			}
			mu08ReceiveUART1Index = 0;
		}
	}
}

PUBLIC void DevUART1TransmitData(void)
{
	U08 u08TransmitData = 0;
	if((mu16TransmitPopIndex1 != mu16TransmitPushIndex1)&&(mbfWritingTXBufferUART1 == FALSE))
	{
		mbfTransmittingUART1 = TRUE;
		if(HAL_IS_BUFFER_UART1_EMPTY() == TRUE)
		{
			u08TransmitData = mau08BufferUART1TransmitData[mu16TransmitPopIndex1];
			if(mu16TransmitPopIndex1 < BUFFER_TRANSMIT_SIZE1 -1)
			{
				mu16TransmitPopIndex1++;
			}
			else
			{
				mu16TransmitPopIndex1 = 0;
			}
			HAL_SET_BUFFER_UART1(u08TransmitData);
		}
		else
		{
			mbfTransmittingUART1 = FALSE;
		}
	}
	else
	{
		mbfTransmittingUART1 = FALSE;
	}
}

PUBLIC void DevSetUART1TransmitData(U08* pu08Data, U16 u16DataSize)
{
	U16 u16Index = 0;

	mbfTransmittingUART1 = FALSE;
	mbfWritingTXBufferUART1 = TRUE;
	for(u16Index = 0; u16Index < u16DataSize; u16Index++)
	{
		mau08BufferUART1TransmitData[mu16TransmitPushIndex1] = pu08Data[u16Index];
		if(mu16TransmitPushIndex1 < (BUFFER_TRANSMIT_SIZE1 - 1))
		{
			mu16TransmitPushIndex1++;
		}
		else
		{
			mu16TransmitPushIndex1 = 0;
		}
	}
	mbfWritingTXBufferUART1 = FALSE;
}
