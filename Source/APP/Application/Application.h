/*
 * Application.h
 *
 *  Created on: Oct 21, 2023
 *      Author: DINH KHANH
 */

#ifndef APP_APPLICATION_APPLICATION_H_
#define APP_APPLICATION_APPLICATION_H_

#include "SysTimer.h"

#define TEST_TIMER  10

PUBLIC void ApplicationInit(void);
PUBLIC void TimerManager(void);
PUBLIC U08 GetMinute(void);
PUBLIC void ResetMinute(void);
#endif /* APP_APPLICATION_APPLICATION_H_ */
