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

double _abs(double x) {
    if (x >= 0) {
        return x;
    }
    return -x;
}

/* Find the square root of a number using fixed-point iteration.
 */
double _sqrt(double a, double precision) {
    if (a <= 0) {
        return 0.0;
    }
    double err = precision * 2;
    double x = a;
    while (err > precision) {
        double x_old = x;
        x = (x + a/x) / 2;
        err = _abs(x - x_old);
    }
    return x;
}

/* Find roots of a quadratic equation ax^2 + bx + c.
 * Roots are retruned in root1 and root2,
 * with the larger root in root1 and smaller in root2.
 */
void solve_quadratic (double a, double b, double c, double *root1, double *root2) {
    double r1 = (-b + _sqrt((b*b)-(4*a*c), 1e-6)) / (2*a);
    double r2 = (-b - _sqrt((b*b)-(4*a*c), 1e-6)) / (2*a);
    if (r1 > r2) {
        *root1 = r1;
        *root2 = r2;
    }
    else {
        *root1 = r2;
        *root2 = r1;
    }
}
