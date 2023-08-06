#ifndef GAMELOOP_H
#define GAMELOOP_H

void gameLoop(void)
{
	print("Welcome!");

	bool quit = false;
	
START:
	fflush(stdout);
	pollWinEvent();

	FRAME_WAIT;
	
	if(!exit_app)
	{
		#ifdef DEBUG
			if(!getScreenPrint()) goto START;
		#endif

        prtScr();
	
        goto START;
	}

	printf("lol");

	SDL_DestroyWindow(main_window);
	SDL_Quit();

	exitUtilityThreads();
	
	exitApp();
}

#endif