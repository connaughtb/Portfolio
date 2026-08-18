#include "platform_hal.h"

/* Kept as a representative peripheral interface from the project. */
void i2c_write_register(uint8_t address, uint8_t reg, uint8_t value) {
    const uint8_t packet[] = { reg, value };
    platform_i2c_write(address, packet, sizeof(packet));
}
