#ifndef D3_H
#define D3_H

#define POINTS[14][3] {{-1,-1,-1},{-1,-1,1},{1,-1,1},{1,-1,-1},{-1,1,-1},{-1,1,1},{1,1,1},{1,1,-1},{0,0,-1},{1,0,0},{0,0,1},{-1,0,0},{0,-1,0},{0,1,0}}
#define CUBE[24][3] {{0,1,8},{1,5,8},{5,4,8},{4,0,8},{1,2,9},{2,6,9},{6,5,9},{5,1,9},{2,3,10},{3,7,10},{7,6,10},{6,2,10},{3,1,11},{1,4,11},{4,7,11},{7,3,11},{0,1,12},{1,2,12},{2,3,12},{3,1,12},{4,5,13},{5,6,13},{6,7,13},{7,4,13}}

#include <stdio.h>
#include <math.h>
#include "math.h"
#include "player.h"
#include "render.h"

float* D3(struct Cam cam,struct Vec3 pnt,int i);
float* Cube(struct Cam cam,float pnt[3],int i);

int draw=1;

//IMPLIMENT

/*float* D3(struct Cam cam,struct Vec3 pnt,int i){
	cam.fwd=Vec3_norm(cam.fwd);
	pnt=Vec3_norm(pnt);
	float theta=Vec3_angle(cam.fwd,pnt);
	if(theta>M_PI/2)
		draw=0;
	pnt=Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd);
	theta=Vec3_angle(cam.rght,pnt);
	if(Vec3_angle(cam.up,pnt)>M_PI/2)
		theta=-theta;
	float D2[2]={100*Vec3_length(pnt)*cos(theta)+(width/2),-100*Vec3_length(pnt)*sin(theta)+(height/2)};
	//if(i==2)
	//	printf("(%f,%f)\n",D2[0],D2[1]);
	return D2;
}/*/
float* D3(struct Cam cam,struct Vec3 pnt,int i){
	cam.fwd=Vec3_norm(cam.fwd);
	pnt=Vec3_norm(pnt);
	float theta=Vec3_angle(cam.fwd,pnt);
	float D2[2];
	float fov=5;
	//printf("%f\n",cos(M_PI/2-.01));
	float t=Vec3_angle(Vec3_newn(0,0,1),Vec3_newn(width,0,3*220));
	if(theta>t)
		draw=0;
	//if(i==0)
	//	printf("%f,%f,%f,%f\n",theta,cos(theta),1/cos(theta),M_PI/2);
	if(theta>M_PI/2-.1 && theta<M_PI/2+.1){
	//	printf("%f\n",cos(theta));
		theta=M_PI/2-.1;
	}
	if(theta>M_PI/2){
		pnt=Vec3_muln(Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd),fov);
		theta=Vec3_angle(cam.rght,pnt);
		if(Vec3_angle(cam.up,pnt)>M_PI/2)
			theta=-theta;
		D2[0]=-100*Vec3_length(pnt)*cos(theta)+(width/2);
		D2[1]=100*Vec3_length(pnt)*sin(theta)+(height/2);
	}else{
		pnt=Vec3_muln(Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd),fov);
		theta=Vec3_angle(cam.rght,pnt);
		if(Vec3_angle(cam.up,pnt)>M_PI/2)
			theta=-theta;
		D2[0]=100*Vec3_length(pnt)*cos(theta)+(width/2);
		D2[1]=-100*Vec3_length(pnt)*sin(theta)+(height/2);
	}
	//if(i==10)
	//	printf("(%f,%f,%f)\n",pnt.x,pnt.y,pnt.z);
	//	printf("(%f,%f)\n",D2[0],D2[1]);
	return D2;
}

float* Cube(struct Cam cam,float pnt[3],int i){
	float D2[14][2];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int j=0;j<14;j++){
		//D2[j]=D3(cam,Vec3_newv(POINTS[i],coord),i);
	}
	//float[24][3][2] pt;
	for(int j=0;j<24;j++){
		//pt[j][
	}
}

#endif //D3_H
