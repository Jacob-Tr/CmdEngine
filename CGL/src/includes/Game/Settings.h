#ifndef SETTINGS_H
#define SETTINGS_H

#define MAX_FPS 300

static size_t fr_pr_sec = 15;

#ifdef _cplusplus
extern "C"
{
#endif

void setFPS(const size_t val) 
{
	if(val > MAX_FPS) 
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Attempted to set FPS to %zu. Overridden to FPS_MAX [%d].\n", val, MAX_FPS);
		#endif
	    fr_pr_sec = MAX_FPS;
	}
	else fr_pr_sec = val;
}
size_t getFPS(void) {return fr_pr_sec;}

#ifdef __cplusplus
}
#endif

#endif