#ifndef NETWORK_THREAD_H
#define NETWORK_THREAD_H

#ifdef __cplusplus
extern "C"
{
#endif

void networkLoop(void)
{
START:

    if(!exitThread[THREAD_NETWORK])
    {
    	goto START;
    }
}

#ifdef __cplusplus
}
#endif

#endif