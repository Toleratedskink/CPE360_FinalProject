#define F_CPU 16000000UL
#include"lcd_i2c.h"
#include <string.h>
#include <stdio.h>
#include <util/twi.h>
#include <util/delay.h>

void I2C_Init(void){
	TWSR0=0x00;
	TWBR0=72;
}
void I2C_Start(uint8_t address) {
	TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));

	if ((TWSR0 & 0xF8) != TW_START)
	return 0;

	TWDR0 = address;
	TWCR0 = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));

	return (TWSR0 & 0xF8) == TW_MT_SLA_ACK;
}

uint8_t I2C_Write(uint8_t data) {
	TWDR0 = data;
	TWCR0 = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR0 & (1 << TWINT)));

	return (TWSR0 & 0xF8) == TW_MT_DATA_ACK;
}

void I2C_Stop(void) {
	TWCR0 = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	while (TWCR0 & (1 << TWSTO));
}

// -------- LCD Low-Level I2C --------
void LCD_SendByte(uint8_t data, uint8_t mode) {
	uint8_t high = data & 0xF0;
	uint8_t low = (data << 4) & 0xF0;

	I2C_Start(LCD_ADDRESS << 1);

	I2C_Write(high | LCD_BACKLIGHT | mode | LCD_ENABLE);
	_delay_us(1);
	I2C_Write(high | LCD_BACKLIGHT | mode);
	_delay_us(50);

	I2C_Write(low | LCD_BACKLIGHT | mode | LCD_ENABLE);
	_delay_us(1);
	I2C_Write(low | LCD_BACKLIGHT | mode);

	I2C_Stop();
}

void LCD_Cmd(uint8_t cmd) {
	LCD_SendByte(cmd, LCD_COMMAND);
}

void LCD_Char(char chr) {
	LCD_SendByte(chr, LCD_DATA);
}

void LCD_String(const char *str) {
	while (*str) {
		LCD_Char(*str++);
	}
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
	uint8_t addr;

	if (row == 0) {
		addr = 0x00;  // Start of row 0
		} else {
		addr = 0x40;  // Start of row 1
	}

	LCD_Cmd(0x80 + addr + col);  // 0x80 = Set DDRAM address
}

void LCD_Init(void) {
	_delay_ms(50); //Initial setup time
	LCD_Cmd(0x33); //0011 sent as 2 nibbles
	LCD_Cmd(0x32); //0011, 0010 sent as 2 nibbles
	LCD_Cmd(0x28); // 0010, 1000 4-bit, 2-line
	LCD_Cmd(0x0C); // Display ON- Look for Table 6
	LCD_Cmd(0x06); // 0000, 0110 Auto increment
	LCD_Cmd(0x01); // Clear display
	_delay_ms(2);
}
