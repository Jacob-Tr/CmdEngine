#ifndef CONFIG_H
#define CONFIG_H

#ifndef MAX_FPS
    #define MAX_FPS 300
#elif (MAX_FPS > USHRT_MAX)
    #define MAX_FPS USHRT_MAX
#endif

enum config_files
{
	DISPLAY,
	CONF_NULL
};

static const char* conf_file_names[] =
{
	"Display"
};

static char* conf_paths[CONF_NULL];
static file* files[CONF_NULL];

enum display_settings
{
	SCREEN_X,
	SCREEN_Z,
	FPS,
	DSPLY_NULL
};

static const char* disp_setting_ident[] =
{
	"Screen-x",
	"Screen-z",
	"Fps"
};


#define empty_screen_obj {BLANK_PIXEL, BLANK_PIXEL, BLANK_PIXEL}
typedef struct
{
	pixel x, y, z;
} screen_obj;

static size_t screen_x = 0, screen_y = 0, fr_pr_sec = 15;

#ifdef _cplusplus
extern "C"
{
#endif

bool initConfig(void)
{
	return true;
	for(size_t i = 0; i < CONF_NULL; i++) conf_paths[i] = (char*) calloc(MAX_FILE_PATH, sizeof(char));
	
	snprintf(conf_paths[DISPLAY], MAX_FILE_PATH, "");
	if((files[DISPLAY] = File(conf_file_names[DISPLAY], conf_paths[DISPLAY], FILE_DATA)) == NULL)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Unable to initialize display config file.\n");
		#endif
		    
		return false;
	}
	
	size_t display_len = files[DISPLAY]->length;
	
	return true;
}

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

#ifdef _cplusplus
}
#endif

#endif