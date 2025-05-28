#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <avr/io.h>

// Motor Control Pins
#define MOTOR_DDR DDRD
#define MOTOR_PORT PORTD
#define MOTOR_PIN1 PD2   // IN1
#define MOTOR_PIN2 PD3   // IN2

// PWM Output Pin (OC0A is on PD6)
#define PWM_DDR DDRD
#define PWM_PIN PD6

// Function Declarations
void motor_init();
void motor_forward(uint8_t speed);
void motor_reverse(uint8_t speed);
void motor_stop();

#endif
