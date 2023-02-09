#ifndef THREADS_H
#define THREADS_H

typedef DWORD thread_id;
typedef int_32 thread_num;
typedef LPSECURITY_ATTRIBUTES thread_attr;
typedef size_t thread_stack_size;
typedef LPTHREAD_START_ROUTINE start_func;
typedef LPVOID start_func_params;

#define thread_information struct thread_info

#define THREAD_CREATE(handle, id, stack_size, attributes, exe_func, exe_func_args, flags) winThreadCreate((handle), (id), (stack_size), (attributes), (exe_func), (exe_func_args), (flags))

#define THREAD_JOIN(id) WaitForSingleObject(id, INFINITE)

#define THREAD_EXIT(id, value) pthread_exit((id), (value))

#define THREAD_ATTR_INIT(attr) winThreadAttrInit((attr))

#define THREAD_ATTR_DESTROY(attrib) winThreadAttrDestroy((attrib))

#ifdef _cplusplus
extern "C"
{
#endif

FORCE_INLINE int_32 winThreadAttrInit(LPSECURITY_ATTRIBUTES attr)
{
	return 0;
}

FORCE_INLINE bool winThreadCreate(HANDLE* handle, LPDWORD id, const size_t stack_size, LPSECURITY_ATTRIBUTES* attr, LPTHREAD_START_ROUTINE exec_func, __drv_aliasesMem LPVOID exec_func_args, DWORD flags)
{
	*handle = CreateThread(*attr, stack_size, exec_func, exec_func_args, flags, id);
	
	return (*handle != NULL);
}

FORCE_INLINE int_32 winThreadAttrDestroy(LPSECURITY_ATTRIBUTES* attr) {return 0;}

#ifdef _cplusplus
}
#endif

#endif
