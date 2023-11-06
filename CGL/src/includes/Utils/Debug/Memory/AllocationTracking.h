#ifndef ALLOC_TRACKING_H
#define ALLOC_TRACKING_H

void debugFree(void* ptr);

void strForm(char* dest, const char* src, const char align, const uint8_t strings, const size_t dest_size, const size_t lengths[]);

#ifdef _MSC_VER
	#define alloca _alloca
#endif

typedef enum 
{
	MALLOC,
	CALLOC,
	ALLOCA,
	NULL_ALLOC
} alloc_type;

enum prt_track
{
	TRCK_ADDR,
	TRCK_BYTES,
	TRCK_NULL
};

#define MAX_PTR_NAME 32

typedef struct
{
	char* name;
	void* addr;
	size_t bytes, name_len;
} ptr_trckr;

static ptr_trckr* ptrs[NULL_ALLOC] = {NULL, NULL, NULL};
static size_t bytes[NULL_ALLOC] = {0, 0, 0}, allocations[NULL_ALLOC] = {0, 0, 0}, ptr_buf_size[NULL_ALLOC] = {0, 0, 0};

static bool __free_msg__ = false;

#ifndef __PRINT_ALL_ALLOCS__
    static bool __print_alloc__ = false;
    static bool __print_calloc__ = false;
    static bool __print_malloc__ = false;
#else
    static bool __print_alloc__ = true;
    static bool __print_calloc__ = true;
    static bool __print_malloc__ = true;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

void setPrintAlloc(const alloc_type type, const bool value)
{
	switch(type)
	{
		case ALLOCA:
		{
			__print_alloc__ = value;
			break;
		}
		case CALLOC:
		{
			__print_calloc__ = value;
			break;
		}
		case MALLOC:
		{
			__print_malloc__ = value;
			break;
		}
	}
}

bool getPrintAlloc(const alloc_type type)
{
	switch(type)
	{
		case ALLOCA: return __print_alloc__;
		case CALLOC: return __print_calloc__;
		case MALLOC: return __print_malloc__;
	}

	return false;
}

void setPrintAllAllocs(const bool value)
{
	setPrintAlloc(MALLOC, value);
	setPrintAlloc(ALLOCA, value);
	setPrintAlloc(CALLOC, value);
}

void setFreeMsg(const bool value) {__free_msg__ = value;}

void allocTypeToText(char* dest, const alloc_type type)
{
	switch(((int) type))
	{
		case MALLOC:
		{
			memcpy(dest, "Malloc", 7);
			*(dest + 6) = '\0';
			return;
		}
		case CALLOC:
		{
			memcpy(dest, "Calloc", 7);
			*(dest + 6) = '\0';
			return;
		}
		case ALLOCA:
		{
			memcpy(dest, "Alloc", 6);
			*(dest + 5) = '\0';
			return;
		}
		default: snprintf(dest, 10, "Null");
	}
}

void initPtrTrckr(alloc_type type)
{
	ptr_buf_size[type] = 32;
	ptrs[type] = (ptr_trckr*) malloc(sizeof(ptr_trckr) * ptr_buf_size[type]);
}

void resizePtrBuf(alloc_type type)
{
	ptr_buf_size[type] *= 2;
	ptrs[type] = (ptr_trckr*) realloc(ptrs[type], sizeof(ptr_trckr) * ptr_buf_size[type]);
}

size_t addPtrToTrckr(alloc_type type, void* ptr, const size_t size)
{
	if(ptr == NULL) return SIZE_MAX;
	
	if((allocations[type] + 1) >= ptr_buf_size[type]) {resizePtrBuf(type);}
	
	ptr_trckr trck = {NULL, 0};
	
	trck.name = ((char*) NULL);
	trck.name_len = 0;
	
	trck.addr = ptr;
	trck.bytes = size;
	
	*(ptrs[type] + allocations[type]) = trck;
	bytes[type] += size;
	
	return allocations[type]++;
}

FORCE_INLINE size_t findPtrIndex(void* ptr, alloc_type* type)
{
	if(ptr == NULL) 
	{
		fprintf(stderr, "Warning: NULL passed to findPtrIndex.\n");
		return SIZE_MAX;
	}
	
	char* type_str = (char*) alloca(sizeof(char) * 10);
	
	for(size_t i = 0; i < NULL_ALLOC; i++)
	{
		*type = (i == 0) ? MALLOC : (i == 1) ? CALLOC : ALLOCA;
		
		for(size_t ii = 0; ii < allocations[*type]; ii++) if((ptrs[*type] + ii)->addr == ptr) return ii;
	}
	
	*type = NULL_ALLOC;
	return SIZE_MAX;
}

