/*
 * Interrupt_Button.c
 *
 *  Created on: Oct 9, 2023
 *      Author: DINH HIEN
 */

/**
 * Function Name: void Handling_Interrupt_Button(U08 GPIX_Interrupt_Button, U08 GPIO_Pin_X, GPIOMode_TypeDef GPIO_Mode_Input, \
                                U08 GPIO_PinSourceX, U08 EXTI_LineX, EXTITrigger_TypeDef EXTI_Trigger_X, U08 EXTIX_IRQn)
 *
 * Author : DINH HIEN(bachhien500@gmail.com)
 *
 * Description: Using configure type of GPIO (Output type or Input type), Enable clock of APB2 bus, External Interrupt.
 *
 * @param parameter1 GPIX_Interrupt_Button: Name of port has button is input	(EX: GPIOA_Interrupt_Button,...)
 * @param parameter2 GPIO_Pin_X: Pin number 	(EX: GPIO_Pin_0,....)
 * @param parameter3 GPIO_Mode_Input: Input Mode 	(EX: GPIO_Mode_IPU,...)
 * @param parameter4 GPIO_PinSourceX: Pin X to interrupt 	(EX: GPIO_PinSource0,...)
 * @param parameter5 EXTI_LineX: Line X for interrupt 	(EX: EXTI_Line0,...)
 * @param parameter6 EXTI_Trigger_X: Trigger Mode for interrupt 	(EX: EXTI_Trigger_Rising,...)
 * @param parameter7 EXTIX_IRQn: EXTI LineX Interrupt 	(EX: EXTI0_IRQn,...)
 * @return : No return
 */

#include "HAL_Interrupt_Button.h"

// Initialization count
U08 counter = 0;

// Function handle interrupt button's EXTI0
void EXTI0_IRQHandler(void) {
  if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
      // Handle interrupts from channel EXTI0 here
      counter++;

      // Clear flag interrupt EXTI0
      EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void Initialize_Button(U08 GPIX_Interrupt_Button, U08 GPIO_Pin_X, GPIOMode_TypeDef GPIO_Mode_Input)
{
  RCC_APB2PeriphClockCmd(GPIX_Interrupt_Button | RCC_APB2Periph_AFIO, ENABLE);  // Turn on clock for GPIO and AFIO

  if(GPIX_Interrupt_Button == GPIOA_Interrupt_Button)
  {
      // Configure the GPIO pin, configure the pin as input and set the button state when not pressed (Pull-down or Pull-up).
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_X; // Pin GPIO X
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;  // Input Pull-Down Mode
      GPIO_Init(GPIOA, &GPIO_InitStructure);
  } 
  else if(GPIX_Interrupt_Button == GPIOB_Interrupt_Button)
  {
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_X; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;  
      GPIO_Init(GPIOB, &GPIO_InitStructure);
  }
  else if(GPIX_Interrupt_Button == GPIOC_Interrupt_Button)
  {
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_X; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;  
      GPIO_Init(GPIOC, &GPIO_InitStructure);
  }
  else if(GPIX_Interrupt_Button == GPIOD_Interrupt_Button)
  {
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_X; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;  
      GPIO_Init(GPIOD, &GPIO_InitStructure);
  }
  else if(GPIX_Interrupt_Button == GPIOE_Interrupt_Button)
  {
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_X; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input; 
      GPIO_Init(GPIOE, &GPIO_InitStructure);
  }
  else if(GPIX_Interrupt_Button == GPIOG_Interrupt_Button)
  {
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_X; 
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;  
      GPIO_Init(GPIOG, &GPIO_InitStructure);
  }
  else{
      // Nothing
  }
}

void Handling_Interrupt_Button(U08 GPIX_Interrupt_Button, U08 GPIO_Pin_X, GPIOMode_TypeDef GPIO_Mode_Input, \
                                U08 GPIO_PinSourceX, U08 EXTI_LineX, EXTITrigger_TypeDef EXTI_Trigger_X, U08 EXTIX_IRQn){

  // Initialization button
  Initialize_Button(GPIX_Interrupt_Button, GPIO_Pin_X, GPIO_Mode_Input);


  // configure GPIOX Pin x as a peripheral signal source for a peripheral interrupt channel
  GPIO_EXTILineConfig(GPIX_Interrupt_Button, GPIO_PinSourceX);
  
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_LineX; // kênh ngắt x tương ứng với Portx, pin x
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_X;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
  EXTI_Init(&EXTI_InitStructure);
  
  // Cofigure NVIC (Nested Vectored Interrupt Controller) to enable interrupt handling from the corresponding EXTIX line
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTIX_IRQn;  // EXTIX is the channel corresponding with GPIOX Pin X
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // Highest priority
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  // Priority to the lowest child interrupt
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
int main(void) {
  // example to call the function interrupt for button
  Handling_Interrupt_Button(GPIOA_Interrupt_Button, GPIO_Pin_0, GPIO_Mode_IPU, GPIO_PinSource0, EXTI_Line0, EXTI_Trigger_Rising, EXTI0_IRQn);
}*/

