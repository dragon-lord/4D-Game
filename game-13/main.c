#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"
#include "space.h"
#include "object.h"

struct Texture3 test;
struct Cam4 cam;
struct Vec3 poly3[4]={{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};
struct Vec4 poly[8]={{-1,-2,-1,-1},{-1,2,-1,-1},{-1,2,1,-1},{-1,-2,1,-1},{1,-2,1,-1},{1,2,1,-1},{1,2,-1,-1},{1,-2,-1,-1}};
struct Vec4 poly1[8]={{-1,2,-1,-1},{-1,2,-1,1},{-1,2,1,1},{-1,2,1,1},{1,2,1,1},{1,2,1,-1},{1,2,-1,-1},{1,2,-1,-1}};
struct Vec4 poly2[8]={{0,-1,-1,-1},{0,1,-1,-1},{0,1,1,-1},{0,-1,1,-1},{0,-1,1,1},{0,1,1,1},{0,1,-1,1},{0,-1,-1,1}};

void game(float fps){
  //Fill_poly(poly,0,4);
  //printf("%f\n",fps);
  if(ind>=1)
    ind=-1;
  ind+=0.01;
  //Draw_Wall3(cam,poly3,test);
  Draw_wall4(cam,poly,test);
  //Draw_wall4(cam,poly1,0);
  /*for(int i=0;i<8;i++){
    struct Vec3 vec=D4(cam,poly1[i]);
    if(vec.z>1)
      Fill_point(Vec2_new(vec.x,vec.y),i*30<<16,100/vec.z);
  }/*
  for(int i=0;i<8;i++){
    struct Vec4 p=Vec4_subv(poly[7-i],cam.pos);
    struct Vec3 vec=Vec3_new(Vec4_dot(p,cam.rght),Vec4_dot(p,Vec4_norm(Vec4_ortho2(cam.up,cam.fwd))),Vec4_dot(p,cam.fwd));
    if(vec.z>1)
      Fill_point(D3(Cam3_zero(),vec),(7-i)*30<<16,50/vec.z);
  }//*/
  //printf("(%f,%f,%f,%f)\n",cam.ana.w,cam.ana.x,cam.ana.y,cam.ana.z);
  //Fill_point(Vec2_new(1,0),0);
}

int main(int argc,char **argv){

  Render_init("Game",640,480);
  cam=Cam4_zero();
  cam.pos=Vec4_new(0,0,0,-2);

  test.w=200;
  test.h=200;
  test.d=200;
  test.pixels=malloc((test.d+1)*(test.w+1)*(test.h+1)*sizeof(Uint32));
  memset(test.pixels,9,(test.d+1)*(test.w+1)*(test.h+1)*sizeof(Uint32));/*/
  test.pixels=malloc((test.w+1)*(test.h+1)*sizeof(Uint32));
  memset(test.pixels,255<<16,(test.w+1)*(test.h+1)*sizeof(Uint32));//*/
  for(int i=0;i<=test.w;i++){
    for(int j=0;j<=test.h;j++){
      for(int k=0;k<=test.d;k++){
        int x=i-test.w/2;
        int y=j-test.h/2;
        int z=k-test.d/2;
        test.pixels[test.w*test.h*k+test.w*j+i]=(int)creal(csqrt(10000-(x*x+y*y+z*z)))*2;
        //if(test.pixels[test.w*test.h*k+test.w*j+i]!=0)printf("%i\n",test.pixels[test.w*test.h*k+test.w*j+i]);
      }/*/
      int x=i-test.w/2;
      int y=j-test.h/2;
      test.pixels[test.w*j+i]=(int)creal(csqrt(2000-(x*x+y*y)))*2;//*/
    }
  }

  while(!quit){
    Cam4_update(&cam);
    Render_update(game);
    Input_update();
    //quit=1;
  }

  free(test.pixels);

  Render_destroy();
  return 0;
}
// a<<24 | r<<16 | g<<8 | b<<0
