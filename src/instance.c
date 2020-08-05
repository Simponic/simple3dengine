#include "instance.h"

void renderInstance(INSTANCE *instance, SDL_Renderer *renderer) {
    // Render an instance
	// Array for projected points
    POINT projected[instance->model->vertices_length];
	// Pointers for transformed vertices
    VERTEX *transformed = malloc(sizeof(VERTEX) * instance->model->vertices_length);

    for (int i = 0; i < instance->model->vertices_length; i++) {
        // Apply translation and rotation
        *(transformed + i) = *(instance->model->vertices + i);
        applyXRotation((transformed + i), *instance->xRotation);
        applyYRotation((transformed + i), *instance->yRotation);
        applyZRotation((transformed + i), *instance->zRotation);
		*(transformed + i) = addVertices((transformed + i), instance->position);
        // Project vertices
        projected[i] = projectVertex(transformed + i);
    }
    VERTEX n, copyV;
	// A directional light source
    VERTEX playerLight = createVertex(0, 0, -1 << FIX_SHIFT);
    normalizeVertex(&playerLight);
    TRIANGLE *addr;
    FIXED intensity;
    COLOR clr;
    for (int i = 0; i < instance->model->triangles_length; i++) {
        // Render the triangle
        addr = (instance->model->triangles + i);
        n = computeNormal(transformed, addr);
        normalizeVertex(&n);
		// Intensity of light on the triangle
        intensity = fixed_multiply(dotProduct(&n, &playerLight) + (1 << FIX_SHIFT), 127 << FIX_SHIFT);
        copyV = *(transformed + addr->v2);
        normalizeVertex(&copyV);

		// Grayscale color of the triangle from light intensity
        clr = createColor(intensity >> FIX_SHIFT, intensity >> FIX_SHIFT, intensity >> FIX_SHIFT);

        if (dotProduct(&n, &copyV) < 0) {
			// The triangle is viewable by the camera
            drawFilledTriangle(
                &(projected[addr->v0]),
                &(projected[addr->v1]),
                &(projected[addr->v2]),
                &clr,
                renderer
            );

        }
    }
	transformed = NULL;
    free(transformed);
}

void destroyInstance(INSTANCE *instance) {
    // Free memory from instance
	instance->model = NULL;
	instance->position = NULL;
	instance->zRotation = NULL;
	instance->xRotation = NULL;
	instance->yRotation = NULL;
}
