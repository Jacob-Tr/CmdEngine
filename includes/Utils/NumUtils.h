#ifndef NUM_UTILS_H
#define NUM_UTILS_H

#include <math.h>

#ifdef _cplusplus
extern "C"
{
#endif

static inline double doubleAbs(const double val) {return ((val < 0) ? (val * ((double) -1.0)) : val);}

static inline float floatAbs(const float val) {return ((float) doubleAbs((double) val));}

static inline int_64 longAbs(const int_64 val) {return ((val < 0) ? val * -1 : val);}

static inline int_32 intAbs(const int_32 val) {return ((int_32) longAbs((int_64) val));}

static inline double doubleDifference(const double a, const double b) {return ((a < 0 && b > 0) ? (doubleAbs(a) + b) : ((a > 0 && b < 0) ? (doubleAbs(b) + a) : ((doubleAbs(a) > doubleAbs(b)) ? (doubleAbs(a) + b) : (doubleAbs(b) + a))));}

static inline float floatDifference(const float a, const float b) {return ((float) doubleDifference((double) a, (double) b));}

static inline size_t sizeDifference(const size_t a, const size_t b) {return ((a > b) ? (a - b) : (b - a));}

static inline int_64 longDifference(const int_64 a, const int_64 b) {return ((a < 0 && b > 0) ? (longAbs(a) + b) : ((a > 0 && b < 0) ? (longAbs(b) + a) : ((longAbs(a) > longAbs(b)) ? (longAbs(a) + b) : (longAbs(b) + a))));}

static inline int_32 intDifference(const int_32 a, const int_32 b) {return ((int_32) longDifference((int_64) a, (int_64) b));}

static inline int_64 longExp(int_64 val, const size_t power) 
{
	int_64 ret = val;
	for(size_t i = 0; i < power; i++) ret *= val;
	
	return ret;
}

#ifdef _cplusplus
}
#endif

#endif