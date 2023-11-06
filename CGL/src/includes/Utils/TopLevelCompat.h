#ifndef TOP_LEVEL_COMPAT_H
#define TOP_LEVEL_COMPAT_H

// Standard Library Headers
#include "includes/Utils/Compat/StdlibInc.h"

// Simple DirectMedia Layer [https://www.libsdl.org/]
#include "includes/Utils/Compat/SDLInc.h"

// Useful mathematical functions.
#include "includes/Utils/Numbers.h"

// Repeat any process a specified number of times.
#define repeat(iterations) for(size_t _current_macro_i_ = 0; _current_macro_i_ < (iterations); _current_macro_i_++)

/*
*	For Debugging purposes. 
*   FORCE_INLINE macro in place of compiler specific methods of forcing inlining.
*	CURRENT_THREAD macro in place of OS specific functionality of threads.
*	FRAME_WAIT macro in place of OS specific functionality of threads.
*	sleep() macro on windows to match the syntax of GCC functionality.
*/
#ifdef _WIN32
    #define FORCE_INLINE __forceinline
    #define CURRENT_THREAD GetCurrentThread()
	#define FRAME_WAIT Sleep(((int32_t) floor(1000.0F / ((float) fr_pr_sec))))
	#define sleep(sec) Sleep(((int32_t) (sec)) * 1000)
#elif defined __GNUC__
    #define FORCE_INLINE __attribute__((always_inline)) inline
    #define CURRENT_THREAD pthread_self
	#define FRAME_WAIT usleep(((int_64) floor(1000000.0F / ((float) fr_pr_sec))))
#endif

static vector2 screen_bounds = Vect2(60, 25);

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl setWindowBounds(const vector2 vect) {screen_bounds = vect;}
vector2 __cdecl getWindowBounds(void) {return screen_bounds;}

#ifdef __cplusplus
}
#endif

#endif