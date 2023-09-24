#ifndef GAME_H
#define GAME_H


// Global variable used to mark exit of threads + application.
static bool exit_app = false;


// Forward declaration of functions to exit threads + application for use in the following headers.
void exitGame(void);
void exitApp(void);

// Configure environment for application runtime.
#include "includes/Game/Settings.h"
// Load and execute ConsoleGL and game engine logic.
#include "includes/GameEngine.h"
// Create a usable window for displaying output.
#include "includes/Game/Window.h"
// Begin executing interactive logic
#include "includes/Game/GameLoop.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Set global exit_app variable to true.
void exitGame(void) 
{
	exit_app = true;
}

// Hide 'exit_app' from being set directly.
#define exit_app NULL

// Cleanup, save and being shutdown.
FORCE_INLINE void exitApp(void)
{
	#ifdef DEBUG
	    setFreeMsg(true);
	#endif
	
	fflush(stdout);
	fflush(stderr);
	
	sleep(5);
	
    clrScr();
    
    #ifdef DEBUG
        fprintf(stdout, "~ Processing alloc report:\n\n");
    
        sleep(2);
    
        printAllocStats();
        
        fprintf(stdout, "\n");
        
        sleep(2);
    #endif
    
    fprintf(stdout, "~ Restoring terminal state.\n");
    
    terminalFinalize(0);
    
    sleep(1);
	
	fprintf(stdout, "~ Destroying thread queue.\n");
	
	destroyThreadPool(main_pool);
	
	sleep(1);
	
	fprintf(stdout, "~ Destroying Chatbox\n");
	
	destroyChatbox();
	
	sleep(1);
	
	fprintf(stdout, "~ Destroying main screen\n");
	destroyScreenBuffer(&main_screen_buf);

    sleep(1);
    
	#ifdef DEBUG
	    fprintf(stdout, "\n~ Processing final alloc report:\n");
	    
	    printAllocStats();
	    
	    sleep(1);
	
	    fprintf(stdout, "\n~ Finalized - Checking for memory leaks...\n");
	
	    sleep(2);
	
	    finalizeMemory();
	#else
	    fprintf(stdout, "~ Finalized");
	#endif
		
	exit(0);
}


// Initialize SDL components for later use.
bool sdlInit(void)
{
	/*
		Initialize the main window and create it for the user.
	*/

	#ifdef DEBUG
		fprintf(stdout, "~ Initializing window.\n");

		sleep(2);
	#endif

	if(!winInit())
	{
		#ifdef DEBUG
			fprintf(stdout, "Error: Window initialization failed.\n");
		#endif

		exitApp();
		
		return false;
	}
}

/*
	Initialize elements of application; conditionally lengthen loading time depending on if DEBUG mode is enabled. 
*/

extern FORCE_INLINE bool init(void)
{
	/*
		Initialize memory trackers if in DEBUG mode.

		*SDL offers this feature, to be deprecated*
	*/
	#ifdef DEBUG
	    fprintf(stdout, "~ DEBUG MODE INITIALIZING...\n  Debug mode is not a replacement for a mature debugger.\n  Parts of debug mode can avoid undefined behavior which will then remain uncaught in a release build.\n\n");
	    
	    sleep(3);
	
	    initTrckrs();
	#endif
	
	#ifdef DEBUG
	    fprintf(stdout, "~ Initializing config & terminal.\n");
	    
	    sleep(2);
	#endif

	/*
		*DEPRECATED* Change terminal arguments in linux and load program configuration.
	*/
	
	if(!(initConfig() && initTerminal()))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Startup initialization failed.\n");
		#endif
		
		exitApp();
		
		return false;
	}

	/*
		Initialize threading modules.
	*/
	
	#ifdef DEBUG
	    fprintf(stdout, "~ Initializing worker threads.\n");
	    
	    sleep(2);
	#endif

	main_pool = newThreadPool(32);

	/*
		Prepare some threads for repective tasks.
		*To be deprecated*
	*/
	
	if(!initUtilityThreads())
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Could not initialize worker threads.\n");
		#endif
		
		exitApp();
		
		return false;
	}

	sdlInit();

	/*
		Create and initialize an array of characters the size of SCREEN_MAX_X * SCREEN_MAX_Y to refresh and draw the screen.

		*To be deprecated*
	*/
	
	#ifdef DEBUG
	    fprintf(stdout, "~ Initializing screen buffer.\n");
	    
	    sleep(2);
	#endif
	
	if(!initScreen())
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Screen initialization failed.\n");
		#endif
		
		exitApp();
		
		return false;
	}

	/*
		Initialize the chatbox and add it to the main screen buffer array. 

		*To be deprecated*
	*/
	
	#ifdef DEBUG
	    fprintf(stdout, "~ Initializing chatbox.\n");
	    
	    sleep(2);
	#endif
	
	initChatbox(15, 10);

	#ifdef DEBUG
		fprintf(stdout, "~ Initialization finished.\n");
	#endif
	
	setFPS(60);
	
	return true;
}

/*
	Begin config + startup process for ConsoleGL game engine.
*/
extern void start(void)
{
	#ifdef DEBUG
	    setFreeMsg(false);
	#endif

	if(!init())
	{
		fprintf(stderr, "Error: Fatal error in engine initialization.\n");
		
		return;
	}

	if(!winCreate(main_window, main_target))
	{
		fprintf(stderr, "Error: Fatal error in window creation.\n");

		exitApp();
		return;
	}
	
	if(!startUtilityThreads())
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Failed to start threads.\n");
		    
		#endif
		
		exitApp();
		return;
	}
	
	// Begin processing game logic.
	gameLoop();
}

#ifdef _cplusplus
}
#endif

#endif