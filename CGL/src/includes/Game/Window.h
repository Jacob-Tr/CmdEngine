#ifndef WINDOW_H
#define WINDOW_H

#include "includes/Engine/Windowing/WinEvents.h"

static GPU_Target* main_target;
static SDL_Window* main_window;

struct GPU_Target a;

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t window_flags = 0;
GPU_InitFlagEnum gpu_flags = 0;

bool winInit(void)
{
	int32_t error = 0;

	error = SDL_Init(SDL_INIT_VIDEO);

	if(error)
	{
		#ifdef DEBUG
			fprintf(stderr, "Warning: Failed to initialize SDL. \"%s\"", SDL_GetError());
		#endif

		return false;
	}

	gpu_flags = (GPU_INIT_ENABLE_VSYNC | GPU_INIT_USE_ROW_BY_ROW_TEXTURE_UPLOAD_FALLBACK);
	window_flags = (SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	return true;
}

bool winCreate(SDL_Window* win, GPU_Target* target)
{
	win = SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, window_flags);
	
	if(win == NULL)
	{
		#ifdef DEBUG
			fprintf(stderr, "Warning: Creation of window failed. \"%s\".\n", SDL_GetError());
		#endif

		return false;
	}

	SDL_GetWindowSize(win, &screen_size_x, &screen_size_y);

	GPU_SetInitWindow(SDL_GetWindowID(win));
	GPU_InitRenderer(GPU_RENDERER_OPENGL_3, screen_size_x, screen_size_y, GPU_DEFAULT_INIT_FLAGS);

	target = GPU_LoadTarget(win);

	if(target == NULL)
	{
		#ifdef DEBUG
			fprintf(stderr, "Warning: Creation of GPU_Target failed. \"%s\"\n", SDL_GetError());
		#endif

		SDL_DestroyWindow(win);

		return false;
	}

	return true;
}

#ifdef __cplusplus
}
#endif

#endif