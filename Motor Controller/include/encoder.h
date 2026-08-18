#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

#define ENCODER_POSITION_MODULUS 1000U
void encoder_init(void);
uint16_t encoder_read(void);
void encoder_irq_handler(void);

#endif
