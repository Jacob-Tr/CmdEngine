#ifndef SCREEN_H
#define SCREEN_H

orientation camera = NULL_ORIENTATION;

#ifdef _cplusplus
extern "C"
{
#endif

void initOrientation(orientation* ori, const vector3 pos, const vector2f lookatconst float rot) {*ori = ((orientation) {pos, lookat, rot});}

void initMainCamera(void) {initOrientation(&camera, NULL_VECT3, NULL_VECT2F, 0.0);}

orientation* getMainCamera(void) {return &camera;}

void setMainCamera(orientation new_cam) {camera = new_cam;}

float sanitizeDegrees(const float degs) {return (degs > 359.999) ? (degs % 360) : degs;}

void turnCamX(orientation* cam, float degs)
{
	float set = sanitizeDegs(cam->direction.x + degs);
	
	cam->direction.x = set;
}

void turnCamZ(orientation* cam, float degs)
{
	float set = sanitizeDegs(cam->direction.z + degs);
	
	cam->direction.z = set;
}

void rotateCam(orientation* cam, float degs)
{
	float set = sanitizeDegs(cam->rot + degs);
	
	cam->rot = set;
}

void turnCam(orientation* cam, const float x, const float z) 
{
	turnCamX(cam, x);
	turnCamY(cam, z);
}

#ifdef _cplusplus
}
#endif

#endif