#ifndef POINT_UTILS_H
#define POINT_UTILS_H

size_t point_size = 1;

#ifdef __cplusplus
extern "C"
{
#endif

size_t getPointSize(void) {return point_size;}

void setPointSize(const size_t size) {point_size = size;}

/*pixel* getPointPixelPtr(point pt, const size_t x, const size_t y) {return (pt.px + (y * pt.width) + x);}

pixel getPointPixel(point pt, const size_t x, const size_t y) {return *(getPointPixelPtr(pt, x, y));}

void setPointPixel(point pt, const pixel new_px, const size_t x, const size_t y) {*(getPointPixelPtr(pt, x, y)) = new_px;}*/

void initPointS(point* pt, const char c, const vector3 vect, const size_t size)
{
	pt->size.x = size;
	pt->size.z = size;
	
	pt->vect = vect;
	
	pixel p;
	initPixel(&p, c);
	
	pt->px = p;
}

FORCE_INLINE void initPoint(point* pt, const char c, const vector3 vect) {initPointS(pt, c, vect, point_size);}

bool isEmptyPoint(const point pt) {return (pt.size.x == 0);}

void destroyPoint(point pt) 
{
	pt.size.x = 0;
	pt.size.z = 0;
}

void setPointPixel(point* pt, const pixel px) {pt->px = px;}

void setPointCoords(point* pt, const vector3 vect) {pt->vect = vect;}

vector3 getPointCoords(const point pt) {return pt.vect;}

size_t getPointX(const point pt) {return getPointCoords(pt).x;}
size_t getPointY(const point pt) {return getPointCoords(pt).y;}
size_t getPointZ(const point pt) {return getPointCoords(pt).z;}

#ifdef _cplusplus
}
#endif

#endif