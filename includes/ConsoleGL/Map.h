#ifndef MAP_H
#define MAP_H

#define NULL_MAP {NULL_VECT3, ((point*) NULL), ((line*) NULL), ((poly*) NULL)}
typedef struct
{
	vector3 size;
	point* pts;
	line* lns;
	poly* polys;
} world;

#include "includes/ConsoleGL/Map/MapUtils.h"

#endif