#ifndef LCD_I2C_H
#define LCD_I2C_H
#include <avr/io.h>
#define LCD_ADDRESS 0x27
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04
#define LCD_COMMAND 0
#define LCD_DATA 1

void I2C_Init(void);
void I2C_Start(uint8_t address);
uint8_t I2C_Write(uint8_t data);
void I2C_Stop(void);
void LCD_Init(void);
void LCD_Cmd(uint8_t cmd);
void LCD_Char(char chr);
void LCD_String(const char *str);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_SendByte(uint8_t data, uint8_t mode);
void Timer1_Init();
void Timer1_Wait(uint8_t delay);
#endif