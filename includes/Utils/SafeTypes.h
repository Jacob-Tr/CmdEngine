#ifndef CRSS_TYPE_H
#define CRSS_TYPE_H

#ifndef __PTR_SIZE__
    #error "__PTR_SIZE__ not defined."
#endif

#if (__PTR_SIZE__ == 1)
    #define __8BIT__
#elif (__PTR_SIZE__ == 2)
    #define __16BIT__
#elif (__PTR_SIZE__ == 4)
    #define __32BIT__
#elif (__PTR_SIZE__ == 8)
    #define __64BIT__
#endif

#if _MSC_VER
    typedef int8_t byte;
#else
    typedef int8_t byte;
#endif

typedef uint8_t ubyte;

#ifndef __8BIT__
    typedef ubyte uint_8_t;
    typedef byte int_8_t;
#endif

#ifdef SHORT_TYPE_NAMES
    #if defined __32BIT__ || defined __64BIT__
        typedef uint64_t uint_64;
        typedef int64_t int_64;
    #endif
    #if defined __16BIT__ || defined __32BIT__ || defined __64BIT__
        typedef uint32_t uint_32;
        typedef int32_t int_32;
    #endif
    typedef uint16_t uint_16;
    typedef int16_t int_16;
    typedef ubyte uint_8;
    #ifdef _MSC_VER
        typedef __int8 int_8;
    #else
        typedef int8_t int_8;
    #endif
#endif

#ifdef __cplusplus
    #define BOOL bool

extern "C"
{
#else
    #define true ((uint8_t) 1)
    #define false ((uint8_t) 0)
    
    /* bool type included with SDL_gpu.h */
    //typedef uint8_t bool;
#endif

static inline bool isBigEdian()
{
    uint32_t a = (UINT_MAX / 2), b = (a << 1);
    
    return (b > a);
}

#ifdef __cplusplus
}
#endif

#endif