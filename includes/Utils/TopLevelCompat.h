#ifndef TOP_LEVEL_COMPAT_H
#define TOP_LEVEL_COMPAT_H

#include "includes/Utils/Compat/StdlibInc.h"

#ifdef _MSC_VER
    #define FORCE_INLINE static __forceinline
    #define CURRENT_THREAD GetCurrentThread()
#else
    #define FORCE_INLINE static __attribute__((always_inline)) inline
    #define CURRENT_THREAD pthread_self
#endif

#define MAX_THREADS 64

enum THREAD_STATES
{
	EXECUTING,
	PAUSED,
	FINISHED
};

#endif