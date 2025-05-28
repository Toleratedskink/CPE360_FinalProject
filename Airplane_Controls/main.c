#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <util/twi.h>

#include "servo.h"
#include "dc_motor.h"
#include "lcd_i2c.h"
#include "lcd_helpers.h"

#define LCD_ADDRESS 0x27 // Adjust if needed (try 0x3F for some modules)
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_COMMAND   0
#define LCD_DATA      1

volatile uint8_t seconds_counter = 0;
volatile uint8_t toggle_turn = 0;


// ----- Clear Servo and Reset -----
void clearServo() {
	LCD_PrintLine(0, "Left Servo = 0");
	LCD_PrintLine(1, "Right Servo = 0");
	servoL_set_angle(0);
	servoR_set_angle(180);
	_delay_ms(1000);
	LCD_ClearRow(0);
	LCD_ClearRow(1);
}

// ----- Turn Left -----
void turnRight() {
	LCD_PrintLine(0, "Turning Right");
	LCD_PrintLine(1, "Speed: 100%");
	servoL_set_angle(0);
	servoR_set_angle(0);
	_delay_ms(2000);
	LCD_ClearRow(0);
	LCD_ClearRow(1);
}

// ----- Turn Right -----
void turnLeft() {
	LCD_PrintLine(0, "Turning Left");
	LCD_PrintLine(1, "Speed: 100%");
	servoL_set_angle(180);
	servoR_set_angle(180);
	_delay_ms(2000);
	LCD_ClearRow(0);
	LCD_ClearRow(1);
}

// ----- Timer3 Setup for 1s Interrupts -----
void Timer3_Init(void) {
	TCCR3A = 0;
	TCCR3B = (1 << CS32); // Prescaler = 256
	TCNT3 = 0;
	TIMSK3 |= (1 << TOIE3); // Enable Timer3 overflow interrupt
}

// ----- ISR: Timer3 Overflow (1s) -----
ISR(TIMER3_OVF_vect) {
	motor_stop();
	TCNT3 = 0; // Reset counter for next 1s

	seconds_counter++;
	
	if (seconds_counter >= 5) {
		seconds_counter = 0;

		if (toggle_turn == 0) {
			turnLeft();
			toggle_turn = 1;
			} else {
			turnRight();
			toggle_turn = 0;
		}
	}
	motor_forward(255);
}

int main() {
	servo_init();
	motor_init();
	I2C_Init();
	LCD_Init();

	Timer3_Init();
	sei();

	while (1) {
	}
}


