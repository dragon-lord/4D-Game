#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"
#include "space.h"
#include "object.h"

struct Cam4 cam;
struct Vec4 poly[8]={{-1,-2,-1,-1},{-1,2,-1,-1},{-1,2,1,-1},{-1,-2,1,-1},{1,-2,1,-1},{1,2,1,-1},{1,2,-1,-1},{1,-2,-1,-1}};
struct Vec4 poly1[8]={{1,2,-1,-1},{1,2,-1,-1},{1,2,1,1},{1,2,1,1},{4,2,1,1},{4,2,1,1},{4,2,-1,-1},{4,2,-1,-1}};
int i=0;

void game(float fps){
  //Fill_poly(poly,0,4);
  //printf("%f\n",fps);
  Draw_wall4(cam,poly,0);
  //Draw_wall4(cam,poly1,0);
  for(int i=0;i<8;i++){
    struct Vec3 vec=D4(cam,poly[i]);
    Fill_point(Vec2_new(vec.x,vec.y),0,10);
  }
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
