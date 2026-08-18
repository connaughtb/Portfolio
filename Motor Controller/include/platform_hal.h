#ifndef PLATFORM_HAL_H
#define PLATFORM_HAL_H

#include <stdbool.h>
#include <stdint.h>

/* Board-specific implementations intentionally omitted from this portfolio. */
typedef enum { PIN_INPUT, PIN_OUTPUT, PIN_ALTERNATE } PinMode;
void platform_gpio_configure(uint8_t port, uint8_t pin, PinMode mode);
void platform_gpio_write(uint8_t port, uint8_t pin, bool high);
bool platform_gpio_read(uint8_t port, uint8_t pin);
void platform_enable_interrupt(uint8_t line);
void platform_clear_interrupt(uint8_t line);
void platform_pwm_start(uint8_t timer, uint8_t channel, uint32_t prescaler, uint32_t period);
void platform_pwm_set_compare(uint8_t timer, uint8_t channel, uint32_t compare);
void platform_uart_write(const char *text);
void platform_i2c_write(uint8_t address, const uint8_t *data, uint8_t length);

#endif
