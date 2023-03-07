#ifndef MESHES_H
#define MESHES_H

#define null_mesh ((mesh*) NULL)
#define empty_mesh {empty_position, empty_vect3}

typedef struct
{
	position pos;
	vector3 dimensions;
} mesh;

#ifdef __cplusplus
extern "C"
{
#endif

void newMesh(mesh* m)
{
	m = (mesh*) calloc(sizeof(mesh), 1);

	m->pos = ((position) empty_position);
	m->dimensions = ((vector3) empty_vector3);
}

void setMeshPosition(mesh* m, const position pos) {m->pos = pos;}

position getMeshPosition(mesh* m) {return m->pos;}

void setMeshDimensions(mesh* m, const vector3 dim) {m->dimensions = dim;}

vector3 getMeshDimensions(mesh* m) {return m->dimensions;}

bool doesPosOverlapMesh(const position pos, mesh* m)
{
	return false;
}

#ifdef __cplusplus
}
#endif

#endif