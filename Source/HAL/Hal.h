/*
 * Hal.h
 *
 *  Created on: Oct 19, 2023
 *      Author: DINH KHANH
 */

#ifndef HAL_HAL_H_
#define HAL_HAL_H_

#include "stm32f10x_adc.h"

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
							}while(0);\



#endif /* HAL_HAL_H_ */
