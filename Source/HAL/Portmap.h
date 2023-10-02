#include "HalGpio.h"

#define mPORT_SET_TYPE(PNum,BNum,PType)			HalPortSetType(GPIO##PNum, GPIO_Pin_##BNum, PType)
#define mPORT_SET_DATA(PNum,BNum,LowHi)			(LowHi == HI) ? (GPIO_SetBits(GPIO##PNum, GPIO_Pin_##BNum)) : (GPIO_ResetBits(GPIO##PNum, GPIO_Pin_##BNum))
#define mPORT_GET_DATA(PNum,BNum)				GPIO_ReadInputDataBit(GPIO##PNum, GPIO_Pin_##BNum)
#define PORT_SET_TYPE(PortMap,Ptype)			mPORT_SET_TYPE(PortMap,Ptype)
#define PORT_SET_DATA(PortMap,LowHi)			mPORT_SET_DATA(PortMap,LowHi)
#define PORT_GET_DATA(PortMap)					mPORT_GET_DATA(PortMap)
