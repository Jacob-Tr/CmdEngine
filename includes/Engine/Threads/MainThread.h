#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H

#ifdef __cplusplus
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
		#ifdef DEBUG
			if(!getScreenPrint()) goto START;
		#endif

        prtScr();
	
        goto START;
	}
}

#ifdef _cplusplus
}
#endif

#endif