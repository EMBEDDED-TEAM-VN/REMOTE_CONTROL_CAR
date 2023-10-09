#include "stm32f10x.h"
#include <stdio.h>
#include <core_cm3.h>
#include <stm32f10x_exti.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <misc.h>
#include <stdint.h>

#define GPIOA_Interrupt_Button       ((uint8_t)0x00)
#define GPIOB_Interrupt_Button       ((uint8_t)0x01)
#define GPIOC_Interrupt_Button       ((uint8_t)0x02)
#define GPIOD_Interrupt_Button       ((uint8_t)0x03)
#define GPIOE_Interrupt_Button       ((uint8_t)0x04)
#define GPIOF_Interrupt_Button       ((uint8_t)0x05)
#define GPIOG_Interrupt_Button       ((uint8_t)0x06)

typedef enum
{ GPIO_Mode_AIN = 0x0,  // Chế độ Analog Input (Đầu vào tín hiệu analog)
  GPIO_Mode_IN_FLOATING = 0x04,  // Chế độ Input Floating (Đầu vào không kéo lên/kéo xuống)
  GPIO_Mode_IPD = 0x28,     // Chế độ Input Pull-Down (Đầu vào kéo xuống)
  GPIO_Mode_IPU = 0x48,     // Chế độ Input Pull-Up (Đầu vào kéo lên)
  GPIO_Mode_Out_OD = 0x14,  // Chế độ Output Open-Drain (Đầu ra mở rơi)
  GPIO_Mode_Out_PP = 0x10,  // Chế độ Output Push-Pull (Đầu ra đẩy)
  GPIO_Mode_AF_OD = 0x1C,   // Chế độ Alternate Function Open-Drain (Chức năng thay thế mở rơi)
  GPIO_Mode_AF_PP = 0x18    // Chế độ Alternate Function Push-Pull (Chức năng thay thế đẩy)
}GPIOModeInterrButton_TypeDef;