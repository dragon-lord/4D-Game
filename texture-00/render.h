#ifndef RENDER_H
#define RENDER_H

#include<stdio.h>
#include<stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "../math.h"

struct Texture2{
  Uint32 *pixels;
  int w;
  int h;
};

struct Texture3{
  Uint32 *pixels;
  int w;
  int h;
  int d;
};

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
struct Texture2 Load_image(char *path);
void Render_update(void(*update)(float));
void Render_poly(float pnts[],Uint32 color,int n);
void Render_mappedTexture2(struct Texture2 image,struct Vec2 *poly,struct Vec2 *source,int n);
void Fill_poly(struct Vec2 poly[],Uint32 color,int n);
void Fill_point(struct Vec2 point,Uint32 color,int s);
void Render_destroy();

//IMPLIMENT

int Render_init(char *title,int w,int h){
  width=w;height=h;
  if(SDL_Init(SDL_INIT_VIDEO)<0){
    fprintf(stderr,"ERR SDL_Init: %s\n",SDL_GetError());
    return 0;
  }
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
    fprintf(stderr,"ERR IMG_Init: %s\n",IMG_GetError());
    return 0;
  }
  window=SDL_CreateWindow(title,
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_RESIZABLE);
  render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  screen=SDL_CreateTexture(render,
    SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STATIC,width,height);
  pixels=malloc(width*height*sizeof(Uint32));
  memset(pixels,100,width*height*sizeof(Uint32));
  return 1;
}

