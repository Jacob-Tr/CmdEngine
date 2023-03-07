#ifndef MAP_H
#define MAP_H

static size_t _max_maps_ = 64;
static size_t maps = 0;

#include "includes/Engine/World/Map/MapPrimitives.h"

typedef struct
{
	size_t map_id;
	structure* strcts;
	size_t size;
} map;

static const map* null_map = ((map*) NULL);

#include "includes/Engine/World/Map/MapUtils.h"

#endif