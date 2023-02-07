#ifndef VISUALS_H
#define VISUALS_H

#define EMPTY_POINT ((point) {.px = EMPTY_PIXEL, .vect = EMPTY_VECT3, .size = EMPTY_VECT2})
#define NULL_POINT ((point*) NULL)
typedef struct
{
	pixel px;
	vector3 vect;
	vector2 size;
} point;

#define EMPTY_LINE ((line) {.a = EMPTY_POINT, .b = EMPTY_POINT, .c = ((char) '\0')})
#define NULL_LINE ((line*) NULL)
typedef struct
{
	point a, b;
	char c;
} line;

#include "Includes/ConsoleGL/Visuals/VisualUtils/PointUtils.h"
#include "Includes/ConsoleGL/Visuals/VisualUtils/LineUtils.h"

typedef struct
{
	vector3 pos;
	point* pts;
	size_t point_arr_size, point_arr_entries;
	line* lines;
	size_t line_arr_size, line_arr_entries;
} object;

#include "includes/ConsoleGL/Visuals/Objects.h"

#define EMPTY_SCREEN ((screen_buffer) {.buffer = NULL_PIXEL, .size = EMPTY_VECT2})
#define NULL_SCREEN ((screen_buffer*) NULL)
typedef struct 
{
	pixel* buffer;
	vector2 size;
} screen_buffer;

#include "includes/ConsoleGL/Visuals/VisualPrimitives.h"

#include "includes/ConsoleGL/Visuals/ScreenBuffers.h"
#include "includes/ConsoleGL/Visuals/VisualUtils/ScreenDrawing.h"

#endif