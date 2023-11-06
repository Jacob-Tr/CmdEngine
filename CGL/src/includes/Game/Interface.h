#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct 
{
	GPU_Target* target;
	SDL_Window* window;
	screen_buffer buffer;
	size_t id;
	bool updated;
} GPUWindow;

#include "Interface/ChatBox.h"

#endif