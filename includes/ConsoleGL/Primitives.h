#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define NULL_VECT2 ((vector2) {((size_t) 0), ((size_t) 0)})
typedef struct {size_t x, z;} vector2;

#define NULL_VECT2I ((vector2i) {((int_32) 0), ((int_32) 0)})
typedef struct {int_32 x, z;} vector2i;

#define NULL_VECT2L ((vector2l) {((int_64) 0), ((int_64) 0)})
typedef struct {int_64 x, z;} vector2l;

#define NULL_VECT2F ((vector2f) {((float) 0.0), ((float) 0.0)})
typedef struct {float x, z;} vector2f;

#define NULL_VECT3 ((vector3) {((size_t) 0), ((size_t) 0), ((size_t) 0)})
typedef struct {size_t x, y, z;} vector3;

#define NULL_VECT3I ((vector3i) {((int_32) 0), ((int_32) 0), ((int_32) 0)})
typedef struct {int_32 x, y, z;} vector3i;

#define NULL_VECT3L ((vector3l) {((int_64) 0), ((int_64) 0), ((int_64) 0)})
typedef struct {int_64 x, y, z;} vector3l;

#define NULL_VECTOR3F ((vector3f) {((float) 0.0), ((float) 0.0), ((float) 0.0)})
typedef struct {float x, y, z;} vector3f;

#define NULL_PIXEL ((pixel) {' '})
typedef struct {char c;} pixel;

#include "Includes/ConsoleGL/Primitives/VectorUtils.h"
#include "Includes/ConsoleGL/Primitives/PixelUtils.h"

#endif