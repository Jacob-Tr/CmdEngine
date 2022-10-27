#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define NULL_PIXEL ((pixel*) NULL)
typedef struct
{
	size_t x, y, z;
	char c;
} pixel;

#define NULL_POINT ((point*) NULL)
typedef struct
{
	pixel* px;
	size_t width, height;
} point;

#define NULL_LINE ((line*) NULL)
typedef struct
{
	point a, b;
	char c;
} line;

size_t point_size = 1, line_width = 1;

#ifdef __cplusplus
extern "C"
{
#endif

size_t getPointSize(void) {return point_size;}

void setPointSize(const size_t size) {point_size = size;}

size_t getLineWidth(void) {return line_width;}

void setLineWidth(const size_t size) {line_width = size;}

void initPixel(pixel* px, const size_t x, const size_t y, const size_t z, const char c)
{
	px->x = x;
	px->y = y;
	px->z = z;
	
	px->c = c;
}

char getPixelChar(const pixel px) {return px.c;}

void setPixelChar(pixel* px, const char c) {px->c = c;}

pixel* getPointPixelPtr(point pt, const size_t x, const size_t y) {return (pt.px + (y * pt.width) + x);}

pixel getPointPixel(point pt, const size_t x, const size_t y) {return *(getPointPixelPtr(pt, x, y));}

void setPointPixel(point pt, const pixel new_px, const size_t x, const size_t y) {*(getPointPixelPtr(pt, x, y)) = new_px;}

point newPointS(const char c, const size_t size)
{
	point pt;
	
	pt.width = size;
	pt.height = size;
	
	size_t pixel_buf_size = (pt.width * pt.height);
	
	pt.px = (pixel*) malloc(sizeof(pixel) * pixel_buf_size);
	
	for(size_t i = (pt.height - 1); i < (pt.height); i--) 
	{
		for(size_t ii = 0; ii < pt.width; ii++)
		{
			pixel px;
			initPixel(&px, ii, i, 0, c);
			setPointPixel(pt, px, ii, i);
		}
	}
	
	return pt;
}

#define empty_point newPointS(' ', 0)
point newPoint(const char c) {return newPointS(c, point_size);}

void removePointPixel(point pt, const size_t x, const size_t y) 
{
	pixel px;
	initPixel(&px, x, y, 0, ' ');
	setPointPixel(pt, px, x, y);
}

void destroyPoint(point pt) 
{
	pt.width = 0;
	pt.height = 0;
	
	pt.px = (pixel*) realloc(pt.px, 0);
}

#define empty_line(ln) initLine((ln), empty_point, empty_point)
void initLine(line* ln, const point a, const point b)
{
	ln->a = a;
	ln->b = b;
}

void destroyLine(line* ln)
{
	destroyPoint(ln->a);
	destroyPoint(ln->b);
	
	empty_line(ln);
}

#ifdef __cplusplus
}
#endif

#endif
