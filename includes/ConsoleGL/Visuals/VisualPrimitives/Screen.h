#ifndef SCREEN_H
#define SCREEN_H

#ifdef _cplusplus
extern "C"
{
#endif

void initOrientation(orientation* ori, const vector3 pos, const vector2f lookat, const float rot) {*ori = ((orientation) {pos, lookat, rot});}

#ifdef _cplusplus
}
#endif

#endif