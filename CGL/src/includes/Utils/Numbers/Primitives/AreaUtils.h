#ifndef AREA_UTILS_H
#define AREA_UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

/*
    Check if 'vect' falls within the bounds of the two vector3s which compose area 'a'.
*/
bool doesAreaContainVector3(const v3_area a, const vector3 vect)
{
    // Separate 'vect' into three variables.
    size_t x = vect.x, y = vect.y, z = vect.z;
    
    // Two variables representing the maximum and minimum bounds of 'a'.
    vector3 max = getVector3Max(a.a, a.b), min = getVector3Min(a.a, a.b);
    
    // If any component of the vectors does not fall inside the area 'a' then return false, otherwise it is inside.
    return !(x < min.x || y < min.y || z < min.z || x > max.x || y > max.y || z > max.z);
}

/*
    Check if 'vect' falls within the bounds of the two vector2s which compose area 'a'.
*/
bool doesAreaContainVector2(const v2_area a, const vector2 vect)
{
    // Convert to vector3s.
    v3_area area3 = {vector2ToVector3(a.a), vector2ToVector3(a.b)};
    vector3 vect3 = vector2ToVector3(vect);

    // Return vector3 check solution.
    return doesAreaContainVector3(area3, vect3);
}

#ifdef __cplusplus
}
#endif

#endif