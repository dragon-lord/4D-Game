#ifndef INPUTHANDELER_H
#define INPUTHENDELER_H

#include<stdio.h>
#include<SDL2/SDL2_gfxPrimitives.h>

#include"render.h"
#include"player.h"

int Input_init();
struct Cam Input_update(struct Cam cam);

//IMPLEMENT
int input[11]={0,0,0,0,0,0,0};
int gui=1;
float mouse[2]={0,0};

int Input_init(){
	/*if(SDL_SetRelativeMouseMode(SDL_TRUE)!=0){
		printf("errr");
		return 0;
	}//*/
	return 1;
}

struct Cam Input_update(struct Cam cam){
	struct Vec3 vec=/*cam.fwd;/*/Vec3_norm(Vec3_cross(cam.rght,cam.up));//*/

	/*if(input[0]==1){
		cam.z+=1;
		input[0]=0;
	}
	if(input[1]==1){
		cam.x-=1;
		input[1]=0;
	}
	if(input[2]==1){
		cam.z-=1;
		input[2]=0;
	}
	if(input[3]==1){
		cam.x+=1;
		input[3]=0;
	}
	if(input[4]==1){
		cam.y+=1;
		input[4]=0;
	}
	if(input[5]==1){
		cam.y-=1;
		input[5]=0;
	}/*/
	if(input[0]==1){
		cam.x+=vec.x/10;
		cam.y+=vec.y/10;
		cam.z+=vec.z/10;
	}
	if(input[1]==1){
		cam.x-=cam.rght.x/10;
		cam.y-=cam.rght.y/10;
		cam.z-=cam.rght.z/10;
	}
	if(input[2]==1){
		cam.x-=vec.x/10;
		cam.y-=vec.y/10;
		cam.z-=vec.z/10;
	}
	if(input[3]==1){
		cam.x+=cam.rght.x/10;
		cam.y+=cam.rght.y/10;
		cam.z+=cam.rght.z/10;
	}
	if(input[4]==1){
		cam.x+=cam.up.x/10;
		cam.y+=cam.up.y/10;
		cam.z+=cam.up.z/10;
	}
	if(input[5]==1){
		cam.x-=cam.up.x/10;
		cam.y-=cam.up.y/10;
		cam.z-=cam.up.z/10;
	}//*/
	if(!gui){
		//printf("(%f,%f)\n",mouse[0],mouse[1]);
		if(mouse[1]<0){
			if(Vec3_angle(cam.fwd,cam.up)<M_PI/8){}else{
				cam.fwd=Vec3_rot(cam.fwd,cam.fwd,cam.up,mouse[1]/-50);}
		}else{
			if(Vec3_angle(cam.fwd,cam.up)>7*M_PI/8){}else{
				cam.fwd=Vec3_rot(cam.fwd,cam.fwd,cam.up,mouse[1]/-50);}
		}
		cam.fwd=Vec3_rot(cam.fwd,cam.fwd,cam.rght,mouse[0]/-50);
		cam.rght=Vec3_cross(cam.fwd,cam.up);
		mouse[0]=0;
		mouse[1]=0;
	}
	if(input[6]==1){
		if(Vec3_angle(cam.fwd,cam.up)<M_PI/8){}else{
			cam.fwd=Vec3_rot(cam.fwd,cam.fwd,cam.up,0.05);}
	}
	if(input[7]==1){
		if(Vec3_angle(cam.fwd,cam.up)>7*M_PI/8){}else{
			cam.fwd=Vec3_rot(cam.fwd,cam.fwd,cam.up,-0.05);}
	}
	if(input[8]==1){
		cam.fwd=Vec3_rot(cam.fwd,cam.fwd,cam.rght,0.05);
		cam.rght=Vec3_cross(cam.fwd,cam.up);
	}
	if(input[9]==1){
		cam.fwd=Vec3_rot(cam.fwd,cam.fwd,cam.rght,-0.05);
		cam.rght=Vec3_cross(cam.fwd,cam.up);
	}
	if(input[10]==1){
		if(!gui){
			if(SDL_SetRelativeMouseMode(SDL_FALSE)!=0){
				printf("err:esc\n");
			}
			gui=1;
		}else{
			if(SDL_SetRelativeMouseMode(SDL_TRUE)!=0){
				printf("err:esc\n");
			}
			gui=0;
		}//*/
		input[10]=0;
	}
	while(SDL_PollEvent(&e)){
		if (e.window.event == SDL_WINDOWEVENT_CLOSE)
			quit=1;
		switch(e.type){
			case SDL_MOUSEMOTION:
				/*if(!gui){
					printf("(%d,%d)\n",e.motion.xrel,e.motion.yrel);
					cam.fwd=Vec3_rot(cam.fwd,cam.rght,e.motion.yrel/5);
					cam.fwd=Vec3_rot(cam.fwd,cam.up,e.motion.xrel/5);
					cam.rght=Vec3_cross(cam.fwd,cam.up);
				}/*/
				if(!gui){
					mouse[0]=e.motion.xrel;
					mouse[1]=e.motion.yrel;
				}else{
					mouse[0]=0;
					mouse[1]=1;
				}
			break;
			case SDL_KEYDOWN:
				if(e.key.keysym.sym==SDLK_w)
					input[0]=1;
				if(e.key.keysym.sym==SDLK_a)
					input[1]=1;
				if(e.key.keysym.sym==SDLK_s)
					input[2]=1;
				if(e.key.keysym.sym==SDLK_d)
					input[3]=1;
				if(e.key.keysym.sym==SDLK_SPACE)
					input[4]=1;
				if(e.key.keysym.sym==SDLK_LSHIFT)
					input[5]=1;
				if(e.key.keysym.sym==SDLK_UP)
					input[6]=1;
				if(e.key.keysym.sym==SDLK_DOWN)
					input[7]=1;
				if(e.key.keysym.sym==SDLK_LEFT)
					input[8]=1;
				if(e.key.keysym.sym==SDLK_RIGHT)
					input[9]=1;
				if(e.key.keysym.sym==SDLK_ESCAPE)
					input[10]=1;
			break;
			case SDL_KEYUP:
				if(e.key.keysym.sym==SDLK_w)
					input[0]=0;
				if(e.key.keysym.sym==SDLK_a)
					input[1]=0;
				if(e.key.keysym.sym==SDLK_s)
					input[2]=0;
				if(e.key.keysym.sym==SDLK_d)
					input[3]=0;
				if(e.key.keysym.sym==SDLK_SPACE)
					input[4]=0;
				if(e.key.keysym.sym==SDLK_LSHIFT)
					input[5]=0;
				if(e.key.keysym.sym==SDLK_UP)
					input[6]=0;
				if(e.key.keysym.sym==SDLK_DOWN)
					input[7]=0;
				if(e.key.keysym.sym==SDLK_LEFT)
					input[8]=0;
				if(e.key.keysym.sym==SDLK_RIGHT)
					input[9]=0;
				if(e.key.keysym.sym==SDLK_ESCAPE)
					input[10]=0;
			break;
			case SDL_WINDOWEVENT:
				if(e.window.event==SDL_WINDOWEVENT_RESIZED){
					width=e.window.data1;
					height=e.window.data2;
				}
			break;
		}
	}
	cam.rght=Vec3_norm(cam.rght);
	cam.fwd=Vec3_norm(cam.fwd);
	cam.up=Vec3_norm(cam.up);
	return cam;
}

#endif //INPUTHENDELER_H
