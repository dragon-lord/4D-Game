#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"

struct Texture3 test;
struct Vec2 poly[4]={{-1,-1},{1,-1},{1,1},{-1,1}};
struct Vec3 src[4]={{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};

void game(float fps){
  Render_mappedTexture3(test,poly,src,4);
}

int main(int argc,char **argv){

  if(!Render_init("Game",640,480)){
    Render_destroy();
    return -1;
  }

  test.w=200;
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
        test.pixels[test.w*test.h*k+test.w*j+i]=(int)creal(csqrt(20000-(x*x+y*y+z*z)));
      }
    }
  }

  /*test=Load_image("test_image.jpg");
  if(test.pixels==NULL){
    free(test.pixels);
    Render_destroy();
    return -1;
  }//*/

  while(!quit){
    Render_update(game);
    Input_update();
    //quit=1;
  }

  free(test.pixels);

  Render_destroy();
  return 0;
}
// a<<24 | r<<16 | g<<8 | b<<0
