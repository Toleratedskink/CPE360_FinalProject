#include "dc_motor.h"

// Initialize motor driver pins and PWM
void motor_init() {
	MOTOR_DDR |= (1 << MOTOR_PIN1) | (1 << MOTOR_PIN2); // Direction control pins
	PWM_DDR |= (1 << PWM_PIN); // PWM output pin

	// Timer0 Fast PWM on OC0A (PD6)
	TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B = (1 << CS01);

	OCR0A = 0; // Start with 0% duty cycle
	motor_stop(); // Ensure stopped
}

// Move motor forward with speed control
void motor_forward(uint8_t speed) {
	MOTOR_PORT |= (1 << MOTOR_PIN1);
	MOTOR_PORT &= ~(1 << MOTOR_PIN2);
	OCR0A = speed; // Set speed via PWM
}

// Move motor reverse with speed control
void motor_reverse(uint8_t speed) {
	MOTOR_PORT |= (1 << MOTOR_PIN2);
	MOTOR_PORT &= ~(1 << MOTOR_PIN1);
	OCR0A = speed; // Set speed via PWM
}

// Stop motor (no output to driver)
void motor_stop() {
	MOTOR_PORT &= ~((1 << MOTOR_PIN1) | (1 << MOTOR_PIN2));
	OCR0A = 0; // Stop PWM
}

