#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"

struct Texture test;
struct Vec2 poly[4]={{0,-0.5},{1,-1},{1,1},{0,0.5}};
struct Vec2 src[4]={{-1,-1},{1,-1},{1,1},{-1,1}};

void game(float fps){
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
