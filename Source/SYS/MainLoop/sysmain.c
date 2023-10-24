#include "Sysmain.h"

PRIVATE U08 mau08Test[400];
int main(void)
{
	memset(mau08Test, 0, 400);
	SysInitTimer();
	DevUARTInit();
	MidLoraInit();
	ApplicationInit();
	while(TRUE)
	{
		SysMainLoopTimer();
		MidLoraCommLoop();
		DevMainLoodUART();
		TimerManager();
		if(gbfSys100mSecFlag == TRUE)
		{
			DevSetUART1TransmitData(mau08Test,400);
		}
	}
}
