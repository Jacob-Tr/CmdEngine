#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

/*
	Forward declaration for exitMainThreadQueue to be used when necessary in the following headers.
	*To be deprecated*
*/
void exitMainThreadQueue(void);

// Declare ConsoleGL data structures and allocate memory blocks.
#include "includes/ConsoleGL.h"

/*
	General output modules for ConsoleGL application engine.
*/
// Sound effects and audio support.
#include "includes/Engine/Audio.h"
// Physics and mapping logic; sprite, model and meshes.
#include "includes/Engine/World.h"
// Screen detail logic; text, options and menus.
#include "includes/Engine/Interface.h"
// Threading logic.
#include "includes/Engine/Threading.h"

#endif