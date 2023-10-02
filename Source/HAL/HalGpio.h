#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define PORT_OUT        						GPIO_Mode_Out_PP
#define PORT_IN         						GPIO_Mode_IN_FLOATING
#define mRCC_APB2_PERIPHCLOCK(PNum,EnDis)   		RCC_APB2PeriphClockCmd(RCC_APB2Periph_##PNum,EnDis)

void HalPortSetType(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Type);
