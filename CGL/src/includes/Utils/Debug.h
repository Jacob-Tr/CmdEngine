#ifdef DEBUG

#ifndef DEBUG_H
#define DEBUG_H

#include "includes/Utils/Debug/MemoryDebug.h"

#ifdef __NO_SCREEN_PRINT__
    static bool __print_screen__ = false;
#else
    static bool __print_screen__ = true;
#endif

#define printSDLError(stream) fprintf((stream), "SDL Error: <%s>.\n", SDL_GetError())

#ifdef _cplusplus
extern "C"
{
#endif

FORCE_INLINE void setScreenPrint(const bool value) {__print_screen__ = value;}

FORCE_INLINE bool getScreenPrint(void) {return __print_screen__;}

#ifdef _cplusplus
}
#endif

#endif

#endif