#include "defs.h"
#include "color.h"
#include "model.h"
#include "instance.h"
#include "fixed.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <unistd.h>

int runningGame = 1;

int main() {
	// Create sdl window
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

	// Array of keys being pressed
    const unsigned char *keys = SDL_GetKeyboardState(NULL);

	// Initialize sdl window
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    fillDisplay(renderer, createColor(0, 0, 0));
	
	// Positions and rotations of each cube
    VERTEX positions[2] = {createVertex(2 << FIX_SHIFT, 0 << FIX_SHIFT, 7 << FIX_SHIFT),
        createVertex(-2 << FIX_SHIFT, 0, 7 << FIX_SHIFT)
    };
    FIXED xRots[2] = {0 << FIX_SHIFT, 0 << FIX_SHIFT};
    FIXED yRots[2] = {30 << FIX_SHIFT, 30 << FIX_SHIFT};
    FIXED zRots[2] = {0 << FIX_SHIFT, 0 << FIX_SHIFT};

	// Create cube and instances of cube
    MODEL cube;
    INSTANCE instances[2];
    for (int i = 0; i < 2; i++) {
		// Set properties of each cube
        instances[i].scale = 1;
        instances[i].xRotation = &xRots[i];
        instances[i].yRotation = &yRots[i];
        instances[i].zRotation = &zRots[i];
        instances[i].model = &cube;
        instances[i].position = &positions[i];
    }
	// Initialize the base cube model
    initializeCube(&cube);

    while(runningGame) {
		// Draw the cubes and interact with them
        fillDisplay(renderer, createColor(0,0,0));
        for (int i = 0; i < 2; i++) {
            renderInstance(&instances[i], renderer);
        }
        updateDisplay(renderer);
        while (SDL_PollEvent(&event)) {
            for (int i = 0; i < 2; i++) {
				// Check events and update each cube accordingly
                if (event.type == SDL_QUIT) {
                    runningGame = 0;
                }
                if (keys[SDL_SCANCODE_RIGHT]) {
                    positions[i].x += float_to_fixed(0.2);
                }
                if (keys[SDL_SCANCODE_LEFT]) {
                    positions[i].x -= float_to_fixed(0.2);
                }
                if (keys[SDL_SCANCODE_DOWN]) {
                    positions[i].y -= float_to_fixed(0.1);
                }
                if (keys[SDL_SCANCODE_UP]) {
                    positions[i].y += float_to_fixed(0.1);
                }
                if (keys[SDL_SCANCODE_W]) {
                    positions[i].z += float_to_fixed(0.1);
                }
                if (keys[SDL_SCANCODE_S]) {
                    positions[i].z -= float_to_fixed(0.1);
                }
                if (keys[SDL_SCANCODE_Q]) {
                    xRots[i] += float_to_fixed(1);
                }
                if (keys[SDL_SCANCODE_E]) {
                    xRots[i] += float_to_fixed(-1);
                }
                if (keys[SDL_SCANCODE_Z]) {
                    zRots[i] += float_to_fixed(1);
                }
                if (keys[SDL_SCANCODE_C]) {
                    zRots[i] += float_to_fixed(-1);
                }
                if (keys[SDL_SCANCODE_A]) {
                    yRots[i] += float_to_fixed(1);
                }
                if (keys[SDL_SCANCODE_D]) {
                    yRots[i] += float_to_fixed(-1);
                }
            }
        }
        sleep(.1);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

	destroyModel(&cube);
	for (int i = 0; i < 2; i++) {
		destroyInstance(&instances[i]);
	}
    return EXIT_SUCCESS;
}
