#include "platform_hal.h"

/* Position samples were emitted over serial for inspection and plotting. */
void uart_write_position(uint16_t position) {
    char message[24];
    unsigned int length = 0;
    unsigned int value = position;

    do {
        message[length++] = (char)('0' + value % 10U);
        value /= 10U;
    } while (value != 0U);

    for (unsigned int i = 0; i < length / 2U; ++i) {
        const char temporary = message[i];
        message[i] = message[length - i - 1U];
        message[length - i - 1U] = temporary;
    }
    message[length++] = '\n';
    message[length] = '\0';
    platform_uart_write(message);
}
