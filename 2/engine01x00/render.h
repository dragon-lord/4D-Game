#ifndef RENDER_H
#define RENDER_H

#include<stdio.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL/SDL.h>

static SDL_Window* window;
//static SDL_Window* win;
static SDL_Renderer* render;
SDL_Event e;
int quit=0;

static double last=0.0;
static double now=0.0;
static float delta=1.0f;

double width=640;
double height=480;

int Render_init(char* title,int width,int height);
void Render_update(void(*update)(float));
void Draw_triangle(short x[3],short y[3],Uint32 color);
void Draw_rect(short x[4],short y[4],Uint32 color);
//void Draw_groundplane(struct Cam cam,Uint32 color);
void Render_destroy();

//IMPLIMENT

int Render_init(char* title,int width,int height){

	if (SDL_Init(SDL_INIT_VIDEO)){
		printf ("SDL_Init Error: %s", SDL_GetError());
		return 0;
	}
	window=SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_RESIZABLE);
	//win=SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_RESIZABLE);
	if(window==NULL){
		printf ("SDL_CreateWindow Error: %s",SDL_GetError());
		SDL_Quit();
		return 0;
	}
	render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(render==NULL){
		SDL_DestroyWindow(window);
		printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return 0;
	}
	return 1;
}

void Render_update(void(*update)(float)){
	//printf("%i,%i\n",SDL_GetWindowID(window),SDL_GetWindowID(win));
	last=SDL_GetTicks();
	SDL_SetRenderDrawColor(render,0,0,0,0);
	SDL_RenderClear(render);

	(*update)(delta);

	SDL_RenderPresent(render);

	SDL_Delay(10);
	now=SDL_GetTicks();
	delta=(float)(now-last)*1.0f;

	while(SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT)
			quit=1;
	}
}

void Draw_triangle(short x[3],short y[3],Uint32 color){
	filledPolygonColor(render,x,y,3,color);
}

void Draw_rect(short x[4],short y[4],Uint32 color){
	filledPolygonColor(render,x,y,4,color);
}

/*void Draw_groundplane(struct Cam cam,Uint32 color){
	short x[4];short y[4];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int i=-1;i<=1;i+=2){
		for(int j=-1;j<=1;j+=2){
			float temp[3]={100*i,-10,100*j};
			float* D2=D3(cam,Vec3_newv(temp,coord),i*2+j);
			if(i<0){
				if(j<0){
					x[1]=D2[0];
					y[1]=D2[1];
				}else{
					x[3]=D2[0];
					y[3]=D2[1];
				}
			}else{
				if(j<0){
					x[2]=D2[0];
					y[2]=D2[1];
				}else{
					x[0]=D2[0];
					y[0]=D2[1];
				}
			}
		}
	}
	filledPolygonColor(render,x,y,4,color);
}//
void Draw_groundplane(struct Cam cam,Uint32 color){
	short x[4];short y[4];
	float coord[3]={cam.x,cam.y,cam.z};
	x[0]=0;y[0]=height;
	x[1]=width;y[1]=height;
	x[2]=width;x[3]=0;
	float temp[3]={cam.fwd.x,-100,cam.fwd.z};
	float* D2=D3(cam,Vec3_newv(temp,coord),5);
	y[2]=D2[1];y[3]=D2[1];
	filledPolygonColor(render,x,y,4,color);
}//*/

void Render_destroy(){
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

#endif//RENDER_H
