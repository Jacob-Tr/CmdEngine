#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H

#ifdef _cplusplus
extern "C"
{
#endif

void mainLoop(void)
{
	print("Welcome!");

START:
	fflush(stdout);
	FRAME_WAIT;
	
	if(!exitThread[THREAD_MAIN])
	{
	    prtScr();
	
        goto START;
	}
	
	pthread_exit(NULL);
}

#ifdef _cplusplus
}
#endif

#endif