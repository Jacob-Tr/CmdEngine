#ifndef THREADS_H
#define THREADS_H

#ifdef _cplusplus
    #include <cpthread>
#else
    #include <pthread.h>
#endif

typedef pthread_t thread_id;
typedef int_32 thread_num;
typedef pthread_attr_t thread_attr;
typedef size_t thread_stack_size;
typedef thread_id* HANDLE;
typedef void* start_func;
typedef void* start_func_params;

#define INFINITE ((uint_32) UINT_MAX)

#define THIS_THREAD pthread_self
#define thread_information struct thread_info

#define THREAD_CREATE(handle, id, stack_size, attributes, exe_func, exe_func_args, flags) unixThreadCreate((handle), (id), (stack_size), (attributes), (exe_func), (exe_func_args), (flags))

#define THREAD_JOIN(id) pthread_join((id), NULL)

#define THREAD_EXIT(id) pthread_exit((id))

#define THREAD_ATTR_INIT(attrib) unixThreadAttrInit((attrib))

#define THREAD_ATTR_DESTROY(attrib) pthread_attr_destroy((attrib))

#ifdef _cplusplus
extern "C"
{
#endif

FORCE_INLINE int_32 unixThreadAttrInit(pthread_attr_t* attr)
{
	return pthread_attr_init(attr);
}

FORCE_INLINE bool unixThreadCreate(HANDLE* handle, thread_id* id, const size_t stack_size, pthread_attr_t* attr, void* exec_func, void* exec_func_params, const int_32 flags)
{
	if(stack_size > 0) pthread_attr_setstacksize(attr, stack_size);
	
	int_64 err = pthread_create(id, attr, exec_func, exec_func_params);
	
	if(err != 0)
	{
		#ifdef DEBUG
		    fprintf(stderr, "Warning: Failed to create thread - Errno %l\n", err);
		#endif
		
		*handle = NULL;
		pthread_exit(id);
		
		return false;
	}
	
	pthread_attr_destroy(attr);
	
	*handle = id;
	
	return true;
}

FORCE_INLINE void WaitForMultipleObjects(const size_t num_threads, HANDLE* handles, const bool wait_all, const uint_32 milliseconds)
{
	HANDLE handle;
	for(size_t i = 0; i < num_threads; i++)
	{
		handle = *(handles + i);
		thread_id id = ((thread_id) *(*(handles + i)));
		
		pthread_join(id, NULL);
	}
}

#ifdef _cplusplus
}
#endif

#endif