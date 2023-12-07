#include "Application.h"

PRIVATE U08 mu08Second;
PRIVATE U08 mu08Minute;
PRIVATE U08 mu08Hours;
PRIVATE U08 mu08SecondCnt;

PUBLIC void ApplicationInit(void)
{
	mu08Second = 0;
	mu08Minute = 0;
	mu08Hours = 0;
	mu08SecondCnt = 0;
}
PUBLIC void ApplicationManager(void)
{
	char mau08Test[1] ={0};
	if(gbfSys100mSecFlag == TRUE)
	{
		mu08SecondCnt++;
		if(mu08SecondCnt >= TEST_TIMER)
		{
			mu08SecondCnt = 0;
			mu08Second++;
			//DevLCDClear();
			DevLCDSetCursor(0, 1);
			sprintf(mau08Test,"%0d",mu08Second);
			DevLCDPrintString(mau08Test);
			//SetDisplayText(mu08Second);
			SetSound(mu08Second);
			if(mu08Second >= 60)
			{
				mu08Minute++;
				SetDisplayText(mu08Minute);
				mu08Second = 0;
				if(mu08Minute >= 60)
				{
					mu08Minute = 0;
					mu08Hours++;
				}
			}
		}
	}
}

PUBLIC U08 GetMinute(void)
{
	return mu08Second;
}

PUBLIC void ResetMinute(void)
{
	mu08Minute = 0;
}
