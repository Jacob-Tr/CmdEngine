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

#define thread_information struct thread_info

#define THREAD_CREATE(handle, id, stack_size, attributes, exe_func, exe_func_args, flags) unixThreadCreate((handle), (id), stack_size, (attributes), (exe_func), (exe_func_args), (flags))

#define THREAD_JOIN(id) pthread_join((id), NULL)

#define THREAD_EXIT(id, value) pthread_exit((id))

#define THREAD_ATTR_INIT(attrib) unixThreadAttrInit((&attrib))

#define THREAD_ATTR_DESTROY(attrib) pthread_attr_destroy((attrib))

#ifdef _cplusplus
extern "C"
{
#endif

FORCE_INLINE int_32 unixThreadAttrInit(pthread_attr_t* attr)
{
	pthread_attr_init(attr);
}

FORCE_INLINE bool unixThreadCreate(HANDLE* handle, pthread_t* id, const size_t stack_size, pthread_attr_t* attr, void* exec_func, void* exec_func_params, const int_32 flags)
{
	long int* err = (!pthread_create(id, attr, exec_func, exec_func_params)) ? id : ((HANDLE) NULL);
	
	*handle = (err) ? NULL : id;
	
	return (*handle == NULL);
}

#ifdef _cplusplus
}
#endif

#endif