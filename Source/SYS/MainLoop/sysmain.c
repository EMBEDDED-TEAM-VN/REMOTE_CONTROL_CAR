#include "stm32f10x.h"
#include "Portmap.h"
#include "DevUART.h"
#include "MidLoraCom.h"

int main(void)
{
	DevUARTInit();
	MidLoraInit();
	while(TRUE)
	{
		MidLoraCommLoop();
	}
}
