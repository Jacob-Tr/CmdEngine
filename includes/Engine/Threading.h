#ifndef THREADING_H
#define THREADING_H

enum thread_enm
{
	THREAD_MAIN,
	THREAD_INPUT,
	THREAD_NULL
};

static bool exitThread[THREAD_NULL] = {false, false};

#include "includes/Engine/Threads/MainThread.h"
#include "includes/Engine/Threads/InputThread.h"

threadQueue main_queue;
thread_attr attr[THREAD_NULL];

#ifdef __cplusplus
extern "C"
{
#endif

bool initMainThreadQueue(void)
{
	newThreadQueue(&main_queue, THREAD_NULL);
	
	THREAD* main_thread = getThreadPtrFromQueue(&main_queue, THREAD_MAIN), *input_thread = getThreadPtrFromQueue(&main_queue, THREAD_INPUT);

	if((main_thread == NULL) || (input_thread == NULL))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Could not get thread pointer from thread queue.\n");
		#endif
		
		return false;
	}
	
	thread_attr* main_attr = &attr[THREAD_MAIN], *input_attr = &attr[THREAD_INPUT];
	
	if(!(initThread(main_thread, main_attr, ((start_func) &(mainLoop)), NULL, 0)))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Could not initialize main thread. (%p)\n", main_thread);
		#endif
		
		return false;
	}

	if(!(initThread(input_thread, input_attr, ((start_func) &(inputLoop)), NULL, 0)))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Could not initialize input thread. (%p)\n", input_thread);
		#endif
		
		return false;
	}
	
	if(!(addThreadToQueue(&main_queue, main_thread) && addThreadToQueue(&main_queue, input_thread)))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Failed to add main and/or input thread to main thread queue.\n");
		#endif
		
		return false;
	}
	
	return true;
}

void exitMainThread(void) {exitThread[THREAD_MAIN] = true;}

void exitInputThread(void) {exitThread[THREAD_INPUT] = true;}

void exitMainThreadQueue(void)
{
	exitInputThread();
	exitMainThread();
}

bool startMainThreadQueue(void)
{
	if(!main_queue.init)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Attempted to start main queue without initialization.\n");
	    #endif
	    
	    return false;
	}
	
	if(main_queue.started)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Attempted to start main queue multiple times.\n");
		#endif
		
		return false;
	}
	
	startThreadsInQueue(&main_queue);
    joinQueue(&main_queue);
    
    return true;
}

#ifdef _cplusplus
}
#endif

#endif