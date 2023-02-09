#ifndef PRIMITIVES_H
#define PRIMITIVES_H

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

#define null_pixel ((pixel*) NULL)
#define empty_pixel {.c = ' '}
typedef struct {char c;} pixel;

#include "Includes/ConsoleGL/Primitives/VectorUtils.h"
#include "Includes/ConsoleGL/Primitives/PixelUtils.h"

#endif