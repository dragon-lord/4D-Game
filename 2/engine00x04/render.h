#ifndef RENDER_H
#define RENDER_H

#include<stdio.h>
#include<math.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL/SDL_opengl.h>
#include<SDL/SDL.h>

double width=640;
double height=480;
double swidth=640;
double sheight=480;

static SDL_Window* window;
//static SDL_Window* win;
static SDL_GLContext context;
static SDL_Surface* image;
static SDL_Renderer* render;
GLuint texture;
SDL_Event e;
int quit=0;

static double last=0.0;
static double now=0.0;
static float delta=1.0f;

int Render_init(char* title,int width,int height);
void Render_update(void(*update)(float));
void Render_reshape();
void Draw_triangle(short x[3],short y[3],Uint32 color);
void Draw_rect(short x[4],short y[4],Uint32 color);
void Draw_face(float verticies[10],int tex[2]);
void Draw_poly(short x[],short y[],int n,Uint32 color);
void Draw_pnt(float pnt[2],Uint32 color);
void Render_destroy();

#include"player.h"
#include"3d.h"

//IMPLIMENT

int Render_init(char* title,int width,int height){

	if (SDL_Init(SDL_INIT_VIDEO)){
		printf ("SDL_Init Error: %s", SDL_GetError());
		return 0;
	}
	window=SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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
	/*image=SDL_LoadBMP("brick.bmp");/*/
	image=SDL_LoadBMP("basictextures.bmp");//*/
	context=SDL_GL_CreateContext(window);
	if(image==NULL){
		printf("SDL_Error: %s\n",SDL_GetError());
	}
	glEnable(GL_TEXTURE_2D);
	//GLuint texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	//glTexImage2D(GL_TEXTURE_2D,0,image->format->BytesPerPixel,image->w,image->h,0,GL_RGB,GL_UNSIGNED_BYTE,image->pixels);
	glTexImage2D(GL_TEXTURE_2D,0,image->format->BytesPerPixel,image->w,image->h,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,image->pixels);

	//glOrtho(0,width,height,0,-1,1);
	glOrtho(0,width,0,height,-1,1);
	return 1;
}

void Render_update(void(*update)(float)){
	last=SDL_GetTicks();
	//SDL_SetRenderDrawColor(render,0,0,0,0);
	//SDL_RenderClear(render);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,height,0,-1,1);//*/
	//printf("%d,%d\n",width,height);
	/*while(SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT)
			quit=1;
	}//*/

	(*update)(delta);

	SDL_GL_SwapWindow(window);
	//SDL_RenderPresent(render);
	SDL_Delay(10);
	now=SDL_GetTicks();
	delta=(float)(now-last)*1.0f;
}

void Render_reshape(){
	glViewport(0,0,swidth,sheight);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0,width,0,height,-1,1);
	//glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
}

void Draw_triangle(short x[3],short y[3],Uint32 color){
	polygonColor(render,x,y,3,color);
}

void Draw_rect(short x[4],short y[4],Uint32 color){
	polygonColor(render,x,y,4,color);
}

void Draw_poly(short x[],short y[],int n,Uint32 color){
	polygonColor(render,x,y,n,color);
}

void Draw_pnt(float pnt[2],Uint32 color){
	short x[4]={(short)(pnt[0]-3),(short)(pnt[0]+3),(short)(pnt[0]+3),(short)(pnt[0]-3)};
	short y[4]={(short)(pnt[1]+3),(short)(pnt[1]+3),(short)(pnt[1]-3),(short)(pnt[1]-3)};
	filledPolygonColor(render,x,y,4,color);
}

/*void Draw_cube(FILE* farr,Uint32 color){
	for(int i=0;i<24;i++){
		int index[3]={CUBE[i][0],CUBE[i][1],CUBE[i][2]};
		int num[6]={0,0,0,0,0,0};
		fseek(farr,(index[0])*sizeof(int),SEEK_SET);
		fread(&num[0],sizeof(int),1,farr);
		fseek(farr,(index[1])*sizeof(int),SEEK_SET);
		fread(&num[1],sizeof(int),1,farr);
		fseek(farr,(index[2])*sizeof(int),SEEK_SET);
		fread(&num[2],sizeof(int),1,farr);
		fseek(farr,(14+index[0])*sizeof(int),SEEK_SET);
		fread(&num[3],sizeof(int),1,farr);
		fseek(farr,(14+index[1])*sizeof(int),SEEK_SET);
		fread(&num[4],sizeof(int),1,farr);
		fseek(farr,(14+index[2])*sizeof(int),SEEK_SET);
		fread(&num[5],sizeof(int),1,farr);
		short x[3]={(short)(num[0]),(short)(num[1]),(short)(num[2])};
		short y[3]={(short)(num[3]),(short)(num[4]),(short)(num[5])};
		filledPolygonColor(render,x,y,3,color);
	}
}//*/

