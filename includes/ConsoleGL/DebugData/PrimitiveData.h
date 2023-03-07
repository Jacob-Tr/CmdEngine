#ifndef PRIMITIVE_DATA_H
#define PRIMITIVE_DATA_H

#define PRIMITIVE_MACROS 6
char* primitive_macros[PRIMITIVE_MACROS] =
{
	"PRIMITIVES_H\0",
	"NULL_PIXEL\0",
	"NULL_POINT\0",
	"NULL_LINE\0",
	"empty_point\0",
	"empty_line(line* ln)\0"
};

char* prinitive_macro_defs[PRIMITIVE_MACROS] =
{
	"NO-EXPSN\0",
	"((pixel*) NULL\0",
	"((point*) NULL\0",
	"((line*) NULL\0",
	"newPointS(' ', 0)\0",
	"initLine((ln), empty_point, empty_point)\0"
};

#define PRIMITIVE_TYPES 4
char* primitive_types[PRIMITIVE_TYPES] =
{
	"vector3\0",
	"pixel\0",
	"point\0",
	"line\0"
};

#define PRIMITIVE_FUNCS 20
char* primitive_functions[PRIMITIVE_FUNCS] =
{
	"getPointSize\0",
	"setPointSize\0",
	"getLineWidth\0", 
	"setLineWidth\0",
	"getVectTotal\0",
	"getVectDifference\0",
	"initPixel\0",
	"isEmptyPixel\0",
	"getPixelChar\0",
	"setPixelChar\0", 
	"getPointPixelPtr\0",
	"getPointPixel\0",
	"setPointPixel\0",
	"newPointS\0", 
	"newPoint\0",
	"isEmptyPoint\0",
	"removePointPixel\0",
	"destroyPoint\0",
	"initLine\0",
	"destroyLine\0"
};

char* primitive_func_details[PRIMITIVE_FUNCS] =
{
	"size_t (void)\0",
	"void (const size_t size)\0",
	"size_t (void)\0",
	"void (const size_t width)\0",
	"size_t (const vector3 vect)\0",
	"size_t (const vector3 a, const vector3 b)\0",
	"void (pixel* px, const vector3 vect, const char c)\0",
	"bool (const pixel px)\0",
	"char (const pixel px)\0",
	"void (pixel* px, const char c)\0",
	"pixel* (point pt, const size_t x, const size_t y)\0",
	"pixel (point pt, const size_t x, const size_t y)\0",
	"void (point pt, const size_t x, const size_t y, const char c)\0",
	"point (const char c, const size_t size)\0",
	"point (const char c)\0",
	"bool (const point pt)\0",
	"void (point pt, const size_t x, const size_t y)\0",
	"void (point pt)\0",
	"void (line* ln, const point a, const point b)\0",
	"void (line* ln)\0"
};

char* primitive_func_descs[PRIMITIVE_FUNCS] =
{
	"Get the current 'point' drawing width/height.\0",
	"Set the current 'point'drawing width/height.\0",
	"Get the current 'line' drawing width.\0",
	"Set the current 'line' drawing width.\0",
	"Get total size of 'vector3' coordinates.\0",
	"Get total difference between two 'vector3' coordinate sizes.\0",
	"Initialize a 'pixel's coordinates and char.\0",
	"Check if a 'pixel's char field is whitespace.\0",
	"Get the 'char' field of a 'pixel'.\0",
	"Set the 'char' field of a 'pixel'.\0",
	"Get the memory address of a 'pixel' within a 'point'.\0",
	"Get the value of a 'pixel' within a 'point'.\0",
	"Set the value of a 'pixel' within a 'point'.\0",
	"Create a new 'point' with specified size.\0",
	"Create a new 'point' using size set VIA \"setPointSize\".\0",
	"Check if a 'point's width/height is 0.\0",
	"Set a 'pixel' in a 'point' to whitespace.\0",
	"Set a point to NULL.\0",
	"Initialize a 'line'.\0",
	"Set both 'line' 'point' fields to NULL and replace the referenced line with an empty line.\0"
};

#ifdef _cplusplus
extern "C"
{
#endif

bool findPrimFuncID(const char* func_name, size_t* id, const size_t length)
{
	for(size_t i = 0; i < PRIMITIVE_FUNCS; i++)
	{
		if(strMatch(func_name, primitive_functions[i], length))
		{
			*id = i;
			return true;
		}
	}
	
	return false;
}

#ifdef _cplusplus
}
#endif

#endif