#include "defs.h"
#include "pt.h"
#include "vertex.h"
#include "triangle.h"
#include "model.h"
#include <math.h>
#include <stdlib.h>

#ifndef INSTANCE_H
#define INSTANCE_H

typedef struct INSTANCE {
    MODEL *model;
    VERTEX *position;
    FIXED scale;
    FIXED *xRotation;
    FIXED *yRotation;
    FIXED *zRotation;
} INSTANCE;

void renderInstance();
void destroyInstance();

#endif // INSTANCE_H
