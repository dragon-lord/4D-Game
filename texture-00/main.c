#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"

struct Texture test;
struct Vec2 poly[4]={{-1,-1},{1,-1},{1,1},{-1,1}};
struct Vec2 src[4]={{-1,-1},{1,-1},{1,1},{-1,1}};

void Render_texture(struct Texture image){
  for(int i=0;i<test.w;i++){
    for(int j=0;j<test.h;j++){
      pixels[width*j+i]=test.pixels[test.w*j+i];
    }
  }
}

void Render_mappedTexture(struct Texture image,struct Vec2 *poly,struct Vec2 *source,int n){
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
      //printf("%i,%i\n",indeces[i][0],indeces[i][1]);
      struct Vec2 sv1=Vec2_subv(src[indeces[i][1]],src[indeces[i][0]]);
      struct Vec2 sv2=Vec2_subv(src[indeces[i+1][1]],src[indeces[i+1][0]]);
      struct Vec2 dv1=Vec2_subv(pnts[indeces[i][1]],pnts[indeces[i][0]]);
      struct Vec2 dv2=Vec2_subv(pnts[indeces[i+1][1]],pnts[indeces[i+1][0]]);
      float d1=(Vec2_length(sv1)*(pixelY-pnts[indeces[i][0]].y))/(Vec2_length(dv1)*Vec2_norm(dv1).y);
      float d2=(Vec2_length(sv2)*(pixelY-pnts[indeces[i+1][0]].y))/(Vec2_length(dv2)*Vec2_norm(dv2).y);
      struct Vec2 vec=Vec2_divn(Vec2_subv(Vec2_muln(Vec2_norm(sv2),d2),Vec2_muln(Vec2_norm(sv1),d1)),nodeX[i+1]-nodeX[i]);
      for(int pixelX=nodeX[i];pixelX<nodeX[i+1];pixelX++){
        if((pixelX>width || pixelX<0 || pixelY>height || pixelY<0)!=1){
          struct Vec2 pnt=Vec2_addv(Vec2_muln(Vec2_norm(sv1),d1),Vec2_muln(vec,pixelX-nodeX[i]));
          printf("%f,%f\n",pnt.x,pnt.y);
          pixels[width*(height-pixelY)+pixelX]=image.pixels[image.w*(int)pnt.y+(int)pnt.x];
        }
      }
    }
  }
}

void game(float fps){
  Render_texture(test);
  Render_mappedTexture(test,poly,src,4);
}

int main(int argc,char **argv){

  if(!Render_init("Game",640,480)){
    Render_destroy();
    return -1;
  }

  test=Load_image("test_image-01.png");
  if(test.pixels==NULL){
    Render_destroy();
    return -1;
  }

  while(!quit){
    Render_update(game);
    Input_update();
  }

  free(test.pixels);

  Render_destroy();
  return 0;
}
// a<<24 | r<<16 | g<<8 | b<<0
