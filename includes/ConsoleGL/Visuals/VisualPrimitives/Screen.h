#ifndef SCREEN_H
#define SCREEN_H

orientation camera = NULL_ORIENTATION;

#ifdef _cplusplus
extern "C"
{
#endif

void initOrientation(orientation* ori, const vector3 pos, const vector2f lookat, const float rot) {*ori = ((orientation) {pos, lookat, rot});}

void initMainCamera(void) 
{
	const vector3 def_vect3 = NULL_VECT3;
	const vector2f def_vect2f = NULL_VECT2F;

	initOrientation(&camera, def_vect3, def_vect2f, 0.0);
}

orientation* getMainCamera(void) {return &camera;}

void setMainCamera(orientation new_cam) {camera = new_cam;}

float sanitizeDegrees(const float degs) {return (degs > 359.999F) ? ((float) fmod(degs, 359.999F)) : degs;}

void turnCamX(orientation* cam, float degs)
{
	float set = sanitizeDegrees(cam->direction.x + degs);
	
	cam->direction.x = set;
}

void turnCamZ(orientation* cam, float degs)
{
	float set = sanitizeDegrees(cam->direction.z + degs);
	
	cam->direction.z = set;
}

void rotateCam(orientation* cam, float degs)
{
	float set = sanitizeDegrees(cam->rot + degs);
	
	cam->rot = set;
}

void turnCam(orientation* cam, const float x, const float z) 
{
	turnCamX(cam, x);
	turnCamZ(cam, z);
}

#ifdef _cplusplus
}
#endif

#endif