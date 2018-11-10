#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"
#include "space.h"
#include "object.h"

struct Cam4 cam;
struct Vec4 poly[8]={{-1,-2,-1,-1},{-1,2,-1,-1},{-1,2,1,-1},{-1,-2,1,-1},{1,-2,1,-1},{1,2,1,-1},{1,2,-1,-1},{1,-2,-1,-1}};
struct Vec4 poly1[8]={{-1,2,-1,-1},{-1,2,-1,1},{-1,2,1,1},{-1,2,1,1},{1,2,1,1},{1,2,1,-1},{1,2,-1,-1},{1,2,-1,-1}};
struct Vec4 poly2[8]={{0,-1,-1,-1},{0,1,-1,-1},{0,1,1,-1},{0,-1,1,-1},{0,-1,1,1},{0,1,1,1},{0,1,-1,1},{0,-1,-1,1}};
int i=0;

void game(float fps){
  //Fill_poly(poly,0,4);
  //printf("%f\n",fps);
  Draw_wall4(cam,poly,0);
  Draw_wall4(cam,poly1,0);
  for(int i=0;i<8;i++){
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

  while(!quit){
    Cam4_update(&cam);
    Render_update(game);
    Input_update();
    //quit=1;
  }

  Render_destroy();
  return 0;
}
// a<<24 | r<<16 | g<<8 | b<<0
