#ifndef THREADPOOL_H
#define THREADPOOL_H

static size_t thread_pools = 0;

#define empty_threadpool {.pool_id = SIZE_MAX, .elements = 0, .size = 0, .threads = ((THREAD*) NULL)}

typedef struct
{
	size_t pool_id, elements, size;
	THREAD* threads;
} thread_pool;

thread_pool* main_pool;

#define getRemainingPoolElements(pool_ptr) ((pool_ptr)->size - ((pool_ptr)->elements))

#ifdef __cplusplus
extern "C"
{
#endif

THREAD* getThreadPtrFromPool(thread_pool pool, const size_t element) {return (pool.threads + element);}

thread_pool* newThreadPool(const size_t size)
{
	thread_pool* pool = (thread_pool*) malloc(sizeof(thread_pool)), empty_pool = empty_threadpool;
	*pool = empty_pool;

	pool->size = size;
	pool->threads = (THREAD*) malloc(sizeof(THREAD) * pool->size);

	pool->pool_id = thread_pools++;

	THREAD* thread;

	for(size_t i = 0; i < pool->size; i++) 
	{
		thread = getThreadPtrFromPool(*pool, i);

		*thread = empty_thread;
		thread->id = SDL_GetThreadID(thread->thread);
		thread->is_pooled = true;
		thread->pool_id = pool->pool_id;
	}

	return pool;
}

void destroyThreadPool(thread_pool* pool)
{
	THREAD* t;

	for(size_t i = 0; i < pool->size; i++)
	{
		t = getThreadPtrFromPool(*pool, i);

		destroyThread(t);
	}

	free(pool->threads);
	free(pool);
}

size_t getFirstEmptyPoolElement(thread_pool pool)
{
	THREAD* thread_ptr;
	for(size_t i = 0; i < pool.size; i++) 
	{
		thread_ptr = getThreadPtrFromPool(pool, i);
		if(!thread_ptr->is_pooled_thread_assigned) return i;
	}

	return SIZE_MAX;
} 

THREAD* getNextThreadFromPool(thread_pool* pool, size_t* element_id)
{
	if(pool->elements >= pool->size) 
	{
		#ifdef DEBUG
			fprintf(stderr, "Warning: No available threads left in thread pool. [%zu/%zu used]\n", pool->elements, pool->size);
		#endif

		*element_id = UINT_MAX;
		return ((THREAD*) NULL);
	}

	*element_id = pool->elements++;
	THREAD* thread_ptr = getThreadPtrFromPool(*pool, *element_id);

	thread_ptr->is_pooled_thread_assigned = true;

	return thread_ptr;
}

void swapPoolElements(thread_pool* pool, const size_t element_one, const size_t element_two)
{
	if(element_one >= pool->size || element_two >= pool->size) 
	{
		#ifdef DEBUG
			fprintf(stderr, "Warning: Could not swap thread pool element %zu in thread pool of size %zu.\n", (element_one > element_two) ? element_one : element_two, pool->size);
		#endif

		return;
	}

	THREAD* one = getThreadPtrFromPool(*pool, element_one), *two = getThreadPtrFromPool(*pool, element_two);

	one->id = element_two;
	two->id = element_one;

	*(getThreadPtrFromPool(*pool, element_one)) = *two;
	*(getThreadPtrFromPool(*pool, element_two)) = *one;
}

void returnThreadToPool(thread_pool* pool, const size_t element)
{
	destroyThread(getThreadPtrFromPool(*pool, element));

	size_t next_empty = getFirstEmptyPoolElement(*pool);

	if(next_empty < element) swapPoolElements(pool, next_empty, element);
}

#ifdef __cplusplus
}
#endif

#endif