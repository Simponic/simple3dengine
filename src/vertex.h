#include "defs.h"
#include "fixed.h"
#include "pt.h"
#include <math.h>

#ifndef VERTEX_H
#define VERTEX_H

typedef struct VERTEX {
    FIXED x;
    FIXED y;
    FIXED z;
} VERTEX;

static inline POINT viewportToScreen (POINT *point) {
    // Convert a viewport coordinate to screen x, y
    return createPoint(fixed_multiply(point->x, fixed_divide(WINDOW_WIDTH << FIX_SHIFT, viewport_width << FIX_SHIFT)),
        fixed_multiply(point->y, fixed_divide(WINDOW_HEIGHT << FIX_SHIFT, viewport_height << FIX_SHIFT))
    );
}

static inline POINT projectVertex(VERTEX *vertex) {
    // Project a vertex to a point
    POINT temp;
    if (vertex->z != 0) {
        // Make sure we don't divide by zero
        temp = createPoint(fixed_multiply(vertex->x, fixed_divide(ZPlane << FIX_SHIFT, vertex->z)),
            fixed_multiply(vertex->y, fixed_divide(ZPlane << FIX_SHIFT, vertex->z))
        );
    }
    else {
        temp = createPoint(0, 0);
    }
    temp = viewportToScreen(&temp);
    return temp;
}

static inline VERTEX createVertex(FIXED x, FIXED y, FIXED z) {
    // Create a vertex from data
    VERTEX temp;
    temp.x = x;
    temp.y = y;
    temp.z = z;
    return temp;
}

static inline VERTEX addVertices(VERTEX *a, VERTEX *b) {
	// Add two vertices together
	VERTEX temp = createVertex(a->x + b->x, a->y + b->y, a->z + b->z);
	return temp;
}

static inline void applyXRotation(VERTEX *vertex, FIXED xRotation) {
    // Apply rotation to vertex on x-axis
    FIXED sinTheta = float_to_fixed(sin(fixed_to_float(xRotation) * (3.14159 / 180)));
    FIXED cosTheta = float_to_fixed(cos(fixed_to_float(xRotation) * (3.14159 / 180)));
    FIXED y = vertex->y;
    FIXED z = vertex->z;
    vertex->y = fixed_multiply(y, cosTheta) - fixed_multiply(z, sinTheta);
    vertex->z = fixed_multiply(z, cosTheta) + fixed_multiply(y, sinTheta);
}

static inline void applyYRotation(VERTEX *vertex, FIXED yRotation) {
    // Apply rotation to vertex on y-axis
    FIXED sinTheta = float_to_fixed(sin(fixed_to_float(yRotation) * (3.14159 / 180)));
    FIXED cosTheta = float_to_fixed(cos(fixed_to_float(yRotation) * (3.14159 / 180)));
    FIXED x = vertex->x;
    FIXED z = vertex->z;
    vertex->x = fixed_multiply(x, cosTheta) + fixed_multiply(z, sinTheta);
    vertex->z = fixed_multiply(z, cosTheta) - fixed_multiply(x, sinTheta);
}

static inline void applyZRotation(VERTEX *vertex, FIXED zRotation) {
    // Apply rotation to vertex on z-axis
    FIXED sinTheta = float_to_fixed(sin(fixed_to_float(zRotation) * (3.14159 / 180)));
    FIXED cosTheta = float_to_fixed(cos(fixed_to_float(zRotation) * (3.14159 / 180)));
    FIXED x = vertex->x;
    FIXED y = vertex->y;
    vertex->x = fixed_multiply(x, cosTheta) - fixed_multiply(y, sinTheta);
    vertex->y = fixed_multiply(y, cosTheta) + fixed_multiply(x, sinTheta);
}

static inline VERTEX crossProduct(VERTEX *a, VERTEX *b) {
    // Calculate the cross product of two vertices
    return createVertex(
        fixed_multiply(a->y, b->z) - fixed_multiply(a->z, b->y),
        fixed_multiply(a->z, b->x) - fixed_multiply(a->x, b->z),
        fixed_multiply(a->x, b->y) - fixed_multiply(a->y, b->x)
    );
}

static inline FIXED dotProduct(VERTEX *a, VERTEX *b) {
    // Dot two vertices
    FIXED product = fixed_multiply(a->x, b->x) +
        fixed_multiply(a->y, b->y) +
        fixed_multiply(a->z, b->z);
    return product;
}

static inline void normalizeVertex(VERTEX *vertex) {
    // Normalize (magnitude = 1) a vertex
    float x = fixed_to_float(vertex->x);
    float y = fixed_to_float(vertex->y);
    float z = fixed_to_float(vertex->z);
    float d = sqrtf(x*x + y*y + z*z);

    vertex->x = float_to_fixed(fixed_to_float(vertex->x) / d);
    vertex->y = float_to_fixed(fixed_to_float(vertex->y) / d);
    vertex->z = float_to_fixed(fixed_to_float(vertex->z) / d);
}

#endif // VERTEX_H
