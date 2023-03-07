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
        #ifndef __NO_GET_INPUT__
            c = fgetc(stdin);
	        addInput(c);
        #endif
	
        goto START;
    }
}

#ifdef _cplusplus
}
#endif

#endif