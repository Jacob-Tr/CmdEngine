#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define Vect2(a, b) {.x = (a), .z = (b)}
#define Vect3(a, b, c) {.x = (a), .y = (b), .z = (c)}

/*
	'Vector' types for logically grouped variables (with 'empty_[vect]' macros for ease of use.
*/
typedef struct {int16_t x, z;} vector2s;
typedef struct {uint16_t x, z;} vector2us;
typedef struct {int32_t x, z;} vector2i;
typedef struct {int64_t x, z;} vector2l;
typedef struct {size_t x, z;} vector2;
typedef struct {float x, z;} vector2f;

typedef struct {int16_t x, y, z;} vector3s;
typedef struct {int16_t x, y, z;} vector3us;
typedef struct {int32_t x, y, z;} vector3i;
typedef struct {int64_t x, y, z;} vector3l;
typedef struct {size_t x, y, z;} vector3;
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
typedef struct 
{
	SDL_Color cl;
	char c;
} pixel;

// Utilities for working with these primitives
#include "includes/Utils/Numbers/Primitives/PrimitiveUtils.h"

#endif