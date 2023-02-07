#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "includes/Engine/World/Map/Structures/Nodes.h"

static size_t _max_structures_ = 256;

#define MAX_STRUCTURES 1024

#define EMPTY_STRUCTURE ((structure) {.strct_id = 0, .node_buf = ((node*) NULL), .size = 0})
#define NULL_STRUCTURE ((structure*) NULL)
typedef struct
{
	size_t strct_id;
	node* node_buf;
	size_t size;
} structure;

#include "includes/Engine/World/Map/Structures/StructureUtils.h"

#endif