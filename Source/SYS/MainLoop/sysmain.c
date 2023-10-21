#include "Sysmain.h"

int main(void)
{
	SysInitTimer();
	DevUARTInit();
	MidLoraInit();
	ApplicationInit();
	while(TRUE)
	{
		SysMainLoopTimer();
		MidLoraCommLoop();
		TimerManager();
	}
}
