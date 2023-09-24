#ifndef INPUT_THREAD_H
#define INPUT_THREAD_H

#ifdef _cplusplus
extern "C"
{
#endif

void inputLoop(void) 
{
    #ifdef __NO_GET_INPUT__
        get_input = false;
    #endif

	char c = '\0';
	
START:
    if(!exitThread[THREAD_INPUT])
    {
        if(get_input) 
        {
            c = fgetc(stdin);
	        addInput(c);
        }

        SDL_Delay(5);
	
        goto START;
    }
}

#ifdef _cplusplus
}
#endif

#endif