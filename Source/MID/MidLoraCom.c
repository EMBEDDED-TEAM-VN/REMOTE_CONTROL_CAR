#include "MidLoraCom.h"

#define BUFFER_LORA_RECEIVE_SIZE      400
#define BUFFER_LORA_PROCESS_SIZE      8
#define RECEIVE_SERVICE_SIZE		  1
#define SIZE_DATA_PACKET  8
#define SIZE_DATA_DISPLAY  1
#define SIZE_DATA_SOUND  1
#define TIME_OUT_RECEIVE_DATA  20

DATAPACKET gsuRecieveDataPacket;
PRIVATE DATAPACKET TransmitDataPacket;
PRIVATE U08 mau08DataTransmit[SIZE_DATA_PACKET];

PRIVATE U08 mau08BufferLoraReceive[BUFFER_LORA_RECEIVE_SIZE];
PRIVATE U08 mau08BufferLoraProcessing[BUFFER_LORA_PROCESS_SIZE];
PRIVATE U08 mau08BufferLoraDataPacket[BUFFER_LORA_PROCESS_SIZE];
PRIVATE U08 mu08ReceivePushIndex;
PRIVATE U08 mu08ReceivePopIndex;
PRIVATE U08 mu08ReceiveDataPacketLoraIndex;
PRIVATE BOOL bmSendData;
PRIVATE U08 mau08TransmitLoraData[BUFFER_LORA_PROCESS_SIZE];
PUBLIC void (*TransmitDataLora)(U08* , U16 );

PRIVATE void ReceiveServiceLoraUART(void* pReceiveBuffer);
PRIVATE void ReceiveLoraDataPacket(void);
PRIVATE BOOL AnalystLoraDataPacket(void);
PRIVATE void TransmitDataToRemote(void);


PUBLIC void MidLoraInit(void)
{
	bmSendData = FALSE;
	mu08ReceivePushIndex 	= 0;
	mu08ReceivePopIndex 	= 0;
	mu08ReceiveDataPacketLoraIndex = 0;
	memset(mau08BufferLoraReceive, 0, BUFFER_LORA_RECEIVE_SIZE);
	memset(mau08BufferLoraProcessing, 0, BUFFER_LORA_PROCESS_SIZE);
	memset(mau08BufferLoraDataPacket, 0, BUFFER_LORA_PROCESS_SIZE);
	memset(mau08TransmitLoraData, 0, BUFFER_LORA_PROCESS_SIZE);
	memset(mau08DataTransmit,0,SIZE_DATA_PACKET);
	memset(&gsuRecieveDataPacket, 0, sizeof(DATAPACKET));
	memset(&TransmitDataPacket, 0, sizeof(DATAPACKET));
	LORA_COMM(RECEIVE_SERVICE_SIZE,ReceiveServiceLoraUART);
}

PUBLIC void SetDisplayText(U08 u08Data)
{
	TransmitDataPacket.u08DataDisplay = u08Data;
	bmSendData = TRUE;
}

PUBLIC void SetSound(U08 u08Data)
{
	TransmitDataPacket.u08DataSound = u08Data;
	bmSendData = TRUE;
}

PUBLIC void SetCursor(U08 u08Row,U08 u08Colum)
{
	TransmitDataPacket.u08Row = u08Row;
	TransmitDataPacket.u08Colum = u08Colum;
	bmSendData = TRUE;
}


PUBLIC void MidLoraCommLoop(void)
{
	BOOL bResultDataPacket = FALSE;

	ReceiveLoraDataPacket();
	bResultDataPacket = AnalystLoraDataPacket();
	if(bResultDataPacket == TRUE)
	{
		//Get data from data packet
		memcpy(&gsuRecieveDataPacket,(mau08BufferLoraDataPacket + 2),sizeof(DATAPACKET));
	}
	else
	{
		memset(mau08BufferLoraDataPacket, 0, BUFFER_LORA_PROCESS_SIZE);
	}
	if(gbfSys100mSecFlag == TRUE)
	{
		if(bmSendData == TRUE)
		{
			TransmitDataToRemote();
			bmSendData = FALSE;
		}
	}
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
	U16 u16CheckSum1 = 0;
	U16 u16CheckSum2 = 0;

	if(mau08BufferLoraDataPacket[u08Index] == 0X5A)// Check Header
	{
		bReturn = TRUE;
	}
	else
	{
		return FALSE;
	}
	u08Index++;

	if(mau08BufferLoraDataPacket[u08Index] == sizeof(DATAPACKET))
	{
		bReturn = TRUE;
	}
	else
	{
		return FALSE;
	}

	u16CheckSum = CaculateCheckSum(mau08BufferLoraDataPacket,(BUFFER_LORA_PROCESS_SIZE-2));
	u16CheckSum1 = (u16CheckSum&0x00ff);
	u16CheckSum2 = (u16CheckSum >> 8);
	if((u16CheckSum1 == mau08BufferLoraDataPacket[BUFFER_LORA_PROCESS_SIZE - 2])
	&&(u16CheckSum2 == mau08BufferLoraDataPacket[BUFFER_LORA_PROCESS_SIZE - 1]))//Check Checksum
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
	u08SizeData = sizeof(DATAPACKET);
	mau08DataTransmit[u08Index] = 0X5A;
	u08Index++;
	mau08DataTransmit[u08Index] = u08SizeData;
	u08Index++;
	memcpy((mau08DataTransmit + u08Index),&TransmitDataPacket,sizeof(DATAPACKET));
	u16CheckSum = CaculateCheckSum(mau08DataTransmit,(SIZE_DATA_PACKET-2));
	mau08DataTransmit[SIZE_DATA_PACKET-2] = (u16CheckSum&0x00ff);
	mau08DataTransmit[SIZE_DATA_PACKET-1] = (u16CheckSum >> 8);
	DevSetUART1TransmitData(mau08DataTransmit,SIZE_DATA_PACKET);
}
