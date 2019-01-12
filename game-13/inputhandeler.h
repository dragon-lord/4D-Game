#ifndef INPUT_H
#define INPUT_H
#include<stdio.h>
#include<SDL2/SDL.h>
#include<string.h>

#include "../math.h"

int key[256]={0};
int mouse[10]={0};
int clicks=0;
struct Vec2 mpos;

#include"render.h"

void Input_update();

//IMPLIMENT

void Input_update(){
  while(SDL_PollEvent(&e)){
    if(e.type==SDL_QUIT){
      quit=1;
    }else if(e.type==SDL_KEYDOWN){
      if(e.key.keysym.sym<=256)
        key[e.key.keysym.sym]=1;
    }else if(e.type==SDL_KEYUP){
      if(e.key.keysym.sym<=256)
        key[e.key.keysym.sym]=0;
    }else if(e.type==SDL_MOUSEBUTTONDOWN){
      mouse[e.button.button]=1;
    }else if(e.type==SDL_MOUSEBUTTONUP){
      mouse[e.button.button]=0;
    }else if(e.type==SDL_MOUSEMOTION){
      mpos=Vec2_new(e.button.x,e.button.y);
    }
    clicks=e.button.clicks;
  }
}

#endif //INPUT_H
