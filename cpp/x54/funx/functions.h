#include <stdint.h>

#define FUNCTIONS_VERSION        "0.0.1"
#define FUNCTIONS_VERSION_NUMBER 0000001
#define FUNCTIONS_SOURCE_ID      "2021-01-27 18:00:00 efe82ef398a2c9cb0983f9855150507a03ca3d1a"

struct bit_set_8
{
    uint8_t bits;
};

void reset_bits(struct bit_set_8* bits);

void set_bit(struct bit_set_8* bits, uint8_t index);

bool get_bit(struct bit_set_8* bits, uint8_t index, uint8_t result);