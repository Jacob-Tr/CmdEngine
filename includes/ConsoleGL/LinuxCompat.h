#ifndef LINUX_COMPAT_H
#define LINUX_COMPAT_H

#ifdef _MSC_VER
    #define FORCE_INLINE static __forceinline
#else
    #define FORCE_INLINE static __attribute__((always_inline)) inline
#endif

#ifdef _cplusplus
extern "C"
{
#endif

#if defined _MSC_VER || defined _WIN32
	static inline void clrScr(void) {system("cls");}
#else
	static inline void clrScr(void) {system("clear");}
#endif

FORCE_INLINE void* betterMalloc(const size_t size)
{
	if(size == 0) return NULL;
	return malloc(size);
}

FORCE_INLINE void* betterCalloc(const size_t element_size, const size_t len)
{
	if((element_size * len) == 0) return NULL;
	return calloc(element_size, len);
}

FORCE_INLINE void* betterRealloc(void* base, size_t size)
{
	if(size == 0)
	{
		free(base);
		return NULL;
	}
	
	return realloc(base, size);
}

#ifdef _cplusplus
}
#endif

#define malloc betterMalloc
#define calloc betterCalloc
#define realloc betterRealloc

#endif