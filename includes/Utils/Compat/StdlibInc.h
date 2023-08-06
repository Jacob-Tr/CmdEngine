#ifndef STDLIB_INC_H
#define STDLIB_INC_H

#ifdef __cplusplus
    #include <cstdio>
    #include <cstdlib>
    #include <cstdint>
    #include <climits>
    #include <cmath>
    #include <cfloat>
    #include <csignal>
#else
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <limits.h>
    #include <math.h>
    #include <float.h>
    #include <signal.h>
#endif

#ifdef __GNUC__
    #ifdef _cplusplus
        #include <cunistd>
        #include <ctermio>
        #include <csocket>
    #else
        #include <unistd.h>
        #include <termio.h>
        #include <sys/socket.h>
    #endif
#elif defined _WIN32
    #define WIN32_LEAN_AND_MEAN

    #ifdef _cplusplus
        #include <cwindows>
        #include <cprocessthreadsapi>
        #include <cwinsock2>
    #else
        #include <windows.h>
        #include <processthreadsapi.h>
        #include <winsock2.h>
    #endif
#endif

#endif