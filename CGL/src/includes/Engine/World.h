#ifndef WORLD_H
#define WORLD_H

// The maximum number of 'worlds' that can be loaded in memory at a single time (memory constraints may lower this number).
#define MAX_WORLDS ((size_t) USHRT_MAX)

// Index for 'world' objects.
typedef size_t world;

#include "includes/Engine/World/Position.h"
#include "includes/Engine/World/Meshes.h"
//#include "includes/Engine/World/Map.h"
#include "includes/Engine/World/Camera.h"
#include "includes/Engine/World/Physics.h"

#endif