 #ifndef LCD_HELPERS_H
 #define LCD_HELPERS_H
 #include <avr/io.h>
 void LCD_ShowWelcome(void);
 void LCD_PrintLine(uint8_t row, const char* text);
 void LCD_ClearRow(uint8_t row);
 #endif