FORCE_INLINE ptr_trckr* getPtrTrckr(const alloc_type type, const size_t index)
{
	if(type >= NULL_ALLOC)
	{
		fprintf(stderr, "Warning: Invalid alloc type passed to getPtrTrckr [%zu].\n", ((size_t) type));
		
		return ((ptr_trckr*) NULL);
	}
	
	char* type_str = (char*) alloca(sizeof(char) * 10);
	
	allocTypeToText(type_str, type);
	
	if(index >= allocations[type])
	{
		fprintf(stderr, "Warning: Index passed to getPrtTrckr [%zu] is out of bounds for alloc type %s.\n", index, type_str);
		
		return ((ptr_trckr*) NULL);
	}
	
	return (ptrs[type] + index);
}

void namePtr(void* ptr, const char* name, const size_t length)
{
	alloc_type type;
	size_t index = findPtrIndex(ptr, &type);
	
	if(index == SIZE_MAX)
	{
		fprintf(stderr, "Warning: Could not assign name \"%s\" to address %p. - Not in pointer tracker.\n", name, ptr);
		
		return;
	}
	
	ptr_trckr* track = (ptrs[type] + index);
	
	track->name = (char*) calloc(sizeof(char), MAX_PTR_NAME);
	track->name_len = (length > MAX_PTR_NAME) ? MAX_PTR_NAME : length;
	
	snprintf(track->name, length, "%s", name);
}

void removePtrNameByTracker(ptr_trckr* track)
{
	char* addr = track->name;
	
	if(addr == NULL) return;
	
	free(track->name);
	track->name_len = 0;
	
    track->name = ((char*) NULL);
    
    free(addr);
}

void removePtrName(void* ptr)
{
	alloc_type type;
	size_t index = findPtrIndex(ptr, &type);
	
	if(index == SIZE_MAX)
	{
		fprintf(stderr, "Warning: Could not remove name from address %p. - Not in pointer tracker.\n", ptr);
		
		return;
	}
	
	ptr_trckr* track = (ptrs[type] + index);
	
	removePtrNameByTracker(track);
}

void removeAllPtrNames(void)
{
	ptr_trckr* track;
	
	for(size_t i = 0; i < NULL_ALLOC; i++)
	{
		for(size_t ii = 0; ii < allocations[i]; ii++)
		{
			track = (ptrs[i] + ii);
			if(track->name != NULL) removePtrNameByTracker(track);
		}
	}
}

void removePtrFromTrckrByIndex(const size_t index, const alloc_type type)
{
	if((ptrs[type] + index)->addr == NULL) return;

	ptr_trckr trckr = *(ptrs[type] + index);
	
	size_t prev_bytes = bytes[type];
	
	bytes[type] -= trckr.bytes;
    
    if(bytes[type] > prev_bytes) fprintf(stderr, "Warning: Registering %zu bytes for allocation type %d.\n", bytes[type], ((int32_t) type));

    removePtrNameByTracker((ptrs[type] + index));
	
	*(ptrs[type] + index) = ((ptr_trckr) {NULL, 0});
}

void removePtrFromTrckr(void* ptr)
{
	alloc_type type = NULL_ALLOC;
	size_t index = findPtrIndex(ptr, &type);
	
	if(type >= NULL_ALLOC || index >= SIZE_MAX)
	{
		fprintf(stderr, "Warning: %p was not found in tracked address list.\n", ptr);
		
		return;
	}
	
	removePtrFromTrckrByIndex(index, type);
}

