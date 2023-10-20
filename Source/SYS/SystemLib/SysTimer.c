/*
 * SysTimer.c
 *
 *  Created on: Oct 19, 2023
 *      Author: DINH KHANH
 */

#include "SysTimer.h"

PRIVATE U16 mu16Main1mSecCnt;
PRIVATE U16 mu16Main10mSecCnt;
PRIVATE U16 mu16Main50mSecCnt;
PRIVATE U16 mu16Main1SecCnt;


PUBLIC void SysInitTimer(void)
{
	mu16Main1mSecCnt = 0;
	mu16Main10mSecCnt = 0;
	mu16Main50mSecCnt = 0;
	mu16Main1SecCnt = 0;
	if(SysTick_Config(SystemCoreClock/1000))
	{
		while(1);
	}
}
PUBLIC void SysMainLoopTimer(void)
{
	*(U08*)&gsuMainTimerFlag = 0;
	if(mu16Main1mSecCnt)
	{
		mu16Main1mSecCnt = 0;
		mu16Main10mSecCnt++;
		if(mu16Main10mSecCnt >= 10)
		{
			gsuMainTimerFlag.bf10mSec = SET;
			mu16Main10mSecCnt = 0;
			mu16Main50mSecCnt++;
			if(mu16Main50mSecCnt >= 5)
			{
				mu16Main50mSecCnt = 0;
				gsuMainTimerFlag.bf50mSec = SET;
				mu16Main1SecCnt++;
				if(mu16Main1SecCnt & 0x01)
				{
					gsuMainTimerFlag.bf100mSec = SET;
					if(mu16Main1SecCnt == 10 || mu16Main1SecCnt >= 20)
					{
						gsuMainTimerFlag.bf500mSec = SET;
						if(mu16Main1SecCnt >= 20)
						{
							gsuMainTimerFlag.bf1Sec = SET;
							mu16Main1SecCnt = 0;
						}
					}
				}
			}
		}
	}
}

PUBLIC void SysIsrTickTimer(void)
{
	mu16Main1mSecCnt++;
	//Implement function after 1ms
}



