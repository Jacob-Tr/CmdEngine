#ifndef TEXTURES_H
#define TEXTURES_H

typedef struct
{
	GPU_Image image;
	vector3f offset, rotation;
	vector2 size;
	size_t id;
} image;

typedef struct
{
	image* img_buf;
	vector3f position, rotation;
	size_t id;
} texture;

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#endif