void finalizeMemory(void)
{
	ptr_trckr track;
	void* ptr = NULL;
	size_t leaked_bytes = 0, total_leaked_bytes = 0, leaks = 0;
	
	for(size_t i = 0; i < NULL_ALLOC; i++) 
	{
		if(i == ALLOCA) continue;
		for(size_t ii = 0; ii < allocations[i]; ii++) 
		{
			track = *(ptrs[i] + ii);
			ptr = track.addr;
			
			if(ptr != NULL)
			{
				leaks++;
				leaked_bytes = track.bytes;
				total_leaked_bytes += leaked_bytes;
				
				fprintf(stderr, "Warning: Memory leak detected - %zu bytes at address: %p.\n", leaked_bytes, ptr);
			    debugFree((ptrs[i] + ii)->addr);
			}
		}
	}
	
	fprintf(stderr, "~ %zu leaks found - Total: %zu leaked bytes.", leaks, total_leaked_bytes);
	
	removeAllPtrNames();
	
	for(size_t i = 0; i < NULL_ALLOC; i++) free(ptrs[i]);
}

void printAllocStats(void)
{
	bool prev_free_val = __free_msg__;
	setFreeMsg(false);
	
	const size_t digits = 12, str_size = (sizeof(char) * (((digits * 2) + 9)));
	char* alloc_bytes[NULL_ALLOC] = {(char*) malloc(str_size), (char*) malloc(str_size), (char*) malloc(str_size)};
	
	const char* chart_head = "Bytes - Allocations";
	
	snprintf(alloc_bytes[ALLOCA], str_size, "Alloc: %zu - %zu", bytes[ALLOCA], allocations[ALLOCA]);
	snprintf(alloc_bytes[CALLOC], str_size, "Calloc: %zu - %zu", bytes[CALLOC], allocations[CALLOC]);
	snprintf(alloc_bytes[MALLOC], str_size, "Malloc: %zu - %zu", bytes[MALLOC], allocations[MALLOC]);
	
	size_t lengths[NULL_ALLOC + 1] = {strlen(chart_head), strlen(alloc_bytes[ALLOCA]), strlen(alloc_bytes[CALLOC]), strlen(alloc_bytes[MALLOC])}, largest = 0;
	
	for(size_t i = 0; i < NULL_ALLOC; i++) if(lengths[i] > largest) largest = lengths[i];
	
	size_t chart_size = (sizeof(char) * (str_size * 4) + (largest * 3));
	char* chart = (char*) malloc(chart_size);
	snprintf(chart, chart_size, "%s%s%s%s", chart_head, alloc_bytes[ALLOCA], alloc_bytes[CALLOC], alloc_bytes[MALLOC]);
	
	free(alloc_bytes[ALLOCA]);
	free(alloc_bytes[CALLOC]);
	free(alloc_bytes[MALLOC]);
	
	strForm(chart, chart, '-', (NULL_ALLOC + 1), chart_size, lengths);
	
	fprintf(stdout, "%s", chart);
	
	free(chart);
	
	setFreeMsg(prev_free_val);
}

void initTrckrs(void)
{
	initPtrTrckr(ALLOCA);
	initPtrTrckr(CALLOC);
	initPtrTrckr(MALLOC);
}

void debugFree(void* ptr)
{
	if(ptr == NULL) return;
	
	alloc_type type;
	size_t index = findPtrIndex(ptr, &type);
	
	if(index == SIZE_MAX)
	{
		fprintf(stderr, "Error: Address %p failed to free - Not found in tracker.\n", ptr);
		
		return;
	}
	
	ptr_trckr track = *(ptrs[type] + index);
	
	char* type_str = (char*) alloca(sizeof(char) * 10);
	allocTypeToText(type_str, type);
	
	if(__free_msg__) 
	{
		if(track.name == NULL) fprintf(stderr, "Freeing address %p of type %s and size %zu bytes\n", ptr, type_str, track.bytes);
		else fprintf(stderr, "Freeing address %p [Name: \"%s\"] of type %s and size %zu bytes\n", ptr, track.name, type_str, track.bytes);
	}
	
	removePtrFromTrckrByIndex(index, type);

	return;
	
	free(ptr);
}

void printAllocMsg(const alloc_type type, const ptr_trckr track)
{
	char* type_str = (char*) alloca(sizeof(char) * 10);
	
	allocTypeToText(type_str, type);
	
	if(track.name == NULL) fprintf(stdout, "Allocated %zu bytes of type %s at address %p.\n", track.bytes, type_str, track.addr);
	else fprintf(stdout, "Allocated %zu bytes of type %s[Name: \"%s\"] at address %p.\n", track.bytes, type_str, track.name, track.addr);
}

#ifdef _cplusplus
}
#endif

#ifdef _MSC_VER
	#undef alloca
#endif

#endif