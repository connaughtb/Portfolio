#include "encoder.h"
#include "platform_hal.h"

typedef enum { STATE_00, STATE_01, STATE_10, STATE_11 } EncoderState;
static volatile uint16_t ticks;
static EncoderState previous_state;

static EncoderState read_state(void) {
    const bool a = platform_gpio_read(0, 4);
    const bool b = platform_gpio_read(0, 10);
    return (EncoderState)((a << 1U) | b);
}

void encoder_init(void) {
    ticks = 0;
    previous_state = read_state();
    platform_enable_interrupt(4);
    platform_enable_interrupt(10);
}

uint16_t encoder_read(void) { return ticks; }

void encoder_irq_handler(void) {
    const EncoderState current_state = read_state();
    const uint8_t transition = ((uint8_t)previous_state << 2U) | (uint8_t)current_state;

    switch (transition) {
        case 0x1: case 0x7: case 0xE: case 0x8:
            ticks = (ticks + 1U) % ENCODER_POSITION_MODULUS;
            break;
        case 0x2: case 0xB: case 0xD: case 0x4:
            ticks = ticks == 0 ? ENCODER_POSITION_MODULUS - 1U : ticks - 1U;
            break;
        default:
            break; /* Ignore repeated/invalid transitions. */
    }
    previous_state = current_state;
    platform_clear_interrupt(4);
    platform_clear_interrupt(10);
}
