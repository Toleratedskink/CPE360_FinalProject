#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>
#include <stdint.h>

// Define servo pins
#define SERVO_DDR     DDRB
#define SERVO_PORT    PORTB
#define SERVO_PINL    PB1  // OC1A
#define SERVO_PINR    PB2  // OC1B

// Function prototypes
void servo_init(void);
void servoL_set_angle(uint8_t angle);
void servoR_set_angle(uint8_t angle);

#endif
