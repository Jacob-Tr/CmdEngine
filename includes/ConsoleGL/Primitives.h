#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define NULL_VECT2 {((size_t) 0), ((size_t) 0)}
typedef struct {size_t x, z;} vector2;

#define NULL_VECT2I {((int_32) 0), ((int_32) 0)}
typedef struct {int_32 x, z;} vector2i;

#define NULL_VECT2L {((int_64) 0), ((int_64) 0)}
typedef struct {int_64 x, z;} vector2l;

#define NULL_VECT2F {0.0F, 0.0F}
typedef struct {float x, z;} vector2f;

#define NULL_VECT3 {((const size_t) 0), ((const size_t) 0), ((const size_t) 0)}
typedef struct {size_t x, y, z;} vector3;

#define NULL_VECT3I {((int_32) 0), ((int_32) 0), ((int_32) 0)}
typedef struct {int_32 x, y, z;} vector3i;

#define NULL_VECT3L {((int_64) 0), ((int_64) 0), ((int_64) 0)}
typedef struct {int_64 x, y, z;} vector3l;

#define NULL_VECTOR3F {((float) 0.0), ((float) 0.0), ((float) 0.0)}
typedef struct {float x, y, z;} vector3f;

#define NULL_PIXEL {' '}
typedef struct {char c;} pixel;

#include "Includes/ConsoleGL/Primitives/VectorUtils.h"
#include "Includes/ConsoleGL/Primitives/PixelUtils.h"

#endif