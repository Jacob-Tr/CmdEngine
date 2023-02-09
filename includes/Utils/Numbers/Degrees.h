#ifndef DEGREES_H
#define DEGREES_H

#ifdef _cplusplus
extern "C"
{
#endif

static inline float sanitizeDegrees(const float degs)
{
	float ret = degs;
	if(ret < 0) return sanitizeDegrees((359.99F - (float) fabs(ret)));
	
	if(ret > 359.99F) return sanitizeDegrees(floatDifference(ret, 359.99F));
	
	return ret;
}

#ifdef _cplusplus
}
#endif

#endif