struct Texture2 Load_image(char *path){
  SDL_Surface* img=IMG_Load(path);
  struct Texture2 image;
  if(img==NULL){
    fprintf(stderr,"ERR IMG_Load: %s\n",IMG_GetError());
    image.pixels=NULL;
    return image;
  }
  img=SDL_ConvertSurfaceFormat(img,SDL_PIXELFORMAT_ARGB8888,0);
  image.w=img->w;
  image.h=img->h;
  image.pixels=malloc(img->w*img->h*sizeof(Uint32));
  memcpy(image.pixels,(Uint32*)img->pixels,img->w*img->h*sizeof(Uint32));
  SDL_FreeSurface(img);
  return image;
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

void Render_mappedTexture2(struct Texture2 image,struct Vec2 *poly,struct Vec2 *source,int n){
  int i=0;
  struct Vec2 pnts[n];
  struct Vec2 src[n];
  pnts[0].x=(int)(poly[0].x*(width/2)+(width/2));
  pnts[0].y=(int)(poly[0].y*(height/2)+(height/2));
  src[0].x=(int)(source[0].x*(image.w/2)+(image.w/2));
  src[0].y=(int)(source[0].y*(image.h/2)+(image.h/2));
  int top=pnts[0].y;
  int bottom=top;
  int right=pnts[0].x;
  int left=right;
  for(i=1;i<n;i++){
    pnts[i].x=(int)(poly[i].x*(width/2)+(width/2));
    pnts[i].y=(int)(poly[i].y*(height/2)+(height/2));
    src[i].x=(int)(source[i].x*(image.w/2)+(image.w/2));
    src[i].y=(int)(source[i].y*(image.h/2)+(image.h/2));
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
  int indeces[n][2];
  for(int pixelY=bottom;pixelY<=top;pixelY++){
    int nodes=0;
    int j=n-1;
    for(i=0;i<n;i++){
      if(pnts[i].y<(double)pixelY && pnts[j].y>=(double)pixelY
      ||  pnts[j].y<(double)pixelY && pnts[i].y>=(double)pixelY){
        nodeX[nodes++]=(int)(pnts[i].x+(pixelY-pnts[i].y)/(pnts[j].y-pnts[i].y)
        *(pnts[j].x-pnts[i].x));
        if(pnts[i].y<pnts[j].y){
          indeces[nodes-1][0]=i;
          indeces[nodes-1][1]=j;
        }else{
          indeces[nodes-1][0]=j;
          indeces[nodes-1][1]=i;
        }
      }
      j=i;
    }
    i=0;
    int swap[3];
    while(i<nodes-1){
      if(nodeX[i]>nodeX[i+1]){
        swap[0]=nodeX[i];
        nodeX[i]=nodeX[i+1];
        nodeX[i+1]=swap[0];
        swap[1]=indeces[i][0];
        swap[2]=indeces[i][1];
        indeces[i][0]=indeces[i+1][0];
        indeces[i][1]=indeces[i+1][1];
        indeces[i+1][0]=swap[1];
        indeces[i+1][1]=swap[2];
        if(i) i--;
      }else{
        i++;
      }
    }
    for(i=0;i<nodes;i+=2){
      if(nodeX[i]>=right) break;
      if(nodeX[i+1]<=left) break;
      if(nodeX[i]<left) nodeX[i]=left;
      if(nodeX[i+1]>right) nodeX[i+1]=right;
      struct Vec2 sv1=Vec2_subv(src[indeces[i][1]],src[indeces[i][0]]);
      struct Vec2 sv2=Vec2_subv(src[indeces[i+1][1]],src[indeces[i+1][0]]);
      struct Vec2 dv1=Vec2_subv(pnts[indeces[i][1]],pnts[indeces[i][0]]);
      struct Vec2 dv2=Vec2_subv(pnts[indeces[i+1][1]],pnts[indeces[i+1][0]]);
      float d1=(Vec2_length(sv1)*(pixelY-pnts[indeces[i][0]].y))/(Vec2_length(dv1)*Vec2_norm(dv1).y);
      float d2=(Vec2_length(sv2)*(pixelY-pnts[indeces[i+1][0]].y))/(Vec2_length(dv2)*Vec2_norm(dv2).y);
      struct Vec2 pnt2=Vec2_addv(Vec2_muln(Vec2_norm(sv2),d2),src[indeces[i+1][0]]);
      struct Vec2 pnt1=Vec2_addv(Vec2_muln(Vec2_norm(sv1),d1),src[indeces[i][0]]);
      struct Vec2 vec=Vec2_divn(Vec2_subv(pnt2,pnt1),nodeX[i+1]-nodeX[i]);
      for(int pixelX=nodeX[i];pixelX<nodeX[i+1];pixelX++){
        if((pixelX>width || pixelX<0 || pixelY>height || pixelY<0)!=1){
          struct Vec2 pnt=Vec2_addv(Vec2_addv(Vec2_muln(Vec2_norm(sv1),d1),src[indeces[i][0]]),Vec2_muln(vec,pixelX-nodeX[i]));
          if(pnt.x>image.w || pnt.x<0 || pnt.y>image.h || pnt.y<0){
            pixels[width*(height-pixelY)+pixelX]=0;
          }else{
            pixels[width*(height-pixelY)+pixelX]=image.pixels[image.w*(image.h-(int)pnt.y)+(int)pnt.x];
          }
        }
      }
    }
  }
}

void Render_mappedTexture3(struct Texture3 image,struct Vec2 *poly,struct Vec3 *source,int n){
  int i=0;
  struct Vec2 pnts[n];
  struct Vec3 src[n];
  pnts[0].x=(int)(poly[0].x*(width/2)+(width/2));
  pnts[0].y=(int)(poly[0].y*(height/2)+(height/2));
  src[0].x=(int)(source[0].x*(image.w/2)+(image.w/2));
  src[0].y=(int)(source[0].y*(image.h/2)+(image.h/2));
  src[0].z=(int)(source[0].z*(image.d/2)+(image.d/2));
  int top=pnts[0].y;
  int bottom=top;
  int right=pnts[0].x;
  int left=right;
  for(i=1;i<n;i++){
    pnts[i].x=(int)(poly[i].x*(width/2)+(width/2));
    pnts[i].y=(int)(poly[i].y*(height/2)+(height/2));
    src[i].x=(int)(source[i].x*(image.w/2)+(image.w/2));
    src[i].y=(int)(source[i].y*(image.h/2)+(image.h/2));
    src[i].z=(int)(source[i].z*(image.d/2)+(image.d/2));
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
  int indeces[n][2];
  for(int pixelY=bottom;pixelY<=top;pixelY++){
    int nodes=0;
    int j=n-1;
    for(i=0;i<n;i++){
      if(pnts[i].y<(double)pixelY && pnts[j].y>=(double)pixelY
      ||  pnts[j].y<(double)pixelY && pnts[i].y>=(double)pixelY){
        nodeX[nodes++]=(int)(pnts[i].x+(pixelY-pnts[i].y)/(pnts[j].y-pnts[i].y)
        *(pnts[j].x-pnts[i].x));
        if(pnts[i].y<pnts[j].y){
          indeces[nodes-1][0]=i;
          indeces[nodes-1][1]=j;
        }else{
          indeces[nodes-1][0]=j;
          indeces[nodes-1][1]=i;
        }
      }
      j=i;
    }
    i=0;
    int swap[3];
    while(i<nodes-1){
      if(nodeX[i]>nodeX[i+1]){
        swap[0]=nodeX[i];
        nodeX[i]=nodeX[i+1];
        nodeX[i+1]=swap[0];
        swap[1]=indeces[i][0];
        swap[2]=indeces[i][1];
        indeces[i][0]=indeces[i+1][0];
        indeces[i][1]=indeces[i+1][1];
        indeces[i+1][0]=swap[1];
        indeces[i+1][1]=swap[2];
        if(i) i--;
      }else{
        i++;
      }
    }
    for(i=0;i<nodes;i+=2){
      if(nodeX[i]>=right) break;
      if(nodeX[i+1]<=left) break;
      if(nodeX[i]<left) nodeX[i]=left;
      if(nodeX[i+1]>right) nodeX[i+1]=right;
      struct Vec3 sv1=Vec3_subv(src[indeces[i][1]],src[indeces[i][0]]);
      struct Vec3 sv2=Vec3_subv(src[indeces[i+1][1]],src[indeces[i+1][0]]);
      struct Vec2 dv1=Vec2_subv(pnts[indeces[i][1]],pnts[indeces[i][0]]);
      struct Vec2 dv2=Vec2_subv(pnts[indeces[i+1][1]],pnts[indeces[i+1][0]]);
      float d1=(Vec3_length(sv1)*(pixelY-pnts[indeces[i][0]].y))/(Vec2_length(dv1)*Vec2_norm(dv1).y);
      float d2=(Vec3_length(sv2)*(pixelY-pnts[indeces[i+1][0]].y))/(Vec2_length(dv2)*Vec2_norm(dv2).y);
      struct Vec3 pnt2=Vec3_addv(Vec3_muln(Vec3_norm(sv2),d2),src[indeces[i+1][0]]);
      struct Vec3 pnt1=Vec3_addv(Vec3_muln(Vec3_norm(sv1),d1),src[indeces[i][0]]);
      struct Vec3 vec=Vec3_divn(Vec3_subv(pnt2,pnt1),nodeX[i+1]-nodeX[i]);
      for(int pixelX=nodeX[i];pixelX<nodeX[i+1];pixelX++){
        if((pixelX>width || pixelX<0 || pixelY>height || pixelY<0)!=1){
          struct Vec3 pnt=Vec3_addv(Vec3_addv(Vec3_muln(Vec3_norm(sv1),d1),src[indeces[i][0]]),Vec3_muln(vec,pixelX-nodeX[i]));
          if(pnt.x>image.w || pnt.x<0 || pnt.y>image.h || pnt.y<0){
            pixels[width*(height-pixelY)+pixelX]=0;
          }else{
            pixels[width*(height-pixelY)+pixelX]=image.pixels[image.w*image.h*(int)pnt.z+image.w*(int)pnt.y+(int)pnt.x];
            //printf("(%i,%i):%i,%i -- (%f,%f,%f)\n",pixelY,pixelX,pixels[width*(height-pixelY)+pixelX],image.pixels[image.w*image.h*(int)pnt.z+image.w*(int)pnt.y+(int)pnt.x],pnt.x,pnt.y,pnt.z);
          }
        }
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
