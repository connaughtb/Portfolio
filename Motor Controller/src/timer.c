#include "timer.h"
#include "platform_hal.h"

void timer_start_pwm(uint8_t timer, uint8_t channel, uint32_t prescaler, uint32_t period) {
    platform_pwm_start(timer, channel, prescaler, period);
    timer_set_duty_cycle(timer, channel, 0);
}

void timer_set_duty_cycle(uint8_t timer, uint8_t channel, uint8_t duty_percent) {
    if (duty_percent > 100U) duty_percent = 100U;
    /* The original firmware used a 4,000-count PWM period. */
    platform_pwm_set_compare(timer, channel, (uint32_t)duty_percent * 40U);
}
