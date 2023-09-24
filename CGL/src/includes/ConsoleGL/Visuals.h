#ifndef VISUALS_H
#define VISUALS_H

/*
	A structure for holding the coordinates of a 'point' containing it's; 'pixel' data, position and size respectively.
*/
#define empty_point {.px = empty_pixel, .vect = empty_vector3, .size = empty_vector2}
typedef struct
{
	pixel px;
	vector3 vect;
	vector2 size;
} point;

/*
	A structure for holding two points which denote a 'line'.
*/
#define empty_line {.a = empty_point, .b = empty_point, .c = ((char) '\0')}
typedef struct
{
	point a, b;
	char c;
} line;

// Untilities for working with points.
#include "Includes/ConsoleGL/Visuals/VisualUtils/PointUtils.h"
// Utilities for working with lines.
#include "Includes/ConsoleGL/Visuals/VisualUtils/LineUtils.h"

// Data structures which use points and lines to create complex polygons.
#include "includes/ConsoleGL/Visuals/Objects.h"

/*
	Structure which is used to hold data meant to be displayed in a window.
*/
#define empty_screen {.buffer = ((pixel*) NULL), .size = empty_vector2}
typedef struct 
{
	pixel* buffer;
	vector2 size;
} screen_buffer;

// Utilities for working with screen buffers.
#include "includes/ConsoleGL/Visuals/ScreenBuffers.h"
// Logic for properly displaying screen buffer info to a window.
#include "includes/ConsoleGL/Visuals/VisualUtils/ScreenDrawing.h"

#endif