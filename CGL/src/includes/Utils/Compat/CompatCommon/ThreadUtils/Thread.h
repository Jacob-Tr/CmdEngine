#ifndef THREAD_H
#define THREAD_H

#define MAX_THREAD_NAME ((size_t) 64)

#define empty_thread ((THREAD) {.init = false, .started = false, .is_pooled = false, .is_pooled_thread_assigned = false, .pool_id = SIZE_MAX, .pool_element = SIZE_MAX, .thread = ((SDL_Thread*) NULL), .id = 0, .stack_size = 0, .param_count = 0})
typedef struct
{
	bool init, started, is_pooled, is_pooled_thread_assigned;
	size_t pool_id, pool_element;
	SDL_Thread* thread;
	SDL_threadID id;
	char* thread_name;
	size_t stack_size, param_count, thread_name_len;
	void* func_ptr;
	void* func_param_buf;
} THREAD; // 672 bytes

#ifdef _cplusplus
extern "C"
{
#endif

void destroyThread(THREAD* thread)
{
	if(thread->thread_name != ((char*) NULL)) free(thread->thread_name);
	thread->thread_name_len = 0;

	bool is_pooled = thread->is_pooled;
	size_t id = SIZE_MAX, element = SIZE_MAX;
	if(is_pooled)
	{
		id = thread->pool_id;
		element = thread->pool_element;
	}

	*thread = empty_thread;

	thread->is_pooled = is_pooled;
	thread->pool_id = id;
	thread->pool_element = element;
}

bool initThread(THREAD* thread, const char* name, size_t name_len, void* func, void* params, const size_t param_count) 
{
	if(thread->init)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Reinitialization of thread \"%s\" [#%lu].\n", thread->thread_name, thread->id);
		#endif
		    
        return false;
	}

	if(strlen(name) >= MAX_THREAD_NAME)
	{
		#ifdef DEBUG
			fprintf(stderr, "Warning: Thread name \"%s\" is too long. [Max: %zu characters]\n", name, MAX_THREAD_NAME);
		#endif

		return false;
	}
	
	*thread = empty_thread;

	thread->thread_name = (char*) malloc(sizeof(char) * (name_len + 1));
	
	thread->thread_name_len = name_len;
	memcpy(thread->thread_name, name, name_len);
	*(thread->thread_name + name_len) = '\0';

	thread->func_ptr = func;
	thread->func_param_buf = params;
	thread->param_count = param_count;
	
	thread->init = true;
	
	return true;
}

bool startThread(THREAD* thread)
{
	if(!thread->init)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Could not start thread \"%s\"[#%zu]. - Thread is not initialized.\n", thread->thread_name, ((size_t) thread->id));
		#endif
		
		return false;
	}
	
	if(thread->started)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Could not start thread \"%s\"[#%zu]. - Thread is already running.\n", thread->thread_name, ((size_t) thread->id));
		#endif
		
		return false;
	}

	thread->thread = SDL_CreateThread(thread->func_ptr, thread->thread_name, thread->func_param_buf);

	if(thread->thread == NULL)
	{
		#ifdef DEBUG
			fprintf(stderr, "Error: Could not start thread \"%s\"[#%zu].\n", thread->thread_name, ((size_t) thread->id));
		#endif

		return false;
	}
	
	thread->started = true;

	return true;
}

#ifdef __cplusplus
}
#endif

#endif