#include "platform_hal.h"

/* GPIO use in this project: encoder inputs, motor H-bridge direction pins,
 * and a timer alternate-function output for PWM. */
void motor_gpio_init(void) {
    platform_gpio_configure(0, 7, PIN_OUTPUT); /* H-bridge IN1 */
    platform_gpio_configure(0, 6, PIN_OUTPUT); /* H-bridge IN2 */
    platform_gpio_configure(0, 4, PIN_INPUT);  /* encoder channel A */
    platform_gpio_configure(0, 10, PIN_INPUT); /* encoder channel B */
}
