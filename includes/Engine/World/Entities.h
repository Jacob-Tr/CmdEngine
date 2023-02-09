#ifndef ENTITIES_H
#define ENTITIES_H

#include "includes/Engine/World/Entities/Sprites.h"

typedef struct
{
	char* name;
	sprite* spriteArr;
	position* spritePos;
	size_t sprites, name_len;
} entity;

static const entity* null_entity = ((entity*) NULL);

#ifdef _cplusplus
extern "C"
{
#endif

void initEntity(entity* ent,  const char* name, const size_t name_len)
{
	snprintf(ent->name, name_len, "%s", name);
	ent->name_len = name_len;
	
	memset((ent->spriteArr), 0, ent->sprites);
	memset((ent->spritePos), 0, ent->sprites);
}

void renameEntity(entity* ent, const char* new_name, const name_len)
{
	if(name_len >= ent->name_len) 
	{
		ent->name = (char*) realloc(ent->name, (sizeof(char*) * name_len));
		memset(ent->name, '\0', name_len);
	}
	
	snprintf(ent->name, name_len, "%s", new_name);
	ent->name_len = name_len;
}

entity* newEntity(const char* name, const size_t sprites, const size_t name_len)
{
	entity* ent = (entity*) malloc(sizeof(entity));
	ent->name = (char*) calloc(name_len, sizeof(char));
	ent->spriteArr = (sprite*) malloc(sizeof(sprite) * sprites);
	ent->spritePos = (position*) malloc(sizeof(position) * sprites);
	
	initEntity(ent, name, name_len);
	
	return ent;
}

#ifdef _cplusplus
}
#endif

#endif