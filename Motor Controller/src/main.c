#include "motor_driver.h"
#include "platform_hal.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_MOTOR_SPEED 90.0
#define MIN_MOTOR_SPEED 10.0
#define POSITION_TOLERANCE 30.0
#define POSITION_MODULUS 1000.0

typedef struct {
    double previous_position;
    double integral;
    double kp;
    double ki;
    double kd;
} PIDController;

static double clamp(double value, double minimum, double maximum) {
    if (value < minimum) return minimum;
    if (value > maximum) return maximum;
    return value;
}

static double pid_update(PIDController *pid, double error, double position) {
    pid->integral = clamp(pid->integral + error, -200.0, 200.0);
    const double derivative = position - pid->previous_position;
    pid->previous_position = position;
    return clamp(pid->kp * error + pid->ki * pid->integral - pid->kd * derivative,
                 MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
}

/* This function represents one iteration of the original periodic RTOS task. */
void motor_control_step(PIDController *pid, uint16_t target_position) {
    const double current = motor_position();
    double signed_error = (double)target_position - current;

    /* Choose the shorter direction on the position ring. */
    if (signed_error > POSITION_MODULUS / 2.0) signed_error -= POSITION_MODULUS;
    if (signed_error < -POSITION_MODULUS / 2.0) signed_error += POSITION_MODULUS;

    const double speed = pid_update(pid, signed_error < 0 ? -signed_error : signed_error, current);
    if (signed_error > POSITION_TOLERANCE) {
        motor_set_direction((uint8_t)speed, MOTOR_FORWARD);
    } else if (signed_error < -POSITION_TOLERANCE) {
        motor_set_direction((uint8_t)speed, MOTOR_REVERSE);
    } else {
        motor_set_direction(0, MOTOR_BRAKE);
    }
}
