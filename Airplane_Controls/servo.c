#include "servo.h"

// Initialize Timer1 for dual servo control (OC1A = PB1, OC1B = PB2)
void servo_init(void) {
	SERVO_DDR |= (1 << SERVO_PINL) | (1 << SERVO_PINR); // Set pins as output

	// Fast PWM mode 14: ICR1 is TOP
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8

	ICR1 = 39999;  // TOP for 20ms period (50 Hz)

	// Initialize both servos to neutral (1.5ms pulse)
	OCR1A = 3000; // Left servo
	OCR1B = 3000; // Right servo
}

// Set angle for left servo (OC1A)
void servoL_set_angle(uint8_t angle) {
	OCR1A = 1000 + (angle * 11);  // Map 0–180° to 1ms–2ms pulse
}

// Set angle for right servo (OC1B)
void servoR_set_angle(uint8_t angle) {
	OCR1B = 1000 + (angle * 11);  // Same mapping
}
