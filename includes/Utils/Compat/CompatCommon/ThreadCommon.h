#ifndef THREAD_COMMON_H
#define THREAD_COMMON_H

#define EMPTY_THREAD ((THREAD) {.init = false, .started = false, .id = 0, .stack_size = 0, .param_count = 0})
typedef struct
{
	bool init, started;
	thread_id id;
	HANDLE handle;
	thread_attr attr;
	size_t stack_size, param_count;
	start_func func_ptr;
	start_func_params func_param_buf;
} THREAD;

#define EMPTY_THREADQUEUE ((threadQueue) {.init = false, .started = false, .size = 0, .entries = 0, .threads = ((THREAD*) NULL)})
typedef struct
{
	bool init, started;
	size_t size, entries;
	THREAD* threads;
} threadQueue;

#ifdef _cplusplus
extern "C"
{
#endif

bool queueInitCheck(threadQueue* queue)
{
	if(queue->init) return true;
	
	THREAD* ptr = ((THREAD*) NULL);
	
	for(size_t i = 0; i < queue->entries; i++)
	{
		ptr = ((queue->threads) + i);
		if(!ptr->init) return false;
	}
	
	queue->init = true;

	return true;
}

void newThreadQueue(threadQueue* queue, const size_t queue_size)
{
	*queue = EMPTY_THREADQUEUE;
	
	queue->size = queue_size;
	queue->threads = (THREAD*) malloc(sizeof(THREAD) * queue->size);

	for(size_t i = 0; i < queue->size; i++) *(queue->threads + i) = EMPTY_THREAD;

	queue->init = true;
}

void destroyThreadQueue(threadQueue* queue)
{
	for(size_t i = 0; i < queue->entries; i++) THREAD_ATTR_DESTROY(&((queue->threads + i)->attr));
	free(queue->threads);
}

THREAD* getThreadPtrFromQueue(threadQueue* queue, const size_t index)
{
	if(index >= queue->size)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not get thread pointer at index #%zu in queue with %zu elements.\n", index, queue->size);
		#endif
		
		return ((THREAD*) NULL);
	}
	
	return ((queue->threads) + index);
}

bool isPtrToQueuedThread(threadQueue* queue, THREAD* thread)
{
	for(size_t i = 0; i < queue->entries; i++) if(getThreadPtrFromQueue(queue, i) == thread) return true;

    return false;
}

bool addThreadToQueue(threadQueue* queue, THREAD* thread)
{
	if(queue->started)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not add thread #%zu to queue - Threads in this queue have already been started.\n", ((size_t) thread->id));
		#endif
		
		return false;
	}
	
	if(!queue->init)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not add thread #%zu to queue - Thread queue not initialized.\n", ((size_t) thread->id));
		#endif
		
		return false;
	}
	
	if(queue->entries >= queue->size)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not add thread #%zu to queue of size %zu.\n", ((size_t) thread->id), queue->size);
		#endif
		
		return false;
	}
	
	thread->id = ((thread_id) queue->entries);
	
	if(isPtrToQueuedThread(queue, thread))
	{
		queue->entries++;
		return true;
	}
	
	*((queue->threads) + queue->entries++) = *thread;
	
	return true;
}

bool initThread(THREAD* thread, thread_attr* attr, start_func func, start_func_params params, const size_t param_count) 
{
	if(thread->init)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Reinitialization of thread #%zu.\n", ((size_t) thread->id));
		#endif
		    
        return false;
	}
	
	*thread = EMPTY_THREAD;
	
	THREAD_ATTR_INIT(*attr);
	thread->attr = *attr;
	
	thread->func_ptr = func;
	thread->func_param_buf = params;
	thread->param_count = param_count;
	
	thread->init = true;
	
	return true;
}

void initThreadsInQueue(threadQueue* queue, thread_attr* attr) {for(size_t i = 0; i < queue->entries; i++) initThread(((queue->threads) + i), attr, NULL, NULL, 0);}

void joinQueue(threadQueue* queue)
{
	if(!queue->started)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not join threads in queue - Threads not started.\n");
		#endif
		
		return;
	}
	
	HANDLE* handles = (HANDLE*) alloca(sizeof(HANDLE) * queue->entries);
	
	for(size_t i = 0; i < queue->entries; i++) *(handles + i) = (queue->threads + i)->handle;
	
	#ifdef _MSC_VER
	    WaitForMultipleObjects(((int_32) queue->entries), handles, true, INFINITE);
	#else
	    for(size_t i = 0; i < queue->entries; i++) pthread_join(*(*(handles + i)), NULL);
	#endif
}

void startThread(THREAD* thread)
{
	if(!thread->init)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not start thread #%zu. - Thread is not initialized.\n", ((size_t) thread->id));
		#endif
		
		return;
	}
	
	if(thread->started)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not start thread #%zu. - Thread is already running.\n", ((size_t) thread->id));
		#endif
		
		return;
	}
	
    #ifdef _MSC_VER
        HANDLE ret = NULL;
    #else
        int_32 ret = 0;
    #endif
	
	if(!(THREAD_CREATE(&thread->handle, &thread->id, thread->stack_size, &thread->attr, thread->func_ptr, thread->func_param_buf, 0)))
	{
	    #ifdef DEBUG
	        fprintf(stderr, "Warning:Failed to start thread #%zu.\n", ((size_t) thread->id));
	    #endif
	    
	    return;
	}
	
	#ifndef _MSC_VER
	    thread->handle = &(thread->id);
	#endif
	
	thread->started = true;
}

void startThreadsInQueue(threadQueue* queue)
{
	if(!queueInitCheck(queue))
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not start threads in queue. - Not all threads are initialized.\n");
		#endif

		return;
	}
	
	for(size_t i = 0; i < queue->entries; i++) startThread(queue->threads + i);
	
	queue->started = true;
}

#ifdef _cplusplus
}
#endif

#endif