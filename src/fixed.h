#include "defs.h"

#ifndef FIXED_H
#define FIXED_H

#define FIX_SHIFT 8
#define HALF_FIX_SHIFT 4
#define FIX_SCALE ( 1 << FIX_SHIFT )
#define FIX_SCALE_FLOAT ((float)(FIX_SCALE))

typedef s32 FIXED;

static inline FIXED fixed_OverMultiply(FIXED a, FIXED b) {
    // This should multiply two fixed-point numbers sacrificing a little
    // accuracy in exchange for less chance of an overflow

    return ((a >> HALF_FIX_SHIFT) * (b >> HALF_FIX_SHIFT));
}

static inline FIXED fixed_multiply (FIXED a, FIXED b) {
    // Multiply two fixed numbers. Possibility of overflow.
    return (a * b) >> FIX_SHIFT;
}

static inline FIXED fixed_divide(FIXED a, FIXED b) {
    if (b != 0){
        return (a * FIX_SCALE) / b;
    }
    else {
        return 100000 << FIX_SHIFT;
    }
}

static inline FIXED float_to_fixed(float a) {
    // Convert a float to fixed point
    return ((FIXED)(a * FIX_SCALE_FLOAT));
}

static inline float fixed_to_float(FIXED a) {
    // Convert fixed point to float
    return (a / FIX_SCALE_FLOAT);
}

static inline void swapFixed(FIXED *a, FIXED *b) {
    // Swap two fixed point integer pointers
    FIXED temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

static inline FIXED fixed_sqrt(FIXED a, int iterations) {
    // Calculate square root of a fixed-point number using Binary-Search
    FIXED low = 0;
    FIXED high = a;
    FIXED mid;
    FIXED midSquared;
    for (int i = 0; i < iterations; i++) {
        mid = fixed_divide((low + high), 2 << FIX_SHIFT);
        midSquared = fixed_OverMultiply(mid, mid);
        if (midSquared == a) {
            return mid;
        }
        else if (midSquared > a) {
            high = mid;
        }
        else {
            low = mid;
        }
    }
    return mid;
}

#endif // FIXED_H
