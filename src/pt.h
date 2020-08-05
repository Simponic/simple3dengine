#include "defs.h"
#include "fixed.h"

#ifndef PT_H
#define PT_H

typedef struct POINT {
    FIXED x;
    FIXED y;
} POINT;

static inline void convertPointToScreen(POINT *point) {
    // Convert point where (SCREEN_WIDTH / 2 * x,
    //                  SCREEN_HEIGHT / 2 - y - 1)
	// is the origin (0,0)
    point->x += (WINDOW_WIDTH / 2) << FIX_SHIFT;
    point->y = (WINDOW_HEIGHT / 2 - (point->y >> FIX_SHIFT) - 1) << FIX_SHIFT;
}

static inline POINT createPoint(FIXED x, FIXED y) {
    // Create a point from data
    POINT temp;
    temp.x = x;
    temp.y = y;
    return temp;
}


static inline void swapPoint(POINT *p1, POINT *p2) {
    POINT temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

#endif // PT_H
