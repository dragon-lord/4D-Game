#ifndef INPUTHANDELER_H
#define INPUTHENDELER_H

#include<stdio.h>
#include<SDL2/SDL2_gfxPrimitives.h>

#include"render.h"
#include"player.h"

struct Cam Input_update(struct Cam cam);

//IMPLEMENT
int input[11]={0,0,0,0,0,0,0};
int gui=1;
float mouse[2]={0,0};
float speed=0.1;

struct Cam Input_update(struct Cam cam){
	if(cam.grounded==1){
		struct Vec3 vec=Vec3_cross(cam.up,cam.rght);
		if(input[0]==1){
			cam.vel.x+=vec.x*speed;
			cam.vel.y+=vec.y*speed;
			cam.vel.z+=vec.z*speed;
		}
		if(input[1]==1){
			cam.vel.x-=cam.rght.x*speed;
			cam.vel.y-=cam.rght.y*speed;
			cam.vel.z-=cam.rght.z*speed;
		}
		if(input[2]==1){
			cam.vel.x-=vec.x*speed;
			cam.vel.y-=vec.y*speed;
			cam.vel.z-=vec.z*speed;
		}
		if(input[3]==1){
			cam.vel.x+=cam.rght.x*speed;
			cam.vel.y+=cam.rght.y*speed;
			cam.vel.z+=cam.rght.z*speed;
		}
		if(input[4]==1){
			cam.vel.x+=cam.up.x/2;
			cam.vel.y+=cam.up.y/2;
			cam.vel.z+=cam.up.z/2;
		}
	}
	if(input[5]==1){
		cam.shift=1;
		speed=0.02;
	}else{
		cam.shift=0;
		speed=0.05;
	}
	if(!gui){
		if(mouse[1]<0){
			if(Vec3_angle(cam.fwd,cam.up)<M_PI/8){}else{
				cam.fwd=Vec3_rot(cam.fwd,cam.rght,mouse[1]/-50);}
		}else{
			if(Vec3_angle(cam.fwd,cam.up)>7*M_PI/8){}else{
				cam.fwd=Vec3_rot(cam.fwd,cam.rght,mouse[1]/-50);}
		}
		cam.fwd=Vec3_rot(cam.fwd,cam.up,mouse[0]/-50);
		mouse[0]=0;
		mouse[1]=0;
	}
	if(input[6]==1){
		if(Vec3_angle(cam.fwd,cam.up)<M_PI/8){}else{
			cam.fwd=Vec3_rot(cam.fwd,cam.rght,0.05);}
	}
	if(input[7]==1){
		if(Vec3_angle(cam.fwd,cam.up)>7*M_PI/8){}else{
			cam.fwd=Vec3_rot(cam.fwd,cam.rght,-0.05);}
	}
	if(input[8]==1){
		cam.fwd=Vec3_rot(cam.fwd,cam.up,0.05);
	}
	if(input[9]==1){
		cam.fwd=Vec3_rot(cam.fwd,cam.up,-0.05);
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
		}
		input[10]=0;
	}
	while(SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT)
			quit=1;
		switch(e.type){
			case SDL_MOUSEMOTION:
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
					swidth=e.window.data1;
					sheight=e.window.data2;
					Render_reshape();
				}
			break;
		}
	}
cam.rght=Vec3_cross(cam.fwd,cam.up);
cam.fwd=Vec3_norm(cam.fwd);
cam.rght=Vec3_norm(cam.rght);
cam.up=Vec3_norm(cam.up);
return cam;
}

#endif //INPUTHENDELER_H
