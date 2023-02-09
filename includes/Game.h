#ifndef GAME_H
#define GAME_H

#include "includes/Game/Settings.h"
#include "includes/GameEngine.h"

#ifdef _cplusplus
extern "C"
{
#endif

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
	
	destroyThreadQueue(&main_queue);
	
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

FORCE_INLINE bool init(void)
{
	#ifdef DEBUG
	    fprintf(stdout, "~ DEBUG MODE INITIALIZING...\n  Debug mode is not a replacement for a mature debugger.\n  Parts of debug mode can avoid undefined behavior which will then remain uncaught in a release build.\n\n");
	    
	    sleep(3);
	
	    initTrckrs();
	#endif
	
	#ifdef DEBUG
	    fprintf(stdout, "~ Initializing config & terminal.\n");
	    
	    sleep(2);
	#endif
	
	if(!(initConfig() && initTerminal()))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Startup initialization failed.\n");
		#endif
		
		exitApp();
		
		return false;
	}
	
	#ifdef DEBUG
	    fprintf(stdout, "~ Initializing main thread queue.\n");
	    
	    sleep(2);
	#endif
	
	if(!initMainThreadQueue())
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Could not initialize main thread queue.\n");
		#endif
		
		exitApp();
		
		return false;
	}
	
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
	
	#ifdef DEBUG
	    fprintf(stdout, "~ Initializing chatbox.\n");
	    
	    sleep(2);
	#endif
	
	initChatbox(15, 10);
	
	setFPS(3);
	
	return true;
}

void start(void)
{
	#ifdef DEBUG
	    setFreeMsg(false);
	#endif
	
	if(!startMainThreadQueue())
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Failed to start threads.\n");
		    
		#endif
		
		exitApp();
	}
	
    exitApp();
}

#ifdef _cplusplus
}
#endif

#endif