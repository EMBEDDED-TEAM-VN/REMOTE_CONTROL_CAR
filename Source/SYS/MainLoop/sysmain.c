#include "stm32f10x.h"
#include "Portmap.h"
#include "DevUART.h"
#include "MidLoraCom.h"
#include "SysTimer.h"

int main(void)
{
	SysInitTimer();
	DevUARTInit();
	MidLoraInit();
	while(TRUE)
	{
		SysMainLoopTimer();
		MidLoraCommLoop();
	}
}
