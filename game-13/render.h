#ifndef RENDER_H
#define RENDER_H

#include<stdio.h>
#include<stdlib.h>

#include<SDL2/SDL.h>

#include "../math.h"

SDL_Renderer *render=NULL;
SDL_Texture *screen=NULL;
SDL_Window *window=NULL;
Uint32 *pixels=NULL;
SDL_Event e;

float frameTime=0;
int prevTime=0;
int currentTime=0;
float deltaTime=0;

int width=640,height=480;
int quit=0;

#include "inputhandeler.h"

int Render_init(char *title,int w,int h);
void Render_update(void(*update)(float));
void Render_poly(float pnts[],Uint32 color,int n);
void Fill_poly(struct Vec2 poly[],Uint32 color,int n);
void Fill_point(struct Vec2 point,Uint32 color,int s);
void Render_destroy();

//IMPLIMENT

int Render_init(char *title,int w,int h){
  width=w;height=h;
  SDL_Init(SDL_INIT_VIDEO);
  window=SDL_CreateWindow("Game",
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_RESIZABLE);
  render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  screen=SDL_CreateTexture(render,
    SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STATIC,width,height);
  pixels=malloc(width*height*sizeof(Uint32));
  memset(pixels,100,width*height*sizeof(Uint32));
  return 1;
}

void Render_update(void(*update)(float)){
  memset(pixels,100,width*height*sizeof(Uint32));
	prevTime=currentTime;
	currentTime=SDL_GetTicks();
	deltaTime=(currentTime-prevTime)/1000.0f;

	(*update)(1/deltaTime);

  SDL_UpdateTexture(screen,NULL,pixels,width*sizeof(Uint32));
  SDL_RenderClear(render);
  SDL_RenderCopy(render,screen,NULL,NULL);
  SDL_RenderPresent(render);
  SDL_Delay(10);
}

void Render_poly(float pnts[],Uint32 color,int n){
  pnts[0]=pnts[0]*width/2;
  pnts[1]=pnts[1]*height/2;
  for(int p=0;p<n;p++){
    int dx;
    int dy;
    if(isnormal(pnts[p*2]) && isnormal(pnts[p*2+1]) && isnormal(pnts[(p+1)*2]) && isnormal(pnts[(p+1)*2+1])
      && pnts[p*2]<1000 && pnts[p*2+1]<1000 && pnts[(p+1)*2]<1000 && pnts[(p+1)*2+1]<1000
      && pnts[p*2]>-1000 && pnts[p*2+1]>-1000 && pnts[(p+1)*2]>-1000 && pnts[(p+1)*2+1]>-1000){
      if(p<n-1){
        //printf("%i:(%f,%f),(%f,%f)\n",p,pnts[p*2]*2/width,pnts[p*2+1]*2/height,pnts[(p+1)*2],pnts[(p+1)*2+1]);
        pnts[(p+1)*2]=pnts[(p+1)*2]*width/2;
        pnts[(p+1)*2+1]=pnts[(p+1)*2+1]*height/2;
        dx=pnts[(p+1)*2]-pnts[p*2];
        dy=pnts[(p+1)*2+1]-pnts[p*2+1];
      }else{
        //printf("%i:(%f,%f),(%f,%f)\n",p,pnts[p*2]*2/width,pnts[p*2+1]*2/height,pnts[0]*2/width,pnts[1]*2/height);
        dx=pnts[0]-pnts[p*2];
        dy=pnts[1]-pnts[p*2+1];
      }
      float steps;
      if(abs(dx)>abs(dy))
        steps=abs(dx);
      else
        steps=abs(dy);
      float x_inc=dx/steps;
      float y_inc=dy/steps;
      //printf("  (%f,%f)\n",x_inc,y_inc);
      float x=pnts[p*2];
      float y=pnts[p*2+1];
      int k=(int)(x+width/2);
      int j=(int)(height/2-y);
      if(k<=width && j<=height && k>=0 && j>=0)
        pixels[k+j*width]=color;
      for(int i=1;i<steps && (k>width && x_inc>0 && j>height && y_inc>0 || k<0 && x_inc<0 && j<0 && y_inc<0)==0;i++){
        x+=x_inc;
        y+=y_inc;
        k=(int)(x+width/2);
        j=(int)(height/2-y);
        if(k<=width && j<=height && k>=0 && j>=0)
          pixels[k+j*width]=color;
      }
    }
  }
}

void Fill_poly(struct Vec2 poly[],Uint32 color,int n){
  int i=0;
  struct Vec2 pnts[n];
  pnts[0].x=(int)(poly[0].x*(width/2)+(width/2));
  pnts[0].y=(int)(poly[0].y*(height/2)+(height/2));
  int top=pnts[0].y;
  int bottom=top;
  int right=pnts[0].x;
  int left=right;
  for(i=1;i<n;i++){
    pnts[i].x=(int)(poly[i].x*(width/2)+(width/2));
    pnts[i].y=(int)(poly[i].y*(height/2)+(height/2));
    if(pnts[i].y>top)
      top=pnts[i].y;
    if(pnts[i].y<bottom)
      bottom=pnts[i].y;
    if(pnts[i].x>right)
      right=pnts[i].x;
    if(pnts[i].x<left)
      left=pnts[i].x;
  }
  if(right<0)
    return;
  if(left>width)
    return;
  if(bottom>height)
    return;
  if(top<0)
    return;
  if(bottom<0)
    bottom=0;
  if(top>height)
    top=height;
  if(right>width)
    right=width;
  if(left<0)
    left=0;
  int nodeX[n];
  for(int pixelY=bottom;pixelY<=top;pixelY++){
    int nodes=0;
    int j=n-1;
    for(i=0;i<n;i++){
      if(pnts[i].y<(double)pixelY && pnts[j].y>=(double)pixelY
      ||  pnts[j].y<(double)pixelY && pnts[i].y>=(double)pixelY){
        nodeX[nodes++]=(int)(pnts[i].x+(pixelY-pnts[i].y)/(pnts[j].y-pnts[i].y)
        *(pnts[j].x-pnts[i].x));
      }
      j=i;
    }
    i=0;
    int swap;
    while(i<nodes-1){
      if(nodeX[i]>nodeX[i+1]){
        swap=nodeX[i];
        nodeX[i]=nodeX[i+1];
        nodeX[i+1]=swap;
        if(i) i--;
      }else{
        i++;
      }
    }
    for(i=0;i<nodes;i+=2){
      if(nodeX[i]>=right) break;
      if(nodeX[i+1]>left){
        if(nodeX[i]<left) nodeX[i]=left;
        if(nodeX[i+1]>right) nodeX[i+1]=right;
        for(int pixelX=nodeX[i];pixelX<nodeX[i+1];pixelX++){
          if((pixelX>width || pixelX<0 || pixelY>height || pixelY<0)!=1)
            pixels[width*(height-pixelY)+pixelX]=color;
        }
      }
    }
  }
}

void Fill_point(struct Vec2 point,Uint32 color,int s){
  point.x=point.x*width/2+width/2;
  point.y=point.y*height/2+height/2;
  for(int i=-s;i<s;i++){
    int c=(int)sqrt(s*s-i*i);
    for(int j=-c;j<c;j++){
      int y=(int)(height-(point.y+i));
      int x=(int)(point.x+j);
      if(x<width && x>=0 && y<height && y>=0)
        pixels[(int)(width*y+x)]=color;
    }
  }
}

void Render_destroy(){
  free(pixels);
  SDL_DestroyTexture(screen);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

#endif//RENDER_H
