#ifndef STDLIB_INC_H
#define STDLIB_INC_H

#ifdef _cplusplus
    #include <cstdio>
    #include <cstdlib>
    #include <climits>
    #include <cmath>
    #include <cfloat>
    #include <ctermio>
    #include <csignal>
#else
    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
    #include <math.h>
    #include <float.h>
    #include <signal.h>
#endif

#ifndef _MSC_VER
    #ifdef _cplusplus
        #include <cunistd>
        #include <ctermio>
    #else
        #include <unistd.h>
        #include <termio.h>
    #endif
#else
    #ifdef _cplusplus
        #include <cwindows>
        #include <cprocessthreadsapi>
    #else
        #include <windows.h>
        #include <processthreadsapi.h>
    #endif
#endif

#endif