#ifndef PRIMITIVES_H
#define PRIMITIVES_H

/*
	'Vector' types for logically grouped variables (with 'empty_[vect]' macros for ease of use.
*/

#define empty_vector2 {.x = 0, .z = 0}
typedef struct {size_t x, z;} vector2;

#define empty_vector2i {.x = 0, .z = 0}
typedef struct {int_32 x, z;} vector2i;

#define empty_vector2l {.x = 0, .z = 0}
typedef struct {int_64 x, z;} vector2l;

#define empty_vector2f {.x = 0.0F, .z = 0.0F}
typedef struct {float x, z;} vector2f;

#define empty_vector3 {.x = 0, .y = 0, .z = 0}
typedef struct {size_t x, y, z;} vector3;

#define empty_vector3i {.x = 0, .y = 0, .z = 0}
typedef struct {int_32 x, y, z;} vector3i;

#define empty_vector3l {.x = 0, .y = 0, .z = 0}
typedef struct {int_64 x, y, z;} vector3l;

#define empty_vector3f {.x = 0.0F, .y = 0.0F, .z = 0.0F}
typedef struct {float x, y, z;} vector3f;

/*
	Vector area structures and empty macros for ease of use..
*/
#define empty_v2area {.a = empty_vector2, .b = empty_vector2}
typedef struct {vector2 a, b;} v2_area;

#define empty_v3area {.a = empty_vector3, .b = empty_vector3}
typedef struct {vector3 a, b;} v3_area;

/*
	Basic pixel color container with 'BLANK' macro for ease of use.
*/

#define BLANK_PIXEL GPU_MakeColor(0, 0, 0, 255)
typedef struct {SDL_Color c;} pixel;

// Utilities for working with Vectors.
#include "Includes/ConsoleGL/Primitives/VectorUtils.h"
// Utilities for working in regard to the bounds created by a collection of Vectors.
#include "Includes/ConsoleGL/Primitives/AreaUtils.h"

#endif