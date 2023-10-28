/*
 * Portmap.h
 *
 *  Created on: Oct 28, 2023
 *      Author: DINH KHANH
 */

#ifndef HAL_PORTMAP_H_
#define HAL_PORTMAP_H_

#include "HalGpio.h"

#define mPORT_SET_TYPE(PNum,BNum,PType)			HalPortSetType(GPIO##PNum, GPIO_Pin_##BNum, PType)
#define mPORT_SET_DATA(PNum,BNum,LowHi)			(LowHi == HIGH) ? (GPIO_SetBits(GPIO##PNum, GPIO_Pin_##BNum)) : (GPIO_ResetBits(GPIO##PNum, GPIO_Pin_##BNum))
#define mPORT_GET_DATA(PNum,BNum)				GPIO_ReadInputDataBit(GPIO##PNum, GPIO_Pin_##BNum)
#define PORT_SET_TYPE(PortMap,Ptype)			mPORT_SET_TYPE(PortMap,Ptype)
#define PORT_SET_DATA(PortMap,LowHi)			mPORT_SET_DATA(PortMap,LowHi)
#define PORT_GET_DATA(PortMap)					mPORT_GET_DATA(PortMap)

/*Define GPIO*/

/*GPIOA*/
#define PMAP_ONC_PA00     A,0  //WKUP
#define PMAP_ONC_PA01     A,1
#define PMAP_ONC_PA02     A,2
#define PMAP_ONC_PA03     A,3
#define PMAP_ONC_PA04     A,4
#define PMAP_ONC_PA05     A,5
#define PMAP_ONC_PA06     A,6
#define PMAP_ONC_PA07     A,7
#define PMAP_ONC_PA08     A,8
#define PMAP_ONC_PA09     A,9
#define PMAP_ONC_PA10     A,10
#define PMAP_ONC_PA11     A,11
#define PMAP_ONC_PA12     A,12
#define PMAP_ONC_PA13     A,13 //SWIO
#define PMAP_ONC_PA14     A,14 //SWCLK
#define PMAP_ONC_PA15     A,15


/*GPIOB*/
#define PMAP_ONC_PB00     B,0
#define PMAP_ONC_PB01     B,1
#define PMAP_ONC_PB02     B,2  //BOOT1
#define PMAP_ONC_PB03     B,3
#define PMAP_ONC_PB04     B,4
#define PMAP_ONC_PB05     B,5
#define PMAP_ONC_PB06     B,6
#define PMAP_ONC_PB07     B,7
#define PMAP_ONC_PB08     B,8
#define PMAP_ONC_PB09     B,9
#define PMAP_ONC_PB10     B,10
#define PMAP_ONC_PB11     B,11
#define PMAP_ONC_PB12     B,12
#define PMAP_ONC_PB13     B,13
#define PMAP_ONC_PB14     B,14
#define PMAP_ONC_PB15     B,15

/*GPIOC*/
#define PMAP_ONC_PC13     C,13 //TAMPER-RT C
#define PMAP_ONC_PC14     C,14 //OSC32_IN - 32KhZ
#define PMAP_ONC_PC15     C,15 //OSC32_OUT- 32KHZ

/*GPIOd*/
#define PMAP_ONC_PD00     D,0 //OSCIN - 8MHZ
#define PMAP_ONC_PD01     D,1 //OSCOUT -8MHZ




#endif /* HAL_PORTMAP_H_ */
