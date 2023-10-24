/*
 * HalGpio.c
 *
 *  Created on: Oct 1, 2023
 *      Author: DINH KHANH
 */

#include "HalGpio.h"

/**
 * Function Name: void HalPortSetType(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Type)
 *
 * Author : DINH KHANH(pdkhanh190820@gmail.com)
 *
 * Description: Using configure type of GPIO (Output type or Input type), Enable clock of APB2 bus.
 *
 * @param parameter1 GPIOx: Name of port 	(EX:GPIOA,...)
 * @param parameter2 GPIO_Pin: Pin number 	(EX: GPIO_Pin_1,....)
 * @param parameter2 GPIO_Type: Type of pin 	(PORT_OUT/PORT_IN)
 * @return : No return
 */
void HalPortSetType(GPIO_TypeDef* pGPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Type)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	if(pGPIOx == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	}else if (pGPIOx == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	}else if (pGPIOx == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	}else if (pGPIOx == GPIOD)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	}else if (pGPIOx == GPIOE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	}else if (pGPIOx == GPIOF)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	}else if (pGPIOx == GPIOG)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	}
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Type;
	if(GPIO_Type == PORT_OUT || GPIO_Type == PORT_ALTF)
	{
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	}
	GPIO_Init(pGPIOx, &GPIO_InitStructure);
}
