#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "math.h"

double width=640;
double height=480;

struct Cam{
	float x;
	float y;
	float z;
	struct Vec3 fwd;
	struct Vec3 rght;
	struct Vec3 up;
	struct Vec3 vel;
};

struct Cam Cam_new(float x,float y,float z,struct Vec3 fwd,struct Vec3 rght,struct Vec3 up);

//IMPLIMENT

struct Cam Cam_new(float x,float y,float z,struct Vec3 fwd,struct Vec3 rght,struct Vec3 up){
	struct Cam cam;
	cam.x=x;
	cam.y=y;
	cam.z=z;
	cam.fwd=fwd;
	cam.rght=rght;
	cam.up=up;
	cam.vel=Vec3_newn(0,0,0);
	return(cam);
}

#endif //PLAYER_H
