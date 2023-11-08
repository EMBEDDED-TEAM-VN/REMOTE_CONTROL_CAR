#include "MidLoraCom.h"

#define BUFFER_LORA_RECEIVE_SIZE      400
#define BUFFER_LORA_PROCESS_SIZE      10
#define RECEIVE_SERVICE_SIZE		  1
#define SIZE_DATA_PACKET  10
#define SIZE_DATA_DISPLAY  1
#define SIZE_DATA_SOUND  1

PRIVATE U08 mau08DataTransmit[SIZE_DATA_PACKET];
PRIVATE U08 mau08DataDisplay[SIZE_DATA_DISPLAY];
PRIVATE U08 mau08DataSound[SIZE_DATA_SOUND];

PRIVATE U08 mau08BufferLoraReceive[BUFFER_LORA_RECEIVE_SIZE];
PRIVATE U08 mau08BufferLoraProcessing[BUFFER_LORA_PROCESS_SIZE];
PRIVATE U08 mau08BufferLoraDataPacket[BUFFER_LORA_PROCESS_SIZE];
PRIVATE U08 mu08ReceivePushIndex;
PRIVATE U08 mu08ReceivePopIndex;
PRIVATE U08 mu08ReceiveDataPacketLoraIndex;
PRIVATE U08 mau08TransmitLoraData[BUFFER_LORA_PROCESS_SIZE];
PUBLIC void (*TransmitDataLora)(U08* , U16 );

PRIVATE void ReceiveServiceLoraUART(void* pReceiveBuffer);
PRIVATE void ReceiveLoraDataPacket(void);
PRIVATE BOOL AnalystLoraDataPacket(void);
PRIVATE void TransmitDataToRemote(void);


PUBLIC void MidLoraInit(void)
{
	mu08ReceivePushIndex 	= 0;
	mu08ReceivePopIndex 	= 0;
	mu08ReceiveDataPacketLoraIndex = 0;
	memset(mau08BufferLoraReceive, 0, BUFFER_LORA_RECEIVE_SIZE);
	memset(mau08BufferLoraProcessing, 0, BUFFER_LORA_PROCESS_SIZE);
	memset(mau08BufferLoraDataPacket, 0, BUFFER_LORA_PROCESS_SIZE);
	memset(mau08TransmitLoraData, 0, BUFFER_LORA_PROCESS_SIZE);
	memset(mau08DataTransmit,0,SIZE_DATA_PACKET);
	memset(mau08DataDisplay,0,SIZE_DATA_DISPLAY);
	memset(mau08DataSound,0,SIZE_DATA_SOUND);
	LORA_COMM(RECEIVE_SERVICE_SIZE,ReceiveServiceLoraUART);
}

PUBLIC void SetDisplayText(U08 u08Data)
{
	U08 u08Index =0;
	mau08DataDisplay[u08Index] = u08Data;
}

PUBLIC void SetSound(U08 u08Data)
{
	U08 u08Index =0;
	mau08DataSound[u08Index] = u08Data;
}

PUBLIC void MidLoraCommLoop(void)
{
	BOOL bResultDataPacket = FALSE;

	ReceiveLoraDataPacket();
	bResultDataPacket = AnalystLoraDataPacket();
	if(bResultDataPacket == TRUE)
	{
		//Get data from data packet
	}
	else
	{
		memset(mau08BufferLoraDataPacket, 0, BUFFER_LORA_PROCESS_SIZE);
	}

	TransmitDataToRemote();
}
PRIVATE void ReceiveServiceLoraUART(void* pReceiveBuffer)
{
	U08* pDataBuffer = (U08*) pReceiveBuffer;

	mau08BufferLoraReceive[mu08ReceivePushIndex] = pDataBuffer[0];
	mu08ReceivePushIndex++;
	if(mu08ReceivePushIndex >= BUFFER_LORA_RECEIVE_SIZE)
	{
		mu08ReceivePushIndex = 0;
	}
}

PRIVATE void ReceiveLoraDataPacket(void)
{
	if(mu08ReceivePopIndex != mu08ReceivePushIndex)
	{
		mau08BufferLoraProcessing[mu08ReceiveDataPacketLoraIndex] = mau08BufferLoraReceive[mu08ReceivePopIndex];
		mu08ReceivePopIndex++;
		mu08ReceiveDataPacketLoraIndex++;
		if(mu08ReceivePopIndex >= BUFFER_LORA_RECEIVE_SIZE)
		{
			mu08ReceivePopIndex = 0;
		}
		if(mu08ReceiveDataPacketLoraIndex >= BUFFER_LORA_PROCESS_SIZE)
		{
			memcpy(mau08BufferLoraDataPacket,mau08BufferLoraProcessing,BUFFER_LORA_PROCESS_SIZE);
			mu08ReceiveDataPacketLoraIndex = 0;
		}
	}
}


PRIVATE BOOL AnalystLoraDataPacket(void)
{
	U08 u08Index = 0;
	BOOL bReturn = FALSE;
	U16 u16CheckSum = 0;
	if(mau08BufferLoraDataPacket[u08Index] == 0X5A)// Check Header
	{
		bReturn = TRUE;
	}
	else
	{
		return FALSE;
	}

	u16CheckSum = CaculateCheckSum(mau08BufferLoraDataPacket,(BUFFER_LORA_PROCESS_SIZE-1));

	if(u16CheckSum == mau08BufferLoraDataPacket[BUFFER_LORA_PROCESS_SIZE - 1])//Check Checksum
	{
		bReturn = TRUE;
	}
	else
	{
		return FALSE;
	}
	return bReturn;
}

PRIVATE void TransmitDataToRemote(void)
{
	U08 u08Index = 0;
	U08 u08SizeData = 0;
	U16 u16CheckSum = 0;
	u08SizeData = SIZE_DATA_DISPLAY + SIZE_DATA_SOUND;
	mau08DataTransmit[u08Index] = 0X5A;
	u08Index++;
	mau08DataTransmit[u08Index] = u08SizeData;
	u08Index++;
	memcpy((mau08DataTransmit + u08Index),mau08DataDisplay,SIZE_DATA_DISPLAY);
	u08Index += SIZE_DATA_DISPLAY;
	memcpy((mau08DataTransmit + u08Index),mau08DataSound,SIZE_DATA_SOUND);
	u16CheckSum = CaculateCheckSum(mau08DataTransmit,(SIZE_DATA_PACKET-1));
	mau08DataTransmit[SIZE_DATA_PACKET-1] = u16CheckSum;
	DevSetUART1TransmitData(mau08DataTransmit,SIZE_DATA_PACKET);
}
