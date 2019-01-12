#ifndef OBJECT_H
#define OBJECT_H

#include<stdio.h>
#include<unistd.h>

#include "math.h"

#include "render.h"
#include "inputhandeler.h"

struct Cell2{
  int size;
  struct Vec2 *Wall;
  int *state;
  int *id;
  int *dst;
};

struct Map2{
  int size;
  struct Cell2 *cell;
};

struct Cam2{
  struct Vec2 pos;
  struct Vec2 fwd;
  struct Vec2 rght;
  int cell;
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

struct Cam2 Cam2_new(struct Vec2 pos,struct Vec2 fwd,struct Vec2 rght);
struct Cam3 Cam3_new(struct Vec3 pos,struct Vec3 up,struct Vec3 rght,struct Vec3 fwd);
struct Cam4 Cam4_new(struct Vec4 pos,struct Vec4 up,struct Vec4 rght,struct Vec4 fwd,struct Vec4 ana);
struct Map2 Map2_zero();
struct Cam2 Cam2_zero();
struct Cam3 Cam3_zero();
struct Cam4 Cam4_zero();
void Cam2_update(struct Cam2 *cam,struct Map2 map);
void Cam3_update(struct Cam3 *cam);
void Cam4_update(struct Cam4 *cam);
void Map2_free(struct Map2 map);

//IMPLIMENT


struct Map2 Map2_zero(){
  struct Map2 map;
  map.size=1;
  map.cell=malloc(sizeof(struct Cell2));
  map.cell->size=4;
  map.cell->Wall=malloc(4*sizeof(struct Vec2));
  memcpy(map.cell->Wall,(struct Vec2[4]){{-.2,-.2},{.2,-.2},{.2,.2},{-.2,.2}},4*sizeof(struct Vec2));
  map.cell->state=malloc(4*sizeof(int));
  memcpy(map.cell->state,(int[4]){1,1,1,1},4*sizeof(int));
  map.cell->id=calloc(4,4*sizeof(int));
  map.cell->dst=calloc(8,8*sizeof(int));
  return map;
}

struct Cam2 Cam2_zero(){
  struct Cam2 cam={{0,0},{0,1},{1,0},0};
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

void Cam2_update(struct Cam2 *cam,struct Map2 map){
  if(key['w']==1){
    cam->pos=Vec2_addv(cam->pos,Vec2_divn(cam->fwd,50));
  }if(key['s']==1){
    cam->pos=Vec2_subv(cam->pos,Vec2_divn(cam->fwd,50));
  }if(key['d']==1){
    cam->pos=Vec2_addv(cam->pos,Vec2_divn(cam->rght,50));
  }if(key['a']==1){
    cam->pos=Vec2_subv(cam->pos,Vec2_divn(cam->rght,50));
  }if(key['l']==1){
    cam->fwd=Vec2_rot(-0.05,cam->fwd);
  }if(key['j']==1){
    cam->fwd=Vec2_rot(0.05,cam->fwd);
  }/*if(key[81]==1){

  }if(key[82]==1){

  }//*/
  for(int i=0;i<map.cell[cam->cell].size;i++){
    //if(map.cell[cam->cell].state[i]==0) continue;
    int m=i+1;
    if(i==map.cell[cam->cell].size-1) m=0;
    struct Vec2 vec=Vec2_subv(map.cell[cam->cell].Wall[m],map.cell[cam->cell].Wall[i]);
    if(Vec2_dot(Vec2_subv(cam->pos,map.cell[cam->cell].Wall[i]),Vec2_norm(vec))-.02<=Vec2_length(vec) && Vec2_dot(Vec2_subv(cam->pos,map.cell[cam->cell].Wall[i]),Vec2_norm(vec))+.02>=0){
      struct Vec2 vec1=Vec2_norm(Vec2_ortho2(Vec2_subv(Vec2_new(0,0),map.cell[cam->cell].Wall[i]),vec));
      if(Vec2_dot(map.cell[cam->cell].Wall[i],vec1)>Vec2_dot(cam->pos,vec1)){
        printf("col:%i\n",i);
        if(map.cell[cam->cell].state[i]){
          cam->pos=Vec2_addv(cam->pos,Vec2_muln(vec1,Vec2_dot(map.cell[cam->cell].Wall[i],vec1)-Vec2_dot(cam->pos,vec1)));
        }else{
          struct Vec2 dst1=map.cell[map.cell[cam->cell].id[i]].Wall[map.cell[cam->cell].dst[i*2]];
          struct Vec2 dst2=map.cell[map.cell[cam->cell].id[i]].Wall[map.cell[cam->cell].dst[i*2+1]];
          float wl=(Vec2_dot(Vec2_subv(cam->pos,dst1),Vec2_norm(vec))/Vec2_length(vec))*Vec2_length(Vec2_subv(dst2,dst1));
          cam->pos=Vec2_addv(dst1,Vec2_muln(Vec2_norm(Vec2_subv(dst2,dst1)),wl));
          cam->cell=map.cell[cam->cell].id[i];
        }
      }
    }
  }
  //printf("%i\n",cam->cell);
  //printf(" %f,%f\n",cam->pos.x,cam->pos.y);
  cam->fwd=Vec2_norm(cam->fwd);
  cam->rght=Vec2_norm(Vec2_ortho2(cam->rght,cam->fwd));
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
    if(Vec3_angle(cam->fwd,cam->up)>=0.5)
      cam->fwd=Vec3_rot(0.02,cam->fwd,cam->fwd,cam->up);
  }if(key[81]==1){
    //printf("2\n");
    if(Vec3_angle(cam->fwd,cam->up)<=2.8)
      cam->fwd=Vec3_rot(-0.02,cam->fwd,cam->fwd,cam->up);
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
    if(Vec4_angle(cam->fwd,cam->up)>=0.5)
      cam->fwd=Vec4_rot(0.02,cam->fwd,cam->fwd,cam->up);
  }if(key['k']==1){
    if(Vec4_angle(cam->fwd,cam->up)<=2.8)
      cam->fwd=Vec4_rot(-0.02,cam->fwd,cam->fwd,cam->up);
  }
  cam->up=Vec4_norm(cam->up);
  cam->fwd=Vec4_norm(cam->fwd);
  cam->rght=Vec4_norm(Vec4_ortho3(cam->rght,cam->fwd,cam->up));
  cam->ana=Vec4_norm(Vec4_ortho4(cam->ana,cam->rght,cam->fwd,cam->up));
}

void Map2_free(struct Map2 map){
  for(int i=0;i<map.size;i++){
    free(map.cell[i].Wall);
    free(map.cell[i].state);
    free(map.cell[i].id);
  }
  free(map.cell);
}

//}
#endif//OBJECT_H
