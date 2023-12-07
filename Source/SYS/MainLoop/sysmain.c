#include "Sysmain.h"
#define SOUND_ID 0X34
#define DISPLAY_ID 0X35

PRIVATE U08 U08Test = 15;
PRIVATE U08 U08TestBk[1];
int main(void)
{
	SysInitTimer();
	DevUARTInit();
	MidLoraInit();
	ApplicationInit();
    DevLCDInit();

    // Hiển thị thông báo "Hello, LCD!" trên màn hình

	while(TRUE)
	{
		U08Test = GetMinute();
		SysMainLoopTimer();
		//DevMainLoodUART();
		ApplicationManager();
		MidLoraCommLoop();
//		if(gbfSys100mSecFlag == TRUE)
//		{
//			DevLCDClear();
//			DevLCDSetCursor(0, 1);
//			sprintf(U08TestBk,"%0d",U08Test);
//			DevLCDPrintString(U08TestBk);
//		}
	}
}
