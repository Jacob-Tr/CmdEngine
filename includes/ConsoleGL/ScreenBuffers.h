#ifndef BUFFERS_H
#define BUFFERS_H

#ifndef MAX_X
    #define MAX_X 60
#endif
#ifndef MAX_Y
    #define MAX_Y 50
#endif

#define NULL_SCREEN ((screen_buffer*) NULL)
typedef struct 
{
	pixel* buffer;
	size_t buf_x_size, buf_y_size;
} screen_buffer;

screen_buffer* main_screen_buf = NULL_SCREEN;

#ifdef __cplusplus
extern "C"
{
#endif

screen_buffer* getMainBuffer(void) {return main_screen_buf;}

void setMainBuffer(screen_buffer* buf) {main_screen_buf = buf;}

void updateMainBuffer(screen_buffer* old_buffer, screen_buffer* new_buffer)
{
	screen_buffer* temp = getMainBuffer();
	setMainBuffer(new_buffer);
	old_buffer = temp;
}

pixel* getScreenBufPixelPtr(const screen_buffer* buf, const size_t x, const size_t y) {return (buf->buffer + ((buf->buf_x_size * buf->buf_y_size) + x));}

pixel getScreenBufPixel(const screen_buffer* buf, const size_t x, const size_t y) {return *(getScreenBufPixelPtr(buf, x, y));}

void setScreenBufPixel(const screen_buffer* buf, const pixel px, const size_t x, const size_t y) {*(getScreenBufPixelPtr(buf, x, y)) = px;}

void initScreenPxBuffer(screen_buffer* buf) 
{
	size_t i, ii;
	char c = '\0';
	for (i = 0; i < buf->buf_y_size; i++) 
	{
		for (ii = 0; ii < buf->buf_x_size; ii++) 
		{
			if(ii == (buf->buf_x_size - 1)) c = '\n';
			else c = ' ';
			
			pixel px;
			initPixel(&px, ii, i, 0, c);
			setScreenBufPixel(buf, px, ii, i);
		}
	}
}

#define INIT_SCREEN setMainBuffer((screen_buffer*) malloc(sizeof(screen_buffer)));initBuffer(getMainBuffer(), MAX_X, MAX_Y)
void initBuffer(screen_buffer* buf, const size_t x_size, const size_t y_size)
{
	buf->buf_x_size = x_size;
	buf->buf_y_size = y_size;
	
	const size_t size = (x_size * y_size);
	buf->buffer = (pixel*) malloc(sizeof(char) * size);
	
	initScreenPxBuffer(buf);
}

void addPointToScrnBuf(screen_buffer* buf, const point pt, const size_t x, const size_t y)
{
	for(size_t i = y; i < (y + pt.height); i++)
	{
		for(size_t ii = x; ii < (x + pt.width); ii++)
		{
			setScreenBufPixel(buf, getPointPixel(pt, (ii - x), (i -y)), ii, i);
		}
	}
}

static inline void clrScr(void) {system("clear");}

void prtScr(void) 
{
	//clrScr();
	size_t i, ii;
	char c = '\0';
	pixel px;
	for(i = 0; i < main_screen_buf->buf_y_size; i++)
	{
		for(ii = 0; ii < main_screen_buf->buf_x_size; ii++) 
		{
			px = getScreenBufPixel(main_screen_buf, ii, i);
			c = getPixelChar(px);
			
			//if(c == 'y') printf("Printing pixel %zu-%zu at address %p with value %c\n", ii, i, getScreenBufPixelPtr(main_screen_buf, ii, i), c);
			
			fprintf(stdout, "%c", c);
		}
	}
}

#ifdef __cplusplus
}
#endif

#endif