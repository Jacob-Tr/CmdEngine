#ifndef TOP_LEVEL_COMPAT_H
#define TOP_LEVEL_COMPAT_H

#include "includes/Utils/Compat/StdlibInc.h"

#ifdef _MSC_VER
    #define FORCE_INLINE static __forceinline
    #define CURRENT_THREAD GetCurrentThread()
	#define FRAME_WAIT Sleep(((int_32) floor(1000.0F / ((float) fr_pr_sec))))
	#define sleep(sec) Sleep(((int_32) (sec)) * 1000)
#else
    #define FORCE_INLINE static __attribute__((always_inline)) inline
    #define CURRENT_THREAD pthread_self
	#define FRAME_WAIT usleep(((int_64) floor(1000000.0F / ((float) fr_pr_sec))))
#endif

#define MAX_THREADS 64

enum THREAD_STATES
{
	EXECUTING,
	PAUSED,
	FINISHED
};

#endif