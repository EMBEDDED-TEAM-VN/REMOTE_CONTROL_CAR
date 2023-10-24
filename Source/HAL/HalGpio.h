#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Macro.h"

#define PORT_OUT        						GPIO_Mode_Out_PP
#define PORT_IN         						GPIO_Mode_IN_FLOATING
#define PORT_ALTF         						GPIO_Mode_AF_PP

void HalPortSetType(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Type);
