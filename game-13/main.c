#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"
#include "space.h"
#include "object.h"

struct Texture3 test;
struct Map2 map;
struct Cam2 cam;
struct Vec2 line[2]={{0,0},{0,0.1}};
struct Vec2 line2[2]={{-1,0},{1,0}};
struct Vec3 poly3[4]={{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};
struct Vec4 poly[8]={{-1,-2,-1,-1},{-1,2,-1,-1},{-1,2,1,-1},{-1,-2,1,-1},{1,-2,1,-1},{1,2,1,-1},{1,2,-1,-1},{1,-2,-1,-1}};
struct Vec4 poly1[8]={{-1,2,-1,-1},{-1,2,-1,1},{-1,2,1,1},{-1,2,1,1},{1,2,1,1},{1,2,1,-1},{1,2,-1,-1},{1,2,-1,-1}};
struct Vec4 poly2[8]={{0,-1,-1,-1},{0,1,-1,-1},{0,1,1,-1},{0,-1,1,-1},{0,-1,1,1},{0,1,1,1},{0,1,-1,1},{0,-1,-1,1}};

void game(float fps){
  //Draw_square3(cam,Vec3_new(0,0,0),0);
  //Draw_square2(cam,Vec2_new(0,0),0);
  Draw_cell2(cam,map);
  Render_line(line,0);
  Render_line(line2,0);
  Fill_point(Vec2_new(0,0),0,10);
}

int main(int argc,char **argv){

  Render_init("Game",640,480);
  cam=Cam2_zero();

  map=Map2_zero();
  map.cell[0].state[0]=0;
  map.cell[0].id[0]=1;
  map.cell[0].dst[0]=3;map.cell[0].dst[1]=2;
  map.cell=realloc(map.cell,2*sizeof(struct Cell2));
  map.cell[1].size=5;
  map.cell[1].Wall=malloc(5*sizeof(struct Vec2));
  memcpy(map.cell[1].Wall,(struct Vec2[5]){{-.6,-.2},{.2,-.2},{.2,.2},{-.2,.2},{-.6,.2}},5*sizeof(struct Vec2));
  map.cell[1].state=malloc(5*sizeof(int));
  memcpy(map.cell[1].state,(int[5]){1,1,0,1,1},5*sizeof(int));
  map.cell[1].id=calloc(5,5*sizeof(int));
  map.cell[1].dst=calloc(10,10*sizeof(int));
  map.cell[1].dst[4]=1;//*/

  /*test.w=200;
  test.h=200;
  test.d=200;
  test.pixels=malloc((test.d+1)*(test.w+1)*(test.h+1)*sizeof(Uint32));
  memset(test.pixels,9,(test.d+1)*(test.w+1)*(test.h+1)*sizeof(Uint32));
  for(int i=0;i<=test.w;i++){
    for(int j=0;j<=test.h;j++){
      for(int k=0;k<=test.d;k++){
        int x=i-test.w/2;
        int y=j-test.h/2;
        int z=k-test.d/2;
        test.pixels[test.w*test.h*k+test.w*j+i]=(int)creal(csqrt(10000-(x*x+y*y+z*z)))*2;
      }
    }
  }//*/

  while(!quit){
    Cam2_update(&cam,map);
    Render_update(game);
    Input_update();
    //quit=1;
  }

  free(test.pixels);
  Map2_free(map);

  Render_destroy();
  return 0;
}
// a<<24 | r<<16 | g<<8 | b<<0
