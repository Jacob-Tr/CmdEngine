#ifndef ALLOCCOMPAT_H
#define ALLOCCOMPAT_H

#ifdef _cplusplus
extern "C"
{
#endif

FORCE_INLINE void* betterAlloc(const size_t size)
{
	if(size == 0) return NULL;
	
	void* ptr = alloca(size);
	
	#ifdef DEBUG
	    alloc_type type = ALLOCA;
	
	    size_t index = addPtrToTrckr(type, ptr, size);
	    
	    if(getPrintAlloc(type)) printAllocMsg(type, *(getPtrTrckr(type, index)));
	#endif
	
	return ptr;
}

FORCE_INLINE void* betterMalloc(const size_t size)
{
	if(size == 0) return NULL;
	
	void* ptr = malloc(size);
	
	#ifdef DEBUG
	    alloc_type type = MALLOC;
	
	    size_t index = addPtrToTrckr(type, ptr, size);
	    
	    if(getPrintAlloc(type)) printAllocMsg(type, *(getPtrTrckr(type, index)));
	#endif
	
	return ptr;
}

FORCE_INLINE void* betterCalloc(const size_t element_size, const size_t len)
{
	size_t size = (element_size * len);
	
	if(size == 0) return NULL;
	
	void* ptr = calloc(element_size, len);
	
	#ifdef DEBUG
	    alloc_type type = CALLOC;
	
	    size_t index = addPtrToTrckr(type, ptr, size);
	    
	    if(getPrintAlloc(type)) printAllocMsg(type, *(getPtrTrckr(type, index)));
	#endif
	
	return ptr;
}

FORCE_INLINE void* betterRealloc(void* base, size_t size)
{
	if(base == NULL) return NULL;
	
	if(size == 0)
	{
		#ifdef DEBUG
		    debugFree(base);
	    #else
		    free(base);
		#endif
		return NULL;
	}
	
	void* ptr = realloc(base, size);

    #ifdef DEBUG
	    alloc_type type;
    	size_t index = findPtrIndex(base, &type);
	
    	*(ptrs[type] + index) = ((ptr_trckr) {ptr, size});
    #endif
	
	return ptr;
}

#ifdef _cplusplus
}
#endif

#define alloc betterAlloc
#define alloca betterAlloc
#define malloc betterMalloc
#define calloc betterCalloc
#define realloc betterRealloc

#ifdef DEBUG
    #define free debugFree
#endif

#endif