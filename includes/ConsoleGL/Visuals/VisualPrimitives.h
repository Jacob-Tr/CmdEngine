#ifndef VISUAL_PRIMITIVES_H
#define VISUAL_PRIMITIVES_H

#define NULL_ORIENTATION ((orientation) {NULL_VECT3, NULL_VECT2F, ((float) 0.0)})
typedef struct 
{
	vector3 pos;
	vector2f direction;
	float rot;
} orientation;

#define NULL_POLY ((poly) {NULL_POINT, ((size_t) 0)})
typedef struct
{
	point* pt_buf;
	size_t points;
} poly;

#include "Includes/ConsoleGL/Visuals/VisualPrimitives/Polys.h"

#include "Includes/ConsoleGL/Visuals/VisualPrimitives/Screen.h"

#endif