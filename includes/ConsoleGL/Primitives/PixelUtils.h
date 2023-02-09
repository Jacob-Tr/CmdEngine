#ifndef PIXEL_UTILS_H
#define PIXEL_UTILS_H

#ifdef _cplusplus
extern "C"
{
#endif

void initPixel(pixel* px, const char c) {px->c = c;}

char getPixelChar(const pixel px) {return px.c;}

void setPixelChar(pixel* px, const char c) {px->c = c;}

void destroyPixel(pixel* px) {px->c = ' ';}

#ifdef _cplusplus
}
#endif

#endif