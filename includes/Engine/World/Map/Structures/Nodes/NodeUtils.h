#ifndef MAP_NODEUTILS_H
#define MAP_NODEUTILS_H

static size_t _max_nodes_ = 256;

#ifdef _cplusplus
extern "C"
{
#endif

static inline void updateMaxNodes(const size_t size)
{
	if(size >= SIZE_MAX) return;
	if(size < _max_nodes_) 
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Cannot reduce max structure nodes. [Attempted %zu -> %zu]", _max_nodes_, size);
		#endif
		
		return;
	}
	
	_max_nodes_ = size;
}

#ifdef _cplusplus
}
#endif

#endif