void Draw_face(float verticies[10],int tex[2]){//,GLuint texture){
	int index=0;
	float d[8]={tex[0]*0.5,tex[1]*0.5, tex[0]*0.5+0.5,tex[1]*0.5, tex[0]*0.5+0.5,tex[1]*0.5+0.5, tex[0]*0.5,tex[1]*0.5+0.5};
	if(verticies[2]-verticies[0]==0){
		int a[3]={0,0,0};int b=0;int c=0;
		for(int i=0;i<3;i++){
			if(verticies[i*2+4]-verticies[0]>0){
				b++;
				a[i]=1;
			}else if(verticies[i*2+4]-verticies[0]==0){
				c=1;
			}
		}
		if(b==3 || b==0){
			index=0;
		}else if(c==1 && b!=1){
			index=0;
		}else{
			if(b==2){
				for(int i=0;i<3;i++){
					if(a[i]==0)
						index=i+1;
				}
			}else{
				for(int i=0;i<3;i++){
					if(a[i]==1)
						index=i+1;
				}
			}
		}
	}else{
		float m=(verticies[3]-verticies[1])/(verticies[2]-verticies[0]);
		int a[3]={0,0,0};int b=0;int c=0;
		for(int i=0;i<3;i++){
			if((verticies[i*2+4]-verticies[0])*m>verticies[i*2+5]-verticies[1]){
				b++;
				a[i]=1;
			}else if((verticies[i*2+4]-verticies[0])*m==verticies[i*2+5]-verticies[1]){
				c=1;
			}
		}
		if(b==3 || b==0){
			index=0;
		}else if(c==1 && b!=1){
			index=0;
		}else{
			if(b==2){
				for(int i=0;i<3;i++){
					if(a[i]==0)
						index=i+1;
				}
			}else{
				for(int i=0;i<3;i++){
					if(a[i]==1)
						index=i+1;
				}
			}
		}
	}
	int dir=0;
	if(index==0){
		float m1=(verticies[9]-verticies[1])/(verticies[8]-verticies[0]);
		float m2=(verticies[5]-verticies[1])/(verticies[4]-verticies[0]);
		int a1[4]={0,0,0,0};int a2[4]={0,0,0,0};int b=0;int c=0;
		for(int i=0;i<4;i++){
			if(i!=3){
				if((verticies[i*2+2]-verticies[0])*m1>verticies[i*2+3]-verticies[1]){
					c++;
					a1[i]=1;
				}
			}
			if(i!=1){
				if((verticies[i*2+2]-verticies[0])*m2>verticies[i*2+3]-verticies[1]){
					b++;
					a2[i]=1;
				}
			}
		}
		if(b==0 || b==3){
			dir=1;
		}else if((c==0 || c==3)!=1){
			float a1[2]={verticies[8]-verticies[0],verticies[9]-verticies[1]};
			float b1[2]={verticies[4]-verticies[0],verticies[5]-verticies[1]};
			if(sqrt(a1[0]*a1[0]+a1[1]*a1[1])>sqrt(b1[0]*b1[0]+b1[1]*b1[1]))
				dir=1;
		}
	}else if(index==3){
		float m1=(verticies[7]-verticies[1])/(verticies[6]-verticies[0]);
		float m2=(verticies[3]-verticies[1])/(verticies[2]-verticies[0]);
		int a1[4]={0,0,0,0};int a2[4]={0,0,0,0};int b=0;int c=0;
		for(int i=0;i<4;i++){
			if(i!=2){
				if((verticies[i*2+2]-verticies[0])*m1>verticies[i*2+3]-verticies[1]){
					c++;
					a1[i]=1;
				}
			}
			if(i!=0){
				if((verticies[i*2+2]-verticies[0])*m2>verticies[i*2+3]-verticies[1]){
					b++;
					a2[i]=1;
				}
			}
		}
		if(b==0 || b==3){
			dir=1;
		}else if((c==0 || c==3)!=1){
			float a1[2]={verticies[6]-verticies[0],verticies[7]-verticies[1]};
			float b1[2]={verticies[2]-verticies[0],verticies[3]-verticies[1]};
			if(sqrt(a1[0]*a1[0]+a1[1]*a1[1])>sqrt(b1[0]*b1[0]+b1[1]*b1[1]))
				dir=1;
		}
	}else{
		float m1=(verticies[index*2]-verticies[1])/(verticies[index*2]-verticies[0]);
		float m2=(verticies[index*2+5]-verticies[1])/(verticies[index*2+4]-verticies[0]);
		int a1[4]={0,0,0,0};int a2[4]={0,0,0,0};int b=0;int c=0;
		for(int i=0;i<4;i++){
			if(i!=index-1){
				if((verticies[i*2+2]-verticies[0])*m1>verticies[i*2+3]-verticies[1]){
					c++;
					a1[i]=1;
				}
			}
			if(i!=index+1){
				if((verticies[i*2+2]-verticies[0])*m2>verticies[i*2+3]-verticies[1]){
					b++;
					a2[i]=1;
				}
			}
		}
		if(b==0 || b==3){
			dir=1;
		}else if((c==0 || c==3)!=1){
			float a1[2]={verticies[index*2]-verticies[0],verticies[index*2]-verticies[1]};
			float b1[2]={verticies[index*2+4]-verticies[0],verticies[index*2+4]-verticies[1]};
			if(sqrt(a1[0]*a1[0]+a1[1]*a1[1])>sqrt(b1[0]*b1[0]+b1[1]*b1[1]))
				dir=1;
		}
	}
	if(dir==1){
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D,texture);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(tex[0]*0.5+0.25,tex[1]*0.5+0.25);
		glVertex3f(verticies[0],verticies[1],0);
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		index++;
		if(index==4)
			index=0;
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		index++;
		if(index==4)
			index=0;
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		index++;
		if(index==4)
			index=0;
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		index++;
		if(index==4)
			index=0;
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		glEnd();
	}else{
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D,texture);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(tex[0]*0.5+0.25,tex[1]*0.5+0.25);
		glVertex3f(verticies[0],verticies[1],0);
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		index--;
		if(index==-1)
			index=3;
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		index--;
		if(index==-1)
			index=3;
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		index--;
		if(index==-1)
			index=3;
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		index--;
		if(index==-1)
			index=3;
		glTexCoord2f(d[index*2],d[index*2+1]);
		glVertex3f(verticies[index*2+2],verticies[index*2+3],0);
		glEnd();
	}
}

void Render_destroy(){
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

#endif//RENDER_H
