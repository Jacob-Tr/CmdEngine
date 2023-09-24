#ifndef SPRITES_H
#define SPRITES_H

#define MAX_ENTITY_SPRITES 32

typedef struct
{
	char* name;
	size_t name_len;
	vector3 size;
	position offset;
	char* layout;
} sprite;

static const sprite* null_sprite = ((sprite*) NULL);

#ifdef _cplusplus
extern "C"
{
#endif

void initSprite(sprite* sp, const char* name, const char* layout, const vector3 size, const size_t name_len) 
{
	snprintf(sp->name, name_len, "%s", name);
	
	memcpy(sp->layout, layout, getVector3Total(size));
	
	sp->size = size;
	sp->name_len = name_len;
	
	initPosition(&(sp->offset));
}

void setSprite(sprite* dest, sprite src) {memcpy(dest, &src, sizeof(sprite));}

void renameSprite(sprite* sp, const char* newName, const size_t length)
{
	if(length >= sp->name_len) 
	{
		sp->name = (char*) realloc(sp->name, (sizeof(char*) * length));
		memset(sp->name, '\0', length);
	}
	
	snprintf(sp->name, length, "%s", newName);
	sp->name_len = length;
}
	
sprite* newSprite(const char* name, const char* layout, const vector3 size, const size_t name_len)
{
	sprite* sp = (sprite*) malloc(sizeof(sprite));
	sp->name = (char*) calloc(name_len, sizeof(char));
	
	initSprite(sp, name, layout, size, name_len);
	
	return sp;
}

void destroySprite(sprite** spPtr)
{
	sprite* sp = *spPtr;
	
	free(sp->name);
	free(sp->layout);
	
	sp->name_len = 0;
	destroyVect(sp->size, 3);
	
	*spPtr = ((sprite*) NULL);
}

#ifdef _cplusplus
}
#endif

#endif