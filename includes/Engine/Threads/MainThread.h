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
        if(getScreenPrint()) prtScr();
	
        goto START;
	}
}

#ifdef _cplusplus
}
#endif

#endif