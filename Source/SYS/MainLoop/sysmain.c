#include "stm32f10x.h"
#include "Portmap.h"
#include "Keyword.h"

U08 TIM1_IRQn;
void TIM1_Configuration(U08 TIM1_Channel);
void Delay_Timer1_StandardLibrary_Ms(U32 milliseconds);

void main()
{
    TIM1_Configuration(TIM1_IRQn);
		TIM1_IRQn = 1;
    while(1)
		{
			    Delay_Timer1_StandardLibrary_Ms(1000);
					PORT_SET_TYPE(PMAP_ONC_PC13,PORT_OUT);
					PORT_SET_DATA(PMAP_ONC_PC13,1);
					Delay_Timer1_StandardLibrary_Ms(1000);
					//PORT_SET_TYPE(C,13,PORT_OUT);
					PORT_SET_DATA(PMAP_ONC_PC13,0);
		}
}
