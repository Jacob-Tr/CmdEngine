#ifndef GAMELOOP_H
#define GAMELOOP_H

// This loop runs on the application thread.
void gameLoop(void)
{
	print("Welcome!");

	bool quit = false;

	GPUWindow* win;
	
START:
	win = getMainWindowPtr();

	pollWinEvent();

	// Wait for the specified frame-rate.
	FRAME_WAIT; 
	
	if(!exit_app)
	{
		#ifdef DEBUG
			if(!getScreenPrint()) goto START;
		#endif

        //prtScr();
		GPU_Flip(win->target);
	
        goto START;
	}

	destroyGPUWindow(main_window);

	SDL_Quit();

	exitUtilityThreads();
	
	exitApp();
}

#endif