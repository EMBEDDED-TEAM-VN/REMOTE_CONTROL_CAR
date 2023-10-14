#include "stm32f10x.h"
#include "stdio.h"
#include "core_cm3.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stdint.h"
#include "Keyword.h"


#define GPIOA_Interrupt_Button       ((uint8_t)0x00)
#define GPIOB_Interrupt_Button       ((uint8_t)0x01)
#define GPIOC_Interrupt_Button       ((uint8_t)0x02)
#define GPIOD_Interrupt_Button       ((uint8_t)0x03)
#define GPIOE_Interrupt_Button       ((uint8_t)0x04)
#define GPIOF_Interrupt_Button       ((uint8_t)0x05)
#define GPIOG_Interrupt_Button       ((uint8_t)0x06)

// Function interrupt for button 
void EXTI0_IRQHandler(void);

// Initialize for Button
void Initialize_Button(U08 GPIX_Interrupt_Button, U08 GPIO_Pin_X, GPIOMode_TypeDef GPIO_Mode_Input);

// Handling Interrupt by button
void Handling_Interrupt_Button(U08 GPIX_Interrupt_Button, U08 GPIO_Pin_X, GPIOMode_TypeDef GPIO_Mode_Input, \
                                U08 GPIO_PinSourceX, U08 EXTI_LineX, EXTITrigger_TypeDef EXTI_Trigger_X, U08 EXTIX_IRQn);

