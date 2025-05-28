#include"lcd_helpers.h"
#include"lcd_i2c.h"
#include <string.h>
void LCD_ShowWelcome(void){
	LCD_SetCursor(0,0);
	LCD_String("Hello, CPE360!");
	LCD_SetCursor(1,0);
	LCD_String("I2C LCD Ready");
}
void LCD_PrintLine(uint8_t row, const char*text){
	LCD_SetCursor(row,0);
	LCD_String(text);
}
void LCD_ClearRow(uint8_t row){
	LCD_SetCursor(row,0);
	LCD_String("                ");
}
