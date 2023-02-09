#ifndef MAP_UTILS_H
#define MAP_UTILS_H

#ifdef _cplusplus
extern "C"
{
#endif

void initMap(map* m, const size_t structures)
{
	if(structures >= MAX_STRUCTURES) return;
	if(structures == 0)
	{
		memset(m, 0, sizeof(*m));
		return;
	}
	
	m->strcts = (structure*) malloc(sizeof(structure) * structures);
	m->size = structures;
	
	for(size_t i = 0; i < m->size; i++) {*(m->strcts) = EMPTY_STRUCTURE;}
}

size_t findFirstNullStructureFrom(map* m, const size_t start_index)
{
	for(size_t i = start_index; i < m->size; i++) if(isEmptyStructure((m->strcts + i))) return i;
	
	return SIZE_MAX;
}

size_t findFirstNullStructure(map* m) {return findFirstNullStructureFrom(m, 0);}


#ifdef _cplusplus
}
#endif

#endif