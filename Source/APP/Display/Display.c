/*
 * Display.c
 *
 *  Created on: Oct 28, 2023
 *      Author: DINH KHANH
 */

#include "Display.h"

PRIVATE U08 mu08DataDisplayBK;
PRIVATE U08 mu08DataDisplayBK1;

PUBLIC void DisplayInit(void)
{
	mu08DataDisplayBK = 0;
	mu08DataDisplayBK1 =0;
}
PUBLIC void DisplayManager(void)
{
	char ms08TextDisplay = ' ';
	if(gsuRecieveDataPacket.u08DataSound != mu08DataDisplayBK1)
	{
		DevLCDSetCursor(gsuRecieveDataPacket.u08Row,gsuRecieveDataPacket.u08Colum);
		//DevLCDSetCursor(0,0);
		DevLCDPrintString("Giay: ");
		DevLCDSetCursor(0,5);
		DevLCDPrintString("  ");
		DevLCDSetCursor(0,5);
		sprintf(&ms08TextDisplay,"%0d",gsuRecieveDataPacket.u08DataSound);
		DevLCDPrintString(&ms08TextDisplay);
		mu08DataDisplayBK1 = gsuRecieveDataPacket.u08DataSound;
	}

	if(gsuRecieveDataPacket.u08DataDisplay != mu08DataDisplayBK)
	{
		DevLCDSetCursor(gsuRecieveDataPacket.u08Row,gsuRecieveDataPacket.u08Colum);
		//DevLCDSetCursor(1,0);
		DevLCDPrintString("Phut: ");
		DevLCDSetCursor(1,6);
		DevLCDPrintString("  ");
		DevLCDSetCursor(1,6);
		sprintf(&ms08TextDisplay,"%0d",gsuRecieveDataPacket.u08DataDisplay);
		DevLCDPrintString(&ms08TextDisplay);
		mu08DataDisplayBK = gsuRecieveDataPacket.u08DataDisplay;
	}
}


