#ifndef NUM_UTILS_H
#define NUM_UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

static inline double doubleAbs(const double val) {return ((val < 0) ? (val * ((double) -1.0)) : val);}
static inline float floatAbs(const float val) {return ((float) doubleAbs((double) val));}
static inline int64_t longAbs(const int64_t val) {return ((val < 0) ? val * -1 : val);}

static inline double doubleDifference(const double a, const double b) {return doubleAbs(a - b);}
static inline float floatDifference(const float a, const float b) {return ((float) doubleDifference((double) a, (double) b));}
static inline size_t ulongDifference(const uint64_t a, const uint64_t b) {return ((a > b) ? (a - b) : (b - a));}
static inline size_t longDifference(const int64_t a, const int64_t b) {return longAbs(a - b);}

/*static inline int64_t expl(const int64_t val, const int64_t power) 
{
	int64_t ret = val;
	repeat(power) ret *= val;
	
	return ret;
}

static inline uint64_t expul(const uint64_t val, const uint64_t power)
{
	uint64_t ret = val;
	repeat(power) ret *= val;
	
	return ret;
}

static inline int32_t expi(const int32_t val, int32_t power)
{
	int32_t ret = val;
	repeat(power) ret *= val;
	
	return ret;
}

static inline uint32_t expui(const uint32_t val, const uint32_t power)
{
	uint32_t ret = val;
	repeat(power) ret *= val;
	
	return ret;
}*/
	


#ifdef __cplusplus
}
#endif

#endif