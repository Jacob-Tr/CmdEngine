#ifndef MAP_NODES_H
#define MAP_NODES_H

#define EMPTY_NODE ((node) {0, 0, 0, ' '})
#define NULL_NODE ((node*) NULL)
typedef struct
{
	vector3l x, y, z;
	char c;
} node;

#include "includes/Engine/World/Map/Structures/Nodes/NodeUtils.h"

#endif