#ifndef BUFFERS_H
#define BUFFERS_H

#ifdef SCREEN_MAX_X && defined SCREEN_MAX_Z
    static int_16 MAX_X = SCREEN_MAX_X, MAX_Z = SCREEN_MAX_Z;
 #else
     #error "SCREEN_MAX_X and/or SCREEN_MAX_Z macro are not defined."
#endif

screen_buffer* main_screen_buf = NULL_SCREEN;

#ifdef __cplusplus
extern "C"
{
#endif

static void resizeScreenX(const int_16 val) {MAX_X = val;}

static void resizeScreenZ(const int_16 val) {MAX_Z = val;}

static void resizeScreen(const int_16 x, const int_16 z)
{
	resizeScreenX(x);
	resizeScreenZ(z);
} 

screen_buffer* getMainBuffer(void) {return main_screen_buf;}

bool setMainBuffer(screen_buffer* buf) 
{
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

void updateMainBuffer(screen_buffer* old_buffer, screen_buffer* new_buffer)
{
	screen_buffer* temp = getMainBuffer();
	setMainBuffer(new_buffer);
	old_buffer = temp;
}

pixel* getScreenBufPixelPtr(const screen_buffer* buf, const size_t x, const size_t z) {return (pixel*) (buf->buffer + ((z * buf->size.x) + x));}

pixel getScreenBufPixel(const screen_buffer* buf, const size_t x, const size_t z) {return *(getScreenBufPixelPtr(buf, x, z));}

void setScreenBufPixel(const screen_buffer* buf, const pixel px, const size_t x, const size_t z) {*(getScreenBufPixelPtr(buf, x, z)) = px;}

static inline void initScreenPxBuffer(screen_buffer* buf) 
{
	char c = '\0';
	pixel px;
	
	memset(buf->buffer, ' ', ((buf->size.x * buf->size.z) - (buf->size.x + 1)));
	
	initPixel(&px, '\n');
	for(size_t i = 0; i < buf->size.z; i++) setScreenBufPixel(buf, px, (buf->size.x), i);
}

void initBuffer(screen_buffer* buf, const size_t x_size, const size_t z_size)
{
	buf->size.x = x_size;
	buf->size.z = z_size;
	
	const size_t size = (x_size * z_size);
	buf->buffer = (pixel*) malloc(sizeof(pixel) * size);
	
	initScreenPxBuffer(buf);
}

bool initScreen(void)
{
	if(getMainBuffer() != NULL_SCREEN)
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
	
	initBuffer(getMainBuffer(), MAX_X, MAX_Z);
	
	return true;
}

void destroyScreenBuffer(screen_buffer* buf)
{
	free(buf->buffer);
	free(buf);
}

static inline void clrScr(void) 
{
	#ifndef _WIN32
		printf("\x1b[2J\x1b[H");
	#else
		system("cls");
	#endif
	fflush(stdout);
}

void prtScr(void) 
{
	clrScr();
	
	for(size_t i = 0; i < main_screen_buf->size.z; i++) for(size_t ii = 0; ii < main_screen_buf->size.x; ii++) fprintf(stdout, "%c", getPixelChar(getScreenBufPixel(main_screen_buf, ii, i)));
}

#ifdef __cplusplus
}
#endif

#endif