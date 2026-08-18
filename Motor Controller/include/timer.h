#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_start_pwm(uint8_t timer, uint8_t channel, uint32_t prescaler, uint32_t period);
void timer_set_duty_cycle(uint8_t timer, uint8_t channel, uint8_t duty_percent);

#endif
