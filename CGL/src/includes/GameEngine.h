#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

/*
	Forward declaration for exitMainThreadQueue to be used when necessary in the following headers.
	*To be deprecated*
*/
void exitMainThreadQueue(void);

/*
	General output modules for ConsoleGL application engine.
*/
// Sound effects and audio support.
#include "Engine/Audio.h"
// Physics and mapping logic; sprite, model and meshes.
#include "Engine/World.h"
// Data structures for visual output information.
#include "Engine/Visuals.h"
// Threading logic.
#include "Engine/Threading.h"

#endif