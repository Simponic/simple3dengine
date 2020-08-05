#include "color.h"
#include <SDL2/SDL.h>

#ifndef DEFS_H
#define DEFS_H

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640

#define ZPlane 1
#define viewport_width 3
#define viewport_height 2

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

typedef signed char     s8;
typedef signed short    s16;
typedef signed int      s32;

static inline void drawPixel(int x, int y, COLOR clr, SDL_Renderer *renderer) {
    // Draw pixel to screen
    SDL_SetRenderDrawColor(renderer, clr.red, clr.green, clr.blue, 255);
    SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2 + x, WINDOW_HEIGHT / 2 - y - 1);
}

static inline void updateDisplay(SDL_Renderer *renderer) {
    // Update a SDL renderer
    SDL_RenderPresent(renderer);
}

static inline void fillDisplay(SDL_Renderer *renderer, COLOR clr) {
    // Fill a renderer with color
    SDL_SetRenderDrawColor(renderer, clr.red, clr.blue, clr.green, 255);
    SDL_RenderClear(renderer);
}

#endif // DEFS_H
