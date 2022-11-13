#ifndef VISUALS_H
#define VISUALS_H

#define NULL_POINT ((point*) NULL)
typedef struct
{
	pixel px;
	vector3 vect;
	size_t width, height;
} point;

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
	size_t obj_x, obj_y, obj_z;
	point* pts;
	size_t point_arr_size, point_arr_entries;
	line* lines;
	size_t line_arr_size, line_arr_entries;
} object;

#include "includes/ConsoleGL/Visuals/Objects.h"

#define NULL_SCREEN ((screen_buffer*) NULL)
typedef struct 
{
	pixel* buffer;
	size_t buf_x_size, buf_z_size;
} screen_buffer;

#include "includes/ConsoleGL/Visuals/VisualPrimitives.h"

#include "includes/ConsoleGL/Visuals/ScreenBuffers.h"
#include "includes/ConsoleGL/Visuals/VisualUtils/ScreenDrawing.h"

#endif