#include "defs.h"
#include "vertex.h"
#include "fixed.h"

#ifndef PLANE_H
#define PLANE_H

typedef struct PLANE {
    VERTEX normal;
    FIXED distance;
} PLANE;

static inline PLANE createPlane(VERTEX *normal, FIXED distance) {
    // Create a plane from data
    PLANE temp;
    temp.normal = *normal;
    temp.distance = distance;
    return temp;
}

#endif // PLANE_H
