#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define EMPTY_VECT2 {.x = 0, .z = 0}
typedef struct {size_t x, z;} vector2;

#define EMPTY_VECT2I {.x = 0, .z = 0}
typedef struct {int_32 x, z;} vector2i;

#define EMPTY_VECT2L {.x = 0, .z = 0}
typedef struct {int_64 x, z;} vector2l;

#define EMPTY_VECT2F {.x = 0.0F, .z = 0.0F}
typedef struct {float x, z;} vector2f;

#define EMPTY_VECT3 ((vector3) {.x = 0, .y = 0, .z = 0})
typedef struct {size_t x, y, z;} vector3;

#define EMPTY_VECT3I {.x = 0, .y = 0, .z = 0}
typedef struct {int_32 x, y, z;} vector3i;

#define EMPTY_VECT3L {.x = 0, .y = 0, .z = 0}
typedef struct {int_64 x, y, z;} vector3l;

#define EMPTY_VECT3F {.x = 0.0F, .y = 0.0F, .z = 0.0F}
typedef struct {float x, y, z;} vector3f;

#define EMPTY_PIXEL {' '}
typedef struct {char c;} pixel;

#include "Includes/ConsoleGL/Primitives/VectorUtils.h"
#include "Includes/ConsoleGL/Primitives/PixelUtils.h"

#endif