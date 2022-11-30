#ifndef BUFFERS_H
#define BUFFERS_H

#ifndef MAX_X
    #define MAX_X 60
#endif
#ifndef MAX_Z
    #define MAX_Z 50
#endif

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

pixel* getScreenBufPixelPtr(const screen_buffer* buf, const size_t x, const size_t z) {return (pixel*) (buf->buffer + ((z * buf->buf_x_size) + x));}

pixel getScreenBufPixel(const screen_buffer* buf, const size_t x, const size_t z) {return *(getScreenBufPixelPtr(buf, x, z));}

void setScreenBufPixel(const screen_buffer* buf, const pixel px, const size_t x, const size_t z) {*(getScreenBufPixelPtr(buf, x, z)) = px;}

void initScreenPxBuffer(screen_buffer* buf) 
{
	char c = '\0';
	pixel px;
	for(size_t i = 0; i < buf->buf_z_size; i++) 
	{
		for(size_t ii = 0; ii < buf->buf_x_size; ii++) 
		{
			initPixel(&px, ((ii % buf->buf_x_size - 1) == 1) ? '\n' : ' ');
			setScreenBufPixel(buf, px, ii, i);
		}
	}
}

#define INIT_SCREEN setMainBuffer((screen_buffer*) malloc(sizeof(screen_buffer)));initBuffer(getMainBuffer(), MAX_X, MAX_Z)
void initBuffer(screen_buffer* buf, const size_t x_size, const size_t z_size)
{
	buf->buf_x_size = x_size;
	buf->buf_z_size = z_size;
	
	const size_t size = (x_size * z_size);
	buf->buffer = (pixel*) malloc(sizeof(pixel) * size);
	
	initScreenPxBuffer(buf);
}

static inline void clrScr(void) {system("clear");}

void prtScr(void) 
{
	clrScr();
	
	for(size_t i = 0; i < main_screen_buf->buf_z_size; i++) for(size_t ii = 0; ii < main_screen_buf->buf_x_size; ii++) fprintf(stdout, "%c", getPixelChar(getScreenBufPixel(main_screen_buf, ii, i)));
}

#ifdef __cplusplus
}
#endif

#endif