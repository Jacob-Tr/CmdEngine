#ifndef INPUT_THREAD_H
#define INPUT_THREAD_H

#ifdef _cplusplus
extern "C"
{
#endif

void inputLoop(void) 
{
	char c = '\0';
	
START:
    if(!exitThread[THREAD_INPUT])
    {
        c = fgetc(stdin);
	    addInput(c);
	
        goto START;
    }
    
    pthread_exit(NULL);
}

#ifdef _cplusplus
}
#endif

#endif