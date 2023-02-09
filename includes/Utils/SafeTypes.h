#ifndef CRSS_TYPE_H
#define CRSS_TYPE_H

#include <inttypes.h>
#include <limits.h>

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
    #define int8_t byte
#else
    typedef int8_t byte;
#endif

typedef uint8_t ubyte;

/*#ifdef __64BIT__
    typedef unsigned long long uint_128_t;
    typedef long long int_128_t;
    typedef unsigned long uint_64_t;
    typedef long int_64_t;
#endif
#ifdef __32BIT__
    typedef unsigned long long uint_64_t;
    typedef long long int_64_t;
#endif
#if defined __64BIT__ || defined __32BIT__
    typedef unsigned int uint_32_t;
    typedef int int_32_t;
    typedef unsigned short uint_16_t;
    typedef short int_16_t;
#elif defined __16BIT__
    typedef unsigned long long uint_32_t;
    typedef long long int_32_t;
    typedef unsigned int uint_16_t;
    typedef int int_16_t;
#elif defined __8BIT__
    typedef unsigned long long uint_16_t;
    typedef long long int_16_t;
    typedef unsigned int uint_8_t;
    typedef int int_8_t;
#endif

#ifndef __8BIT__
    typedef ubyte uint_8_t;
    typedef byte int_8_t;
#endif*/

#ifdef SHORT_TYPE_NAMES
    /*#ifdef __64BIT__
        typedef uint128_t uint_128;
        typedef int128_t int_128;
    #endif*/
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

/*#if (CHAR_MAX == 127)
    #define schar char
    #define char uchar
#endif*/

#ifdef __cplusplus
extern "C"
{
#else
    #define true ((uint8_t) 1)
    #define false ((uint8_t) 0)
    
    typedef uint8_t bool;
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