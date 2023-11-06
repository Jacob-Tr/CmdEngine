#ifndef WINDOW_H
#define WINDOW_H

#include "includes/Game/Interface/Windowing/WinEvents.h"

uint32_t window_flags = 0;
GPU_InitFlagEnum gpu_flags = 0;

static GPUWindow* main_window;
static size_t active_gpu_windows = 0;

// SDL provided macro in the form of a vector2.
#define DEFAULT_WINPOS ((vector2) {SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED})

#ifdef __cplusplus
extern "C"
{
#endif

GPUWindow* __cdecl getMainWindowPtr() {return main_window;}
void __cdecl setMainWindowPtr(GPUWindow* window) {main_window = window;}

// Initialize SDL video data for use with windowing.
bool __stdcall winInit(void)
{
	int32_t error = 0;

	error = SDL_Init(SDL_INIT_VIDEO);

	if(error)
	{
		#ifdef DEBUG
			fprintf(stderr, "Error: Failed to initialize SDL. \"%s\"", SDL_GetError());
		#endif

		return false;
	}

	gpu_flags = (GPU_INIT_ENABLE_VSYNC | GPU_INIT_USE_ROW_BY_ROW_TEXTURE_UPLOAD_FALLBACK);
	window_flags = (SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	return true;
}

#define winCreateDefaultPos(win, area) winCreate((win), (area), DEFAULT_WINPOS)
bool __stdcall winCreate(SDL_Window** win, const vector2 area, const vector2 pos)
{
	*win = SDL_CreateWindow("My Window", (int32_t) pos.x, (int32_t) pos.z, (int32_t) area.x, (int32_t) area.z, window_flags);
	
	if(*win == NULL)
	{
		#ifdef DEBUG
			fprintf(stderr, "Error: Creation of window failed. \"%s\".\n", SDL_GetError());
		#endif

		return false;
	}

	SDL_GetWindowSize(*win, (int32_t*) &screen_bounds.x, (int32_t*) &screen_bounds.z);

	GPU_SetInitWindow(SDL_GetWindowID(*win));
	GPU_InitRenderer(GPU_RENDERER_OPENGL_3, (uint16_t) screen_bounds.x, (uint16_t) screen_bounds.z, GPU_DEFAULT_INIT_FLAGS);

	return true;
}

bool __cdecl applyGPUTargetToWindow(SDL_Window* win, GPU_Target** target)
{
	*target = GPU_CreateTargetFromWindow(SDL_GetWindowID(win));

	if(*target == NULL)
	{
		#ifdef DEBUG
			fprintf(stderr, "Error: Creation of GPU_Target failed. \"%s\"\n", SDL_GetError());
		#endif

		return false;
	}

	return true;
}

void __stdcall destroyGPUWindow(GPUWindow* window)
{
	if(window == ((GPUWindow*) NULL)) return;

	SDL_DestroyWindow(window->window);
	GPU_FreeTarget(window->target);

	window->id = SIZE_MAX;
}

bool __cdecl createGPUWindow(GPUWindow** window) 
{
	*window = (GPUWindow*) malloc(sizeof(GPUWindow));

	(*window)->id = ++active_gpu_windows;

	if(!winCreateDefaultPos(&((*window)->window), (vector2) Vect2(640, 480)) || !applyGPUTargetToWindow((*window)->window, &(*window)->target))
	{
		#ifdef DEBUG
			fprintf(stderr, "Error: createGPUWindow failed to create window #%zu.\n", (*window)->id);
			printSDLError(stderr);
		#endif

		destroyGPUWindow(*window);

		return false;
	}

	(*window)->id = ((size_t) SDL_GetWindowID((*window)->window));
	(*window)->updated = true;

	return true;
}

#ifdef __cplusplus
}
#endif

#endif