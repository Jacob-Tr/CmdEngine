#ifndef DISPLAY_H
#define DISPLAY_H

#ifndef MAX_FPS
    #define MAX_FPS 300
#elif (MAX_FPS > USHRT_MAX)
    #define MAX_FPS USHRT_MAX
#endif

static uint_16 fr_pr_sec = 15;

#ifdef _MSC_VER
	#define FRAME_WAIT Sleep(((int_32) floor(1000.0F / ((float) fr_pr_sec))))
#else
	#define FRAME_WAIT usleep(((int_64) floor(1000000.0F / ((float) fr_pr_sec))))
#endif

#ifdef _cplusplus
extern "C"
{
#endif

void setFPS(const uint_16 val) 
{
	if(val > MAX_FPS) 
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Attempted to set FPS to %d. Overridden to FPS_MAX [%d].\n", val, MAX_FPS);
		#endif
	    fr_pr_sec = MAX_FPS;
	}
	else fr_pr_sec = val;
}

uint_16 getFPS(void) {return fr_pr_sec;}

#ifdef _cplusplus
}
#endif

#include "includes/Engine/Display/Physics.h"
#include "includes/Engine/Display/Render.h"
#include "includes/Engine/Display/ChatBox.h"

#endif