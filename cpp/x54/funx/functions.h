#include <stdint.h>

struct bit_set_8
{
    uint8_t bits;
};

void reset_bits(struct bit_set_8* bits);

void set_bit(struct bit_set_8* bits, uint8_t index);

bool get_bit(struct bit_set_8* bits, uint8_t index, uint8_t result);