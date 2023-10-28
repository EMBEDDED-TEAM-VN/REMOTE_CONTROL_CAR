/*
 * Display.c
 *
 *  Created on: Oct 28, 2023
 *      Author: DINH KHANH
 */

#include "Display.h"

#define SIZE_DATA_PACKET  10
#define SIZE_DATA_DISPLAY  1
#define SIZE_DATA_SOUND  1

PRIVATE U08 mau08DataTransmit[SIZE_DATA_PACKET];
PRIVATE U08 mau08DataDisplay[SIZE_DATA_DISPLAY];
PRIVATE U08 mau08DataSound[SIZE_DATA_SOUND];
PRIVATE void TransmitDataToRemote(void);

PUBLIC void DisplayInit(void)
{
	memset(mau08DataTransmit,0,SIZE_DATA_PACKET);
	memset(mau08DataDisplay,0,SIZE_DATA_DISPLAY);
	memset(mau08DataSound,0,SIZE_DATA_SOUND);
}
PUBLIC void DisplayManager(void)
{
	TransmitDataToRemote();
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
PUBLIC void TransmitDataToRemote(void)
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
	TransmitDataLora(mau08DataTransmit,SIZE_DATA_PACKET);
}


