#ifndef PIXEL_UTILS_H
#define PIXEL_UTILS_H

#ifdef _cplusplus
extern "C"
{
#endif

void initPixel(pixel* px, const char c) {px->c = c;}

bool isEmptyPixel(const pixel px) {return (px.c == ' ');}

char getPixelChar(const pixel px) {return px.c;}

void setPixelChar(pixel* px, const char c) {px->c = c;}

#ifdef _cplusplus
}
#endif

#endif