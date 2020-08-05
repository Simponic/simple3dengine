#include "defs.h"
#include "fixed.h"
#include "vertex.h"
#include "triangle.h"
#include "pt.h"

#ifndef MODEL_H
#define MODEL_H

typedef struct MODEL {
    VERTEX *vertices;
    int vertices_length;
    TRIANGLE *triangles;
    int triangles_length;
    VERTEX bounds_center;
} MODEL;

void initializeCube();
void destroyModel();

#endif // MODEL_H
