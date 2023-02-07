#ifndef CONFIG_H
#define CONFIG_H

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

static size_t fps = 0, screen_x = 0, screen_y = 0;

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



#ifdef _cplusplus
}
#endif

#endif