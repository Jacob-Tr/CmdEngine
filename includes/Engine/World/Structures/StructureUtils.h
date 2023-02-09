#ifndef STRUCTURE_UTILS_H
#define STRUCTURE_UTILS_H

#ifdef _cplusplus
extern "C"
{
#endif

static inline void updateMaxStructures(const size_t size)
{
	if(size >= SIZE_MAX) return;
	if(size < _max_nodes_) 
	{
		#ifdef DEBUG
		    fprintf(stderr, "Error: Cannot reduce max map structures. [Attempted %zu -> %zu]", _max_nodes_, size);
		#endif
		
		return;
	}
	
	_max_structures_ = size;
}

void initStructure(structure* strct, size_t nodes)
{
	if(nodes == 0)
	{
	    *strct = EMPTY_STRUCTURE;
	    return;
	}
	if(nodes >= _max_nodes_) nodes = (_max_nodes_ - 1);
	
	strct->node_buf = (node*) malloc(sizeof(node) * nodes);
	strct->size = nodes;
}

void updateStructureElement(structure* strct, const size_t element_id, const node value)
{
    if(element_id >= strct->size) return;
    
    *(strct->node_buf + element_id) = value;
}

void destroyStructure(structure* strct)
{
	free(strct->node_buf);
	strct->size = 0;
}

bool isEmptyStructure(structure* strct) {return (strct->size == 0);}


#ifdef _cplusplus
}
#endif

#endif