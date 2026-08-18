#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

typedef enum { MOTOR_COAST, MOTOR_FORWARD, MOTOR_REVERSE, MOTOR_BRAKE } MotorDirection;
void motor_init(void);
void motor_set_direction(uint8_t duty_cycle, MotorDirection direction);
uint16_t motor_position(void);

#endif
