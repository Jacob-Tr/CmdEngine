#ifndef AREA_UTILS_H
#define AREA_UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

bool doesAreaContainVector3(const v3_area a, const vector3 vect)
{
    vector3 b = a.a, c = a.b;
    size_t x = vect.x, y = vect.y, z = vect.z;
    
    vector3 max = {.x = (b.x >= c.x) ? b.x : c.x, .y = (b.y >= c.y) ? b.y : c.y, .z = (b.z >= c.z) ? b.z : c.z}, min = {.x = (b.x >= c.x) ? c.x : b.x, .y = (b.y >= c.y) ? c.y : b.y, .z = (b.z >= c.z) ? c.z : b.z};
    
    for(size_t i = 0; i < 3; i++) if(x < min.x || y < min.y || z < min.z || x > max.x || y > max.y || z > max.z) return false;
    
    return true;
}

#ifdef __cplusplus
}
#endif

#endif