/*
 * Hal.h
 *
 *  Created on: Oct 19, 2023
 *      Author: DINH KHANH
 */

#ifndef HAL_HAL_H_
#define HAL_HAL_H_

#include "stm32f10x_adc.h"
#include "stm32f10x_exti.h"
#include "HalGpio.h"

#define HAL_ADC_INIT()		do																		\
							{																		\
								RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);				\
								ADC_InitTypeDef ADC_InitStructure;									\
								ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					\
								ADC_InitStructure.ADC_ScanConvMode = DISABLE;						\
								ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					\
								ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; \
								ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				\
								ADC_InitStructure.ADC_NbrOfChannel = 1;								\
								ADC_Init(ADC1, &ADC_InitStructure);									\
								ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5); \
								ADC_Cmd(ADC1, ENABLE); 												\
							}while(0);

#define HAL_EXTERNAL_INTERRUPT()    do																		\
									{																		\
										GPIO_InitTypeDef GPIO_InitStruct;									\
										GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7; 								\
										GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;							\
										 GPIO_Init(GPIOA, &GPIO_InitStruct); 								\
										EXTI_InitTypeDef EXTI_InitStruct;									\
										NVIC_InitTypeDef NVIC_InitStruct;									\
										EXTI_InitStruct.EXTI_Line = EXTI_Line0; 							\
										EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;  					\
										EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;  				\
										EXTI_InitStruct.EXTI_LineCmd = ENABLE;								\
										EXTI_Init(&EXTI_InitStruct);										\
										NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;						\
										NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;				\
										NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;						\
										NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;						\
										NVIC_Init(&NVIC_InitStruct);										\
									}while(0);

#endif /* HAL_HAL_H_ */
