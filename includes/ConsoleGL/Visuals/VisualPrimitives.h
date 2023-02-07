#ifndef VISUAL_PRIMITIVES_H
#define VISUAL_PRIMITIVES_H

#define EMPTY_ORIENTATION {.pos = EMPTY_VECT3, .direction = EMPTY_VECT2F, .rot = 0.0F}
typedef struct 
{
	vector3 pos;
	vector2f direction;
	float rot;
} orientation;

#define EMPTY_POLY ((poly) {NULL_POINT, ((size_t) 0)})
typedef struct
{
	point* pt_buf;
	size_t points;
} poly;

#include "Includes/ConsoleGL/Visuals/VisualPrimitives/Polys.h"

#include "Includes/ConsoleGL/Visuals/VisualPrimitives/Screen.h"

#endif