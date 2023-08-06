#define __PTR_SIZE__ 4
#define SHORT_TYPE_NAMES
//#define DEBUG
#define __NO_SCREEN_PRINT__
//#define __NO_GET_INPUT__
#define __PRINT_ALL_ALLOCS__

#include "includes/Utils.h"

// Used in Window.h.

SDL_Renderer* renderer;
SDL_RendererInfo* render_info;

int32_t total_drivers;
int32_t screen_size_x = 0, screen_size_y = 0;

#include "includes/Game.h"

int main(void)
{
	total_drivers = SDL_GetNumRenderDrivers();

	render_info = ((SDL_RendererInfo*) malloc(sizeof(SDL_RendererInfo)));

	SDL_zero(render_info);



	for(size_t i = 0; i < ((size_t) total_drivers); i++)
	{
		SDL_GetRendererInfo(SDL_CreateRenderer(main_window, ((int) i), 0), render_info);
		fprintf(stdout, "Info #%zu: %s\n", i, render_info->name);
	}

	fprintf(stdout, "Total: %d\n", total_drivers);

	//start();
	return 0;
}