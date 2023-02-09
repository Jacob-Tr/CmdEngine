#ifndef VISUALS_H
#define VISUALS_H

#define null_point ((point*) NULL)
#define empty_point {.px = empty_pixel, .vect = empty_vector3, .size = empty_vector2}

typedef struct
{
	pixel px;
	vector3 vect;
	vector2 size;
} point;

#define null_line ((line*) NULL)
#define empty_line {.a = empty_point, .b = empty_point, .c = ((char) '\0')}

typedef struct
{
	point a, b;
	char c;
} line;

#include "Includes/ConsoleGL/Visuals/VisualUtils/PointUtils.h"
#include "Includes/ConsoleGL/Visuals/VisualUtils/LineUtils.h"

#include "includes/ConsoleGL/Visuals/Objects.h"

#define null_screen ((screen_buffer*) NULL)
#define empty_screen {.buffer = null_pixel, .size = empty_vector2}

typedef struct 
{
	pixel* buffer;
	vector2 size;
} screen_buffer;

#include "includes/ConsoleGL/Visuals/VisualPrimitives.h"

#include "includes/ConsoleGL/Visuals/ScreenBuffers.h"
#include "includes/ConsoleGL/Visuals/VisualUtils/ScreenDrawing.h"

#endif