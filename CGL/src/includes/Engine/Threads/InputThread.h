#ifndef INPUT_THREAD_H
#define INPUT_THREAD_H

bool addInput(char c);

bool get_input = true;

#ifdef __cplusplus
extern "C"
{
#endif



void inputLoop(void) 
{
    #ifdef NO_GET_INPUT
        get_input = false;
    #endif

	char c = '\0';
	
START:
    if(!exitThread[THREAD_INPUT])
    {
        c = fgetc(stdin);



        if(get_input) addInput(c);

        SDL_Delay(5);
	
        goto START;
    }
}

#ifdef __cplusplus
}
#endif

#endif