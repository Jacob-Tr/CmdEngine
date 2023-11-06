#ifndef PRIMITIVE_UTILS_H
#define PRIMITIVE_UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

void initPixel(pixel* px, SDL_Color cl, char c)
{
	px->cl = cl;
	px->c = c;
}

char getPixelChar(const pixel px) {return px.c;}
SDL_Color getPixelColor(const pixel px) {return px.cl;}

#ifdef __cplusplus
}
#endif

// Utilities for working with Vectors.
#include "Includes/Utils/Numbers/Primitives/VectorUtils.h"
// Utilities for working in regard to the bounds created by a collection of Vectors.
#include "Includes/Utils/Numbers/Primitives/AreaUtils.h"

#endif