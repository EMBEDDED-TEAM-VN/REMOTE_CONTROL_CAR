#include "HalGpio.h"

#define mPORT_SET_TYPE(PNum,BNum,PType)			HalPortSetType(GPIO##PNum, GPIO_Pin_##BNum, PType)
#define mPORT_SET_DATA(PNum,BNum,LowHi)			(LowHi == HI) ? (GPIO_SetBits(GPIO##PNum, GPIO_Pin_##BNum)) : (GPIO_ResetBits(GPIO##PNum, GPIO_Pin_##BNum))
#define mPORT_GET_DATA(PNum,BNum)				GPIO_ReadInputDataBit(GPIO##PNum, GPIO_Pin_##BNum)
#define PORT_SET_TYPE(PortMap,Ptype)			mPORT_SET_TYPE(PortMap,Ptype)
#define PORT_SET_DATA(PortMap,LowHi)			mPORT_SET_DATA(PortMap,LowHi)
#define PORT_GET_DATA(PortMap)					mPORT_GET_DATA(PortMap)

/*Define GPIO*/

/*GPIOA*/
#define PMAP_ONC_PA00     A,0  //ADC1_IN0
#define PMAP_ONC_PA01     A,1  //ADC1_IN1
#define PMAP_ONC_PA02     A,2  //ADC1_IN2
#define PMAP_ONC_PA03     A,3  //ADC1_IN3
#define PMAP_ONC_PA04     A,4  //USART2_TX
#define PMAP_ONC_PA05     A,5  //USART2_rX
#define PMAP_ONC_PA06     A,6  //TIM3_CH1
#define PMAP_ONC_PA07     A,7  //TIM3_CH2
#define PMAP_ONC_PA08     A,8  //USART1_TX
#define PMAP_ONC_PA09     A,9  //USART1_RX
#define PMAP_ONC_PA10     A,10 //EVENTOUT
#define PMAP_ONC_PA11     A,11 //USB_OTG_FS_DM
#define PMAP_ONC_PA12     A,12 //USB_OTG_FS_DM
#define PMAP_ONC_PA13     A,13 //JTMS/SWDIO
#define PMAP_ONC_PA14     A,14 //JTCK/SWCLK
#define PMAP_ONC_PA15     A,15 //EVENTOUT


/*GPIOB*/
#define PMAP_ONC_PB00     B,0  //ADC1_IN4
#define PMAP_ONC_PB01     B,1  //ADC1_IN5
#define PMAP_ONC_PB02     B,2  //BOOT1
#define PMAP_ONC_PB03     B,3  //USART1_CTS
#define PMAP_ONC_PB04     B,4  //USART1_RTS
#define PMAP_ONC_PB05     B,5  //I2C1_SCL
#define PMAP_ONC_PB06     B,6  //I2C1_SDA
#define PMAP_ONC_PB07     B,7  //TIM4_CH1
#define PMAP_ONC_PB08     B,8  //TIM4_CH2
#define PMAP_ONC_PB09     B,9  //TIM4_CH3
#define PMAP_ONC_PB10     B,10 //TIM4_CH4
#define PMAP_ONC_PB11     B,11 //SPI1_SCK
#define PMAP_ONC_PB12     B,12 //SPI1_MISO
#define PMAP_ONC_PB13     B,13 //SPI1_MOSI
#define PMAP_ONC_PB14     B,14 //TIM1_CH2
#define PMAP_ONC_PB15     B,15 //TIM1_CH3

/*GPIOC*/
#define PMAP_ONC_PC00     C,0  //USART6_TX
#define PMAP_ONC_PC01     C,1  //USART6_RX
#define PMAP_ONC_PC02     C,2  //TIM3_CH1
#define PMAP_ONC_PC03     C,3  //TIM3_CH2
#define PMAP_ONC_PC04     C,4  //TIM3_CH3
#define PMAP_ONC_PC05     C,5  //TIM4_CH4
#define PMAP_ONC_PC06     C,6  //I2C1_SCL
#define PMAP_ONC_PC07     C,7  //I2C1_SDA
#define PMAP_ONC_PC08     C,8  //USART3_TX
#define PMAP_ONC_PC09     C,9  //USART3_RX
#define PMAP_ONC_PC10     C,10 //SPI2_SCK
#define PMAP_ONC_PC11     C,11 //SPI2_MISO
#define PMAP_ONC_PC12     C,12 //SPI2_MOSI
#define PMAP_ONC_PC13     C,13 //EVENTOUT