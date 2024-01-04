#include "DevI2C.h"

#define LCD_ADDRESS 0x4E // Địa chỉ của màn hình LCD


PRIVATE void DelayMs(U32 u32DalayMs);
PRIVATE void LCDWriteCommand(U08 u08Command);
PRIVATE void LCDWriteData(U08 u08Data);
PRIVATE void I2CConfiguration(void);

PRIVATE void I2CConfiguration(void)
{
    I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); // Bật Clock cho I2C1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // Bật Clock cho GPIOB

    // Cấu hình chân SDA và SCL
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Cấu hình I2C1
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 100000;

    I2C_Init(I2C1, &I2C_InitStructure);

    // Bật I2C1
    I2C_Cmd(I2C1, ENABLE);
}

PRIVATE void LCDWriteCommand(U08 u08Command)
{
    U08 data_u, data_l;
    U08 data_t[4];
    data_u = (u08Command & 0xf0);
    data_l = ((u08Command << 4) & 0xf0);
    data_t[0] = data_u | 0x0C;  // Enable=1, Rs=0 (lệnh)
    data_t[1] = data_u | 0x08;  // Enable=0, Rs=0 (lệnh)
    data_t[2] = data_l | 0x0C;  // Enable=1, Rs=0 (lệnh)
    data_t[3] = data_l | 0x08;  // Enable=0, Rs=0 (lệnh)

    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, LCD_ADDRESS, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    for (int i = 0; i < 4; i++)
    {
        I2C_SendData(I2C1, data_t[i]);
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }

    I2C_GenerateSTOP(I2C1, ENABLE);
    DelayMs(1); // Delay 1ms
}

PRIVATE void LCDWriteData(U08 u08Data)
{
    U08 data_u, data_l;
    U08 data_t[4];
    data_u = (u08Data & 0xf0);
    data_l = ((u08Data << 4) & 0xf0);
    data_t[0] = data_u | 0x0D;  // Enable=1, Rs=1 (dữ liệu)
    data_t[1] = data_u | 0x09;  // Enable=0, Rs=1 (dữ liệu)
    data_t[2] = data_l | 0x0D;  // Enable=1, Rs=1 (dữ liệu)
    data_t[3] = data_l | 0x09;  // Enable=0, Rs=1 (dữ liệu)

    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, LCD_ADDRESS, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    for (int i = 0; i < 4; i++)
    {
        I2C_SendData(I2C1, data_t[i]);
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }

    I2C_GenerateSTOP(I2C1, ENABLE);
    DelayMs(1); // Delay 1ms
}

PRIVATE void DelayMs(U32 u32DalayMs)
{
    U32 u32Delay = (SystemCoreClock / 1000) * u32DalayMs;
    while (u32Delay--)
    {
    }
}

PUBLIC void DevLCDInit(void)
{
	I2CConfiguration();
    LCDWriteCommand(0x33); // Khởi tạo màn hình
    LCDWriteCommand(0x32);
    LCDWriteCommand(0x28); // Chế độ 4-bit, 2 dòng, font 5x7
    LCDWriteCommand(0x0C); // Bật màn hình, tắt con trỏ nhấp nháy
    LCDWriteCommand(0x06); // Tự động di chuyển con trỏ
    LCDWriteCommand(0x01); // Xóa màn hình
    DelayMs(2); // Delay 2ms
}

PUBLIC void DevLCDSetCursor(U08 u08Row, U08 u08Colum)
{
    U08 u08Address = 0;

    if (u08Row == 0)
    {
    	u08Address = 0x80 + u08Colum; // Địa chỉ dòng 1
    }
    else
    {
    	u08Address = 0xC0 + u08Colum; // Địa chỉ dòng 2
    }

    LCDWriteCommand(u08Address);
}

PUBLIC void DevLCDPrintString(char *str)
{
    while (*str)
    {
        LCDWriteData(*str++);
    }
}

PUBLIC void DevLCDClear(void)
{
    // Gửi lệnh xóa màn hình (0x01) tới LCD
    LCDWriteCommand(0x01);
    // Đợi một khoảng thời gian ngắn để cho LCD xóa màn hình
    DelayMs(2);
    // Đưa con trỏ văn bản về vị trí ban đầu (dòng 1, cột 1)
    DevLCDSetCursor(0, 0);
}
