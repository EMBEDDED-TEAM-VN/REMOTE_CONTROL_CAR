#include "Sysmain.h"
#define SOUND_ID 0X34
#define DISPLAY_ID 0X35
int main(void)
{
	SysInitTimer();
	DevUARTInit();
	MidLoraInit();
	ApplicationInit();
	while(TRUE)
	{
		SysMainLoopTimer();
		//DevMainLoodUART();
		ApplicationManager();
		MidLoraCommLoop();
	}
}
