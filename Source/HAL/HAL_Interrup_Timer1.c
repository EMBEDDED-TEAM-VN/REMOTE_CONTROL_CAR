#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "Keyword.h"
#include "system_stm32f10x.h"
#include "misc.h"


void TIM1_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  }
}


/**
 * Function Name 2: void TIM1_Configuration(U08 TIM1_Channel)
 *
 * Description: Using configure for Timer1
 *
 * @param parameter1 TIM1_Channel: Channel for Timer1 (TIM1_IRQn)
 * @return : No return
 */
void TIM1_Configuration(U08 TIM1_Channel)
{
  // 1 tick 1/100000

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 1000 - 1; // System clock is 72Mhz, fCK_PSC / (PSC[15:0] + 1) = 1000
  TIM_TimeBaseStructure.TIM_Period = 65535;  // 0xffff
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // Count up
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      // Division for 1
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;             // Repetition from 0
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);              // Init for Timer1

  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);                   // TIM_IT_Update allows to automatically trigger an interrupt when an Update event occurs 

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_Channel;           // Choose channel for timer1 TIM1_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    // Priority for interrupt
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM1, ENABLE);
}

/*
 * Interrupt_Button.c
 *
 *  Created on: Sep 21, 2023
 *      Author: DINH HIEN
 */

/**
 * Function Name 1: void Delay_Timer1_StandardLibrary_Ms(U32 milliseconds)
 *
 * Author : DINH HIEN(bachhien500@gmail.com)
 *
 * Description: Using configure type of TIMER1 to have the event for interruption
 *
 * @param parameter1 milliseconds: value of the timing you want, and the unit is millisecond (ex: 1000, 2000,...)

 * @return : No return
 */
void Delay_Timer1_StandardLibrary_Ms(U32 milliseconds)
{
  TIM_SetCounter(TIM1, 0); // set the first value for timer1 is 0 -> 
  TIM_Cmd(TIM1, ENABLE);   // Enable Timer1

  while (TIM_GetFlagStatus(TIM1, TIM_FLAG_Update) == RESET)  // The event occurs TIM_FLAG_Update will be SET
  {
    if (TIM_GetCounter(TIM1) >= milliseconds)
    {
      break;
    }
  }

  TIM_ClearFlag(TIM1, TIM_FLAG_Update);    // Clear flag update and disable Timer1
  TIM_Cmd(TIM1, DISABLE);
}
/* Example in here
int main(void)
{
  TIM1_Configuration(TIM1_IRQn);

  while (1)
  {
    // Gọi hàm delay_ms để tạo độ trễ 1000ms (1 giây)
    Delay_Timer1_StandardLibrary_Ms(1000);
    // Thực hiện các công việc khác ở đây
  }
}*/