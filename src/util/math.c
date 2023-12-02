#include "util.h"

/* Base-2 logarithm of a number.
 */
long logb2(size_t x) {
    size_t shift, result;
    result = (x > 0xFFFFFFFF) << 5; x >>= result;
    shift = (x > 0xFFFF) << 4; x >>= shift; result |= shift;
    shift = (x > 0xFF) << 3; x >>= shift; result |= shift;
    shift = (x > 0xF) << 2; x >>= shift; result |= shift;
    shift = (x > 0x3) << 1; x >>= shift; result |= shift;
    result |= (x >> 1);
    return result;
}

/* Round a number up to the next power of 2.
 */
long round_pow2_up(size_t x) {
    x -= 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x+1;
}