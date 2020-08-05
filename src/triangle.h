#include "fixed.h"
#include "defs.h"
#include "vertex.h"
#include "plane.h"
#include "color.h"
#include <math.h>

#ifndef TRIANGLE_H
#define TRIANGLE_H

typedef struct TRIANGLE {
    int v0;
    int v1;
    int v2;
    COLOR color;
} TRIANGLE;

static inline TRIANGLE createTriangle(int v0, int v1, int v2, COLOR color) {
    // Create a triangle from data
    TRIANGLE temp;
    temp.v0 = v0;
    temp.v1 = v1;
    temp.v2 = v2;
    temp.color = color;
    return temp;
}

static inline VERTEX computeNormal(VERTEX *vertices, TRIANGLE *triangle) {
    // Use cross product to compute a normal vector to a triangle
    VERTEX normal, v1, v2;

    // Compute vectors for cross product
    v1.x = (vertices + triangle->v1)->x - (vertices + triangle->v0)->x;
    v1.y = (vertices + triangle->v1)->y - (vertices + triangle->v0)->y;
    v1.z = (vertices + triangle->v1)->z - (vertices + triangle->v0)->z;
    v2.x = (vertices + triangle->v2)->x - (vertices + triangle->v0)->x;
    v2.y = (vertices + triangle->v2)->y - (vertices + triangle->v0)->y;
    v2.z = (vertices + triangle->v2)->z - (vertices + triangle->v0)->z;

    // Compute cross product
    normal.x = fixed_multiply(v1.y, v2.z) - fixed_multiply(v1.z, v2.y);
    normal.y = fixed_multiply(v1.z, v2.x) - fixed_multiply(v1.x, v2.z);
    normal.z = fixed_multiply(v1.x, v2.y) - fixed_multiply(v1.y, v2.x);

    return normal;
}

static inline void drawTriangle(POINT *v1, POINT *v2, POINT *v3, COLOR *clr, SDL_Renderer *renderer) {
    // Draw a triangle to screen from data
    int x1, x2, x3, y1, y2, y3;
    SDL_SetRenderDrawColor(renderer, clr->red, clr->green, clr->blue, 255);
    x1 = (v1->x >> FIX_SHIFT) + WINDOW_WIDTH / 2;
    x2 = (v2->x >> FIX_SHIFT) + WINDOW_WIDTH / 2;
    x3 = (v3->x >> FIX_SHIFT) + WINDOW_WIDTH / 2;
    y1 = WINDOW_HEIGHT / 2 - (v1->y >> FIX_SHIFT) - 1;
    y2 = WINDOW_HEIGHT / 2 - (v2->y >> FIX_SHIFT) - 1;
    y3 = WINDOW_HEIGHT / 2 - (v3->y >> FIX_SHIFT) - 1;

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x1, y1, x3, y3);
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
}

static inline void fillBottomFlatTriangle(POINT *v1, POINT *v2, POINT *v3, COLOR *clr, SDL_Renderer *renderer) {
    // Ported from sunshine2k.de
    SDL_SetRenderDrawColor(renderer, clr->red, clr->green, clr->blue, 255);
    FIXED iSlope1 = fixed_divide(v2->x - v1->x, v2->y - v1->y);
    FIXED iSlope2 = fixed_divide(v3->x - v1->x, v3->y - v1->y);

    FIXED curx1 = v1->x;
    FIXED curx2 = curx1;
    int scanline;
    for (int scanlineY = ((v1->y + (1 << FIX_SHIFT)) >> FIX_SHIFT); scanlineY <= (v2->y >> FIX_SHIFT); scanlineY++) {
        scanline = WINDOW_HEIGHT / 2 - scanlineY - 1;
        SDL_RenderDrawLine(renderer, ((curx1 >> FIX_SHIFT) + WINDOW_WIDTH / 2),
            scanline, ((curx2 >> FIX_SHIFT) + WINDOW_WIDTH / 2), scanline
        );
        curx1 += iSlope1;
        curx2 += iSlope2;
    }
}

static inline void fillTopFlatTriangle(POINT *v1, POINT *v2, POINT *v3, COLOR *clr, SDL_Renderer *renderer) {
    // Ported from sunshine2k.de
    SDL_SetRenderDrawColor(renderer, clr->red, clr->green, clr->blue, 255);
    FIXED iSlope1 = fixed_divide(v3->x - v1->x, v3->y - v1->y);
    FIXED iSlope2 = fixed_divide(v3->x - v2->x, v3->y - v2->y);

    FIXED curx1 = v3->x;
    FIXED curx2 = curx1;
    int scanline;
    for (int scanlineY = ((v3->y - (1 << FIX_SHIFT)) >> FIX_SHIFT); scanlineY > (v1->y >> FIX_SHIFT); scanlineY--) {
        scanline = WINDOW_HEIGHT / 2 - scanlineY - 1;
        SDL_RenderDrawLine(renderer, ((curx1 >> FIX_SHIFT) + WINDOW_WIDTH / 2),
            scanline, ((curx2 >> FIX_SHIFT) + WINDOW_WIDTH / 2), scanline
        );
        curx1 -= iSlope1;
        curx2 -= iSlope2;
    }
}

static inline void drawFilledTriangle(POINT *v1, POINT *v2, POINT *v3, COLOR *clr, SDL_Renderer *renderer) {
    // Draw a filled triangle at points
    // Sort the vertex points

    POINT p1, p2, p3;
    p1 = *v1;
    p2 = *v2;
    p3 = *v3;
    if (p1.y > p2.y) {
        swapPoint(&p1, &p2);
    }
    if (p1.y > p3.y) {
        swapPoint(&p1, &p3);
    }
    if (p2.y > p3.y) {
        swapPoint(&p2, &p3);
    }

    // Check if bottom of triangle is flat
    if (p2.y == p3.y) {
        fillBottomFlatTriangle(&p1, &p2, &p3, clr, renderer);
    }
    // Check if top of triangle is flat
    else if (p1.y == p2.y) {
        fillTopFlatTriangle(&p1, &p2, &p3, clr, renderer);
    }
    else {
        // General case where neither top or bottom is flat
        POINT p4 = createPoint(
            p1.x + fixed_multiply(fixed_divide(p2.y - p1.y, p3.y - p1.y), (p3.x - p1.x))
            ,p2.y
        );
        fillBottomFlatTriangle(&p1, &p2, &p4, clr, renderer);
        fillTopFlatTriangle(&p2, &p4, &p3, clr, renderer);
    }
}

#endif // TRIANGLE_H
