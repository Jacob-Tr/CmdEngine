#ifndef CAMERA_H
#define CAMERA_H

typedef struct
{
	position pos;
	int_16 map_id;
} camera;

static camera main_cam;

#ifdef _cplusplus
extern "C"
{
#endif

camera* getMainCameraPtr(void) {return &main_cam;}

void setMainCamera(camera new_cam) {*(getMainCameraPtr()) = new_cam;}

void turnCam(camera* cam, const AXIS axis, const float degs) {updatePosAxis(&(cam->pos), axis, (getPosAxis(&(cam->pos), axis) + degs));}

void rotateCam(camera* cam, const AXIS axis, const float degs) {updatePosRotAxis(&(cam->pos), axis, (getPosRotAxis(&(cam->pos), axis) + degs));}

#ifdef _cplusplus
}
#endif

#endif