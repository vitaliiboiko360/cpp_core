#include "../functions.h"


void reset_bits(struct bit_set_8* bits)
{
    bits->bits = 0;
}

void set_bit(struct bit_set_8* bits, uint8_t index)
{
    if (index > 7)
    {
        return;
    }

    bits->bits = bits->bits | (1U << index);
}

bool get_bit(struct bit_set_8* bits, uint8_t index, uint8_t* result)
{
    if (index > 7)
    {
        return false;
    }

    *result = (bits->bits >> index) & 1U;
    return true;
}