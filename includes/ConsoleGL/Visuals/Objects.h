#ifndef OBJECTS_H
#define OBJECTS_H

#ifndef BASE_OBJ_POINTS
    #define BASE_OBJ_POINTS 32
#endif
#ifndef BASE_OBJ_LINES
    #define BASE_OBJ_LINES 32
#endif

#ifdef _cplusplus
extern "C"
{
#endif

void initPointBuffer(object* obj) 
{
	obj->pts = (point*) malloc(sizeof(point) * BASE_OBJ_POINTS);
	obj->point_arr_size = BASE_OBJ_POINTS;
	obj->point_arr_entries = 0;
}

void initLineBuffer(object* obj)
{
	obj->lines = (line*) malloc(sizeof(line) * BASE_OBJ_LINES);
	obj->line_arr_size = BASE_OBJ_LINES;
	obj->line_arr_entries = 0;
}

object newObject(const size_t x, const size_t y, const size_t z)
{
	object obj;
	
	obj.pos.x = x;
	obj.pos.y = y;
	obj.pos.z = z;
	
	initPointBuffer(&obj);
	initLineBuffer(&obj);
	
	return obj;
}

void resizePointArr(object* obj)
{
	size_t new_size = (BASE_OBJ_POINTS * (obj->point_arr_size / BASE_OBJ_POINTS) + 1);
	if(obj->point_arr_size > new_size) return;
	
	obj->pts = (point*) realloc(obj->pts, (sizeof(point) * new_size));
	obj->point_arr_size = new_size;
}

point* getNextObjPointPtr(object* obj)
{
	resizePointArr(obj);
	return (obj->pts + obj->point_arr_entries);
}

size_t addPointToObj(object* obj, const point pt) 
{
	*(getNextObjPointPtr(obj)) = pt;
	obj->point_arr_entries++;
	
	return (obj->point_arr_entries - 1);
}

void removePointFromObj(object* obj, const size_t index) 
{
	for(size_t i = index; i < (obj->point_arr_entries - 1); i++) *((obj->pts) + i) = *((obj->pts) + (i + 1));
	
	*((obj->pts) + --obj->point_arr_entries) = EMPTY_POINT;
}

void resizeLineArr(object* obj)
{
	size_t new_size = (BASE_OBJ_LINES * (obj->line_arr_size / BASE_OBJ_LINES) + 1);
	if(obj->line_arr_size > new_size) return;
	
	obj->lines = (line*) realloc(obj->lines, (sizeof(line) * new_size));
	obj->line_arr_size = new_size;
}

line* getNextObjLinePtr(object* obj)
{
	resizeLineArr(obj);
	return (obj->lines + obj->line_arr_entries);
}

size_t addLineToObj(object* obj, const line ln)
{
	*(getNextObjLinePtr(obj)) = ln;
	obj->line_arr_entries++;
	
	return (obj->line_arr_entries - 1);
}

void removeLineFromObj(object* obj, const size_t index)
{
	for(size_t i = index; i < (obj->line_arr_entries - 1); i++) *((obj->lines) + i) = *((obj->lines) + (i + 1));
	
	*((obj->lines) + --obj->line_arr_entries) = EMPTY_LINE;
}

#ifdef _cplusplus
}
#endif

#endif