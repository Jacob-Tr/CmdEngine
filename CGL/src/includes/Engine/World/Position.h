#ifndef POSITION_H
#define POSITION_H

typedef enum
{
	X,
	Y,
	Z
} AXIS;

#define empty_position {0, (vector3f) Vect3(0.0, 0.0, 0.0), (vector3f) Vect3(0.0, 0.0, 0.0)}
typedef struct
{
	world w;
	vector3f rot, pos;
} position;

static const position* null_position = ((position*) NULL);

#ifdef __cplusplus
extern "C"
{
#endif

float* getPosAxisPtr(position* pos, const AXIS axis)
{
	switch(axis)
	{
		case X: return &(pos->pos.x);
		case Y: return &(pos->pos.y);
		case Z: return &(pos->pos.z);
	}
	
	#ifdef DEBUG
		fprintf(stderr, "Warning: Invalid axis specified for position axis [%zu].\n", ((size_t) axis));
	#endif
	
	return ((float*) NULL);
}

float* getPosRotAxisPtr(position* pos, const AXIS axis)
{
	switch(axis)
	{
		case X: return &(pos->rot.x);
		case Y: return &(pos->rot.y);
		case Z: return &(pos->rot.z);
	}
	
	#ifdef DEBUG
		fprintf(stderr, "Warning: Invalid axis specified for rotation axis [%zu].\n", ((size_t) axis));
	#endif
	
	return ((float*) NULL);
}

float getPosAxis(position* pos, const AXIS axis) {return *(getPosAxisPtr(pos, axis));}

float getPosRotAxis(position* pos, const AXIS axis) {return *(getPosRotAxisPtr(pos, axis));}

world getPosWorld(const position pos) {return pos.w;}

void updatePosAxis(position* pos, const AXIS axis, const float new_val)
{
	switch(axis)
	{
		case X:
		{
			pos->pos.x = new_val;
			return;
		}
		case Y:
		{
			pos->pos.y = new_val;
			return;
		}
		case Z:
		{
			pos->pos.z = new_val;
			return;
		}
		default:
		{
			#ifdef DEBUG
			    fprintf(stderr, "Warning: Invalid axis specified for position update [%zu].\n", ((size_t) axis));
			#endif
			
			return;
		}
	}
}

void updatePosRotAxis(position* pos, const AXIS axis, float new_val)
{
	new_val = sanitizeDegrees(new_val);
	
	switch(axis)
	{
		case X:
		{
			pos->rot.x = new_val;
			return;
		}
		case Y:
		{
			pos->rot.y = new_val;
			return;
		}
		case Z:
		{
			pos->rot.z = new_val;
			return;
		}
		default:
		{
			#ifdef DEBUG
			    fprintf(stderr, "Warning: Invalid axis specified for rotation update [%zu].\n", ((size_t) axis));
			#endif
			
			return;
		}
	}
}

void updatePos(position* pos, const vector3f new_pos) {pos->pos = new_pos;}

void updatePosRot(position* pos, const vector3f new_rot) {pos->rot = new_rot;}

void updatePosWorld(position* pos, const world w) {pos->w = w;}

void initPosition(position* pos)
{
	vector3f coords = (vector3f) Vect3(0.0, 0.0, 0.0), rot = (vector3f) Vect3(0.0, 0.0, 0.0);
	
	updatePosWorld(pos, 0);
	updatePos(pos, coords);
	updatePosRot(pos, rot);
}

#ifdef __cplusplus
}
#endif

#endif