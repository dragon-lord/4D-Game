#ifndef OBJECT_H
#define OBJECT_H

#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"

struct Cam2{
  struct Vec2 pos;
  struct Vec2 up;
  struct Vec2 rght;
};

struct Cam3{
  struct Vec3 pos;
  struct Vec3 up;
  struct Vec3 rght;
  struct Vec3 fwd;
};

struct Cam4{
  struct Vec4 pos;
  struct Vec4 up;
  struct Vec4 rght;
  struct Vec4 fwd;
  struct Vec4 ana;
};

struct Cam2 Cam2_new(struct Vec2 pos,struct Vec2 up,struct Vec2 rght);
struct Cam3 Cam3_new(struct Vec3 pos,struct Vec3 up,struct Vec3 rght,struct Vec3 fwd);
struct Cam4 Cam4_new(struct Vec4 pos,struct Vec4 up,struct Vec4 rght,struct Vec4 fwd,struct Vec4 ana);
struct Cam2 Cam2_zero();
struct Cam3 Cam3_zero();
struct Cam4 Cam4_zero();
void Cam2_update(struct Cam2 *cam);
void Cam3_update(struct Cam3 *cam);
void Cam4_update(struct Cam4 *cam);

//IMPLIMENT


struct Cam2 Cam2_zero(){
  struct Cam2 cam={{0,0},{0,1},{1,0}};
  return cam;
}

struct Cam3 Cam3_zero(){
  struct Cam3 cam={{0,0,0},{0,1,0},{1,0,0},{0,0,1}};
  return cam;
}

struct Cam4 Cam4_zero(){
  struct Cam4 cam={{0,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,1},{1,0,0,0}};
  return cam;
}

void Cam2_update(struct Cam2 *cam){
 if(key['w']==1){
   cam->pos=Vec2_addv(cam->pos,Vec2_divn(cam->up,20));
 }if(key['s']==1){
   cam->pos=Vec2_subv(cam->pos,Vec2_divn(cam->up,20));
 }if(key['d']==1){
   cam->pos=Vec2_addv(cam->pos,Vec2_divn(cam->rght,20));
 }if(key['a']==1){
   cam->pos=Vec2_subv(cam->pos,Vec2_divn(cam->rght,20));
 }if(key[79]==1){
   cam->up=Vec2_rot(-0.05,cam->up);
 }if(key[80]==1){
   cam->up=Vec2_rot(0.05,cam->up);
 }/*if(key[81]==1){

 }if(key[82]==1){

 }//*/
 cam->up=Vec2_norm(cam->up);
 cam->rght=Vec2_norm(Vec2_ortho2(cam->rght,cam->up));
}

void Cam3_update(struct Cam3 *cam){
  struct Vec3 vec=Vec3_norm(Vec3_ortho2(cam->fwd,cam->up));
  if(key['w']==1){
    cam->pos=Vec3_addv(cam->pos,Vec3_divn(vec,20));
  }if(key['s']==1){
    cam->pos=Vec3_subv(cam->pos,Vec3_divn(vec,20));
  }if(key['d']==1){
    cam->pos=Vec3_addv(cam->pos,Vec3_divn(cam->rght,20));
  }if(key['a']==1){
    cam->pos=Vec3_subv(cam->pos,Vec3_divn(cam->rght,20));
  }if(key[79]==1){
    cam->fwd=Vec3_rot(0.02,cam->fwd,cam->fwd,cam->rght);
  }if(key[80]==1){
    cam->fwd=Vec3_rot(-0.02,cam->fwd,cam->fwd,cam->rght);
  }if(key[82]==1){
    //printf("1\n");
    if(Vec3_angle(cam->fwd,cam->up)<=2.8)
      cam->fwd=Vec3_rot(-0.02,cam->fwd,cam->fwd,cam->up);
  }if(key[81]==1){
    //printf("2\n");
    if(Vec3_angle(cam->fwd,cam->up)>=0.5)
      cam->fwd=Vec3_rot(0.02,cam->fwd,cam->fwd,cam->up);
  }
  //printf("%f\n",Vec3_angle(cam->fwd,cam->up));
  cam->up=Vec3_norm(cam->up);
  cam->fwd=Vec3_norm(cam->fwd);
  cam->rght=Vec3_norm(Vec3_ortho3(cam->rght,cam->fwd,cam->up));
}

void Cam4_update(struct Cam4 *cam){
  struct Vec4 vec=Vec4_norm(Vec4_ortho2(cam->fwd,cam->up));
  if(key['w']==1){
    cam->pos=Vec4_addv(cam->pos,Vec4_divn(vec,20));
  }if(key['s']==1){
    cam->pos=Vec4_subv(cam->pos,Vec4_divn(vec,20));
  }if(key['d']==1){
    cam->pos=Vec4_addv(cam->pos,Vec4_divn(cam->rght,20));
  }if(key['a']==1){
    cam->pos=Vec4_subv(cam->pos,Vec4_divn(cam->rght,20));
  }if(key['e']==1){
    cam->pos=Vec4_addv(cam->pos,Vec4_divn(cam->ana,20));
  }if(key['q']==1){
    cam->pos=Vec4_subv(cam->pos,Vec4_divn(cam->ana,20));
  }if(key['l']==1){
    cam->fwd=Vec4_rot(0.02,cam->fwd,cam->fwd,cam->rght);
  }if(key['j']==1){
    cam->fwd=Vec4_rot(-0.02,cam->fwd,cam->fwd,cam->rght);
  }if(key['o']==1){
    cam->fwd=Vec4_rot(0.02,cam->fwd,cam->fwd,cam->ana);
  }if(key['u']==1){
    cam->fwd=Vec4_rot(-0.02,cam->fwd,cam->fwd,cam->ana);
  }if(key['i']==1){
    if(Vec4_angle(cam->fwd,cam->up)<=2.8)
      cam->fwd=Vec4_rot(-0.02,cam->fwd,cam->fwd,cam->up);
  }if(key['k']==1){
    if(Vec4_angle(cam->fwd,cam->up)>=0.5)
      cam->fwd=Vec4_rot(0.02,cam->fwd,cam->fwd,cam->up);
  }
  cam->up=Vec4_norm(cam->up);
  cam->fwd=Vec4_norm(cam->fwd);
  cam->rght=Vec4_norm(Vec4_ortho3(cam->rght,cam->fwd,cam->up));
  cam->ana=Vec4_norm(Vec4_ortho4(cam->ana,cam->rght,cam->fwd,cam->up));
}

//}
#endif//OBJECT_H
