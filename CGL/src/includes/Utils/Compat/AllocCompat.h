
#ifndef ALLOCCOMPAT_H
#define ALLOCCOMPAT_H

#ifdef _cplusplus
extern "C"
{
#endif

static inline void* betterAlloc(const size_t size)
{
	if(size == 0) return NULL;
	
	#ifdef _MSC_VER
		void* ptr = _alloca(size);
	#else
		void* ptr = alloca(size);
	#endif
	
	#ifdef DEBUG
	    alloc_type type = ALLOCA;
	
	    size_t index = addPtrToTrckr(type, ptr, size);
	    
	    if(getPrintAlloc(type)) printAllocMsg(type, *(getPtrTrckr(type, index)));
	#endif
	
	return ptr;
}

static inline void* betterMalloc(const size_t size)
{
	if(size == 0) return NULL;
	
	void* ptr = malloc(size);

	if(ptr == NULL) return NULL;
	
	#ifdef DEBUG
		alloc_type type = MALLOC;
	
	    size_t index = addPtrToTrckr(type, ptr, size);
	    
	    if(getPrintAlloc(type)) printAllocMsg(type, *(getPtrTrckr(type, index)));
	#endif
	
	return ptr;
}

static inline void* betterCalloc(const size_t element_size, const size_t len)
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

static inline void* betterRealloc(void* base, size_t size)
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

		ptr_trckr* track = getPtrTrckr(type, index);

		track->addr = ptr;
		track->bytes = size;
    #endif
	
	return ptr;
}

#ifdef DEBUG
static inline void* namedMalloc(const char* name, const size_t length, const size_t size)
{
	if(size == 0) return NULL;
	
	void* ptr = malloc(size);
	
	alloc_type type = MALLOC;
	
	size_t index = addPtrToTrckr(type, ptr, size);
	
	namePtr(ptr, name, length);
	    
	if(getPrintAlloc(type)) printAllocMsg(type, *(getPtrTrckr(type, index)));
	
	return ptr;
}

static inline void* namedCalloc(const char* name, const size_t length, const size_t element_size, const size_t len)
{
size_t size = (element_size * len);
	
	if(size == 0) return NULL;
	
	void* ptr = calloc(element_size, len);
	
	alloc_type type = CALLOC;
	
	size_t index = addPtrToTrckr(type, ptr, size);
	
	namePtr(ptr, name, length);
	    
	if(getPrintAlloc(type)) printAllocMsg(type, *(getPtrTrckr(type, index)));
	
	return ptr;
}
#endif

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