#ifndef WINEVENTS_H
#define WINEVENTS_H

static SDL_Event event;

#ifdef __cplusplus
extern "C"
{
#endif

void pollWinEvent(void)
{
	while(SDL_PollEvent(&event)) 
	{
		switch(event.type)
		{
			case SDL_QUIT:
			{
				exit_app = true;
				break;
			}

			case SDL_KEYDOWN:
			{

			}

			case SDL_MOUSEBUTTONDOWN:
			{
			}

			default: break;
		}
	}
}

#ifdef __cplusplus
}
#endif

#endif