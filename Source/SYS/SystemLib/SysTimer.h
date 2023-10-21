/*
 * SysTimer.h
 *
 *  Created on: Oct 19, 2023
 *      Author: DINH KHANH
 */

#ifndef SYS_SYSTEMLIB_SYSTIMER_H_
#define SYS_SYSTEMLIB_SYSTIMER_H_

#include "Keyword.h"
#include "Macro.h"
#include "stm32f10x.h"

typedef struct ST_TimeBit{
	U08      bf1Sec          :1;
	U08      bf500mSec       :1;
	U08      bf100mSec       :1;
	U08      bf50mSec        :1;
	U08      bf10mSec        :1;
} TTimeFlag;

extern TTimeFlag   gsuMainTimerFlag;

#define gbfSys10mSecFlag            gsuMainTimerFlag.bf10mSec
#define gbfSys50mSecFlag            gsuMainTimerFlag.bf50mSec
#define gbfSys100mSecFlag           gsuMainTimerFlag.bf100mSec
#define gbfSys500mSecFlag           gsuMainTimerFlag.bf500mSec
#define gbfSys1SecFlag            	gsuMainTimerFlag.bf1Sec

PUBLIC void SysInitTimer(void);
PUBLIC void SysMainLoopTimer(void);
PUBLIC void SysIsrTickTimer(void);

#endif /* SYS_SYSTEMLIB_SYSTIMER_H_ */
