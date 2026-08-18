#include "encoder.h"
#include "motor_driver.h"
#include "platform_hal.h"
#include "timer.h"

void motor_init(void) {
    encoder_init();
    platform_gpio_configure(0, 7, PIN_OUTPUT);
    platform_gpio_configure(0, 6, PIN_OUTPUT);
    timer_start_pwm(2, 2, 16, 4000);
}

void motor_set_direction(uint8_t duty_cycle, MotorDirection direction) {
    switch (direction) {
        case MOTOR_COAST:
            timer_set_duty_cycle(2, 2, 0);
            platform_gpio_write(0, 7, false);
            platform_gpio_write(0, 6, false);
            break;
        case MOTOR_FORWARD:
            timer_set_duty_cycle(2, 2, duty_cycle);
            platform_gpio_write(0, 7, true);
            platform_gpio_write(0, 6, false);
            break;
        case MOTOR_REVERSE:
            timer_set_duty_cycle(2, 2, duty_cycle);
            platform_gpio_write(0, 7, false);
            platform_gpio_write(0, 6, true);
            break;
        case MOTOR_BRAKE:
            timer_set_duty_cycle(2, 2, 0);
            platform_gpio_write(0, 7, true);
            platform_gpio_write(0, 6, true);
            break;
    }
}

uint16_t motor_position(void) { return encoder_read(); }
