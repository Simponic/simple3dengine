#include "model.h"
#include <stdlib.h>

void initializeCube(MODEL *cube) {
    // Initialize a cube model
	cube->bounds_center = createVertex(0, 0, 0);
    COLOR red = createColor(255,0,0);
    COLOR green = createColor(0,255,0);
    COLOR blue = createColor(0,0,255);
    COLOR yellow = createColor(255,255,0);
    COLOR pink = createColor(255, 0, 100);
    COLOR weird = createColor(100, 255, 70);
    cube->vertices = malloc(sizeof(VERTEX) * 8);
    cube->triangles = malloc(sizeof(TRIANGLE) * 12);
    cube->vertices_length = 8;
    cube->triangles_length = 12;
    VERTEX vertices[8] = {
        createVertex( -1 << FIX_SHIFT, -1 << FIX_SHIFT, -1 << FIX_SHIFT), // (0,0,0) 0
        createVertex( -1 << FIX_SHIFT,  1 << FIX_SHIFT, -1 << FIX_SHIFT), // (0,1,0) 1
        createVertex(  1 << FIX_SHIFT,  1 << FIX_SHIFT, -1 << FIX_SHIFT), // (1,1,0) 2
        createVertex(  1 << FIX_SHIFT, -1 << FIX_SHIFT, -1 << FIX_SHIFT), // (1,0,0) 3
        createVertex(  1 << FIX_SHIFT,  1 << FIX_SHIFT,  1 << FIX_SHIFT), // (1,1,1) 4
        createVertex(  1 << FIX_SHIFT, -1 << FIX_SHIFT,  1 << FIX_SHIFT), // (1,0,1) 5
        createVertex( -1 << FIX_SHIFT,  1 << FIX_SHIFT,  1 << FIX_SHIFT), // (0,1,1) 6
        createVertex( -1 << FIX_SHIFT, -1 << FIX_SHIFT,  1 << FIX_SHIFT), // (0,0,1) 7
    };
    TRIANGLE triangles[12] = {
        createTriangle( 0, 1, 2, red),
        createTriangle( 0, 2, 3, red),
        createTriangle( 3, 2, 4, green),
        createTriangle( 3, 4, 5, green),
        createTriangle( 5, 4, 6, blue),
        createTriangle( 5, 6, 7, blue),
        createTriangle( 7, 6, 1, yellow),
        createTriangle( 7, 1, 0, yellow),
        createTriangle( 1, 6, 4, pink),
        createTriangle( 1, 4, 2, pink),
        createTriangle( 5, 7, 0, weird),
        createTriangle( 5, 0, 3, weird),
    };
    for (int i = 0; i < 8; i++) {
        // Copy vertices data to cube
        *(cube->vertices + i) = vertices[i];
    }
    for (int i = 0; i < 12; i++) {
        // Copy triangles to cube
        *(cube->triangles + i) = triangles[i];
    }
}

void destroyModel(MODEL *model) {
	// Free memory of a model
	model->vertices = NULL;
	model->triangles = NULL;
	free(model->vertices);
	free(model->triangles);
}
