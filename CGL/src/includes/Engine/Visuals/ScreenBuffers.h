#ifndef BUFFERS_H
#define BUFFERS_H

/*
	Structure which is used to hold data meant to be displayed in a window.
*/
typedef struct 
{
	texture* buffer;
	vector2 bounds;
	size_t textures;
} screen_buffer;

static screen_buffer* main_screen_buf = ((screen_buffer*) NULL);

#ifdef __cplusplus
extern "C"
{
#endif

/*
	Get and set the ptr to the next screen buffer to be displayed to the client.
*/
screen_buffer* getMainBuffer(void) {return main_screen_buf;}
bool setMainBuffer(screen_buffer* buf) 
{
	// Cannot set main buffer ptr to NULL.
	if(buf == ((screen_buffer*) NULL))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Cannot set main buffer pointer to NULL.\n");
		#endif
		
		return false;
	}
	
	main_screen_buf = buf;
	
	return true;
}

/*
	Swap the current buffer with a new one.
*/
void updateMainBuffer(screen_buffer* old_buffer, screen_buffer* new_buffer)
{
	screen_buffer* temp = getMainBuffer();
	setMainBuffer(new_buffer);
	old_buffer = temp;
}

/*
	Get the memory address of a specific pixel by it's coordinates.
*/
texture* getScreenBufTexturePtr(const screen_buffer buf, const size_t id) {return (texture*) (buf.buffer + id);}

/*
	Get and set the value of a pixel by it's coordinates.
*/
texture getScreenBufTexture(const screen_buffer buf, const size_t id) {return *(getScreenBufTexturePtr(buf, id));}
void setScreenBufTexture(const screen_buffer buf, const texture tx, const size_t id) {*(getScreenBufTexturePtr(buf, id)) = tx;}

/*
	Initialize the screen buffer pixel buffer to the size of the screen.
*/
void initBuffer(screen_buffer* buf, const vector2 bounds)
{
	buf->bounds.x = bounds.x;
	buf->bounds.z = bounds.z;
	
	const size_t size = vector2Total(buf->bounds);
	buf->buffer = (texture*) malloc(sizeof(texture) * size);
}

bool initScreen(void)
{
	if(getMainBuffer() != ((screen_buffer*) NULL))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Reinitialization of main screen buffer without free.\n");
		#endif
	}
	
	if(!setMainBuffer((screen_buffer*) malloc(sizeof(screen_buffer))))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Setting main buffer failed.\n");
		#endif
		
		return false;
	}
	
	initBuffer(getMainBuffer(), (vector2) Vect2(screen_bounds.x, screen_bounds.z));
	
	return true;
}


/*
	Properly destroy a screen_buffer pointer and it's buffer.
*/
void destroyScreenBuffer(screen_buffer** buf)
{
	screen_buffer* ptr = *buf;
	
	if(ptr == ((screen_buffer*) NULL)) // Double free
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Attemoted to destroy null screen buffer.\n");
		#endif
		
		return;
	}
	
	free(ptr->buffer);
	free(ptr);
	
	*buf = ((screen_buffer*) NULL);
}

static inline void clrScr() 
{
		// Ensure everything is printed
	/*fflush(stdout);
	fflush(stderr);
	
	#ifndef NO_CLR_SCREEN
		#ifndef _WIN32
			printf("\x1b[2J\x1b[H"); // ?
		#else
			system("cls"); // Batch cmd
		#endif
	#endif*/

	#ifndef NO_CLR_SCREEN
		
	#endif
}

void prtScr(void) 
{
	/*clrScr();
	#ifndef NO_SCREEN_PRINT
		for(size_t i = 0; i < main_screen_buf->size.z; i++) for(size_t ii = 0; ii < main_screen_buf->size.x; ii++) 
		{
			fprintf(stdout, "%c", getPixelChar(getScreenBufPixel(main_screen_buf, Vect2(ii, i))));

			//SDL_
		}
	#endif
	*/

	#ifndef NO_SCREEN_PRINT
		
	#endif
}

#ifdef __cplusplus
}
#endif

#endif