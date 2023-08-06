#ifndef THREADQUEUE_H
#define THREADQUEUE_H

#define empty_threadqueue ((threadQueue) {.init = false, .started = false, .size = 0, .entries = 0, .threads = ((thread_pool*) NULL)})
typedef struct
{
	bool init, started;
	thread_pool* threads;
} threadQueue;

#ifdef __cplusplus
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
	*queue = empty_threadqueue;
	
	queue->size = queue_size;
	queue->threads = (THREAD*) malloc(sizeof(THREAD) * queue->size);

	for(size_t i = 0; i < queue->size; i++) *(queue->threads + i) = empty_thread;

	queue->init = true;
}

void destroyThreadQueue(threadQueue* queue) 
{
	for(size_t i = 0; i < queue->entries; i++) destroyThread((queue->threads +  i));
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
	
	thread->id = ((uint32_t) queue->entries);
	
	if(isPtrToQueuedThread(queue, thread))
	{
		queue->entries++;
		return true;
	}
	
	*(queue->threads + queue->entries++) = *thread;
	
	return true;
}

void joinQueue(threadQueue* queue)
{
	if(!queue->started)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Could not join threads in queue - Threads not started.\n");
		#endif
		
		return;
	}
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

#ifdef __cplusplus
}
#endif

#endif