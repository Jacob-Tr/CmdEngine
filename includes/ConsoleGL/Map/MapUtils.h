#ifndef MAP_UTILS_H
#define MAP_UTILS_H

#ifdef _cplusplus
extern "C"
{
#endif

void newWorld(world* map, const vector3 size)
{
	*map = (world) NULL_MAP;
	map->size = size;
}

#ifdef _cplusplus
}
#endif

#endif