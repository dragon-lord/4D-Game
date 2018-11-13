#ifndef SPACE_H
#define SPACE_H

#include<stdio.h>
#include<unistd.h>

#include "../math.h"

float fov=10;
int d=0;

#include "object.h"
#include "render.h"
#include "inputhandeler.h"

const struct Vec2 POINTS2[4]={{-1,-1},{-1,1},{1,1},{1,-1}};
//                            0           1         2         3         4       5         6       7
const struct Vec3 POINTS3[8]={{-1,-1,-1},{1,-1,-1},{-1,1,-1},{1,1,-1},{-1,-1,1},{1,-1,1},{-1,1,1},{1,1,1}};
const int FACE3[6][4]={{0,1,3,2},{0,1,5,4},{0,2,6,4},{1,3,7,5},{2,3,7,6},{4,5,7,6}};
const int WALL3[6][4]={{0,1,2,3},{0,1,5,4},{0,4,7,3},{1,5,6,2},{2,3,7,6},{4,5,6,7}};
const int WALL4[12][2]={{0,1},{1,2},{2,3},{3,0},{0,7},{7,4},{4,3},{4,5},{5,2},{5,6},{6,7},{6,1}};
//												0			1			2			3			4			5			6			7			8			9			10		11
struct Vec2 D3(struct Cam3 cam,struct Vec3 pnt);
struct Vec3 D4(struct Cam4 cam,struct Vec4 pnt);

void Draw_square2(struct Cam2 cam,struct Vec2 pnt,Uint32 color);
void Draw_square3(struct Cam3 cam,struct Vec3 pnt,Uint32 color);
void Draw_cube3(struct Cam3 cam,struct Vec3 pnt,Uint32 color);
void Draw_Wall3(struct Cam3 cam,struct Vec3 pnt[4],struct Texture2 texture);
void Draw_cuboid3(struct Cam3 cam,struct Vec3 pnt[8],Uint32 color);
void Draw_wall4(struct Cam4 cam,struct Vec4 pnt[8],struct Texture3 texture);

//IMPLIMENT

struct Vec2 D3(struct Cam3 cam,struct Vec3 pnt){
	if(Vec3_equal(cam.pos,pnt))
		return Vec2_new(0,0);
	struct Vec3 up=Vec3_norm(Vec3_ortho3(cam.up,cam.fwd,cam.rght));
  cam.fwd=Vec3_norm(cam.fwd);
	cam.rght=Vec3_norm(cam.rght);
	pnt=Vec3_norm(Vec3_subv(pnt,cam.pos));
  float dot=Vec3_dot(pnt,cam.fwd);
	if(Vec3_dot(pnt,cam.fwd)<0.1){
		d+=1;
		pnt=Vec3_addv(Vec3_muln(Vec3_ortho2(pnt,cam.fwd),8),Vec3_divn(cam.fwd,2));/*/Vec3_rot(Vec3_angle(cam.fwd,pnt)-M_PI*2/5,pnt,pnt,cam.fwd,0);//*/
	}
	pnt=Vec3_subv(Vec3_muln(pnt,(1/Vec3_dot(pnt,cam.fwd))),cam.fwd);
  //printf("(%f,%f):(%f,%f)\n",dot,1/dot,Vec3_dot(pnt,cam.rght),Vec3_dot(pnt,up));
	return Vec2_new(Vec3_dot(pnt,cam.rght),Vec3_dot(pnt,up));
}

struct Vec3 D4(struct Cam4 cam,struct Vec4 pnt){
	if(Vec4_equal(cam.pos,pnt))
		return Vec3_new(0,0,0);
	struct Vec4 up=Vec4_norm(Vec4_ortho4(cam.up,cam.fwd,cam.rght,cam.ana));
  cam.fwd=Vec4_norm(cam.fwd);
	cam.rght=Vec4_norm(cam.rght);
	pnt=Vec4_norm(Vec4_subv(pnt,cam.pos));
  float dot=Vec4_dot(pnt,cam.fwd);
	if(Vec4_dot(pnt,cam.fwd)<0.1){
		d+=1;
		pnt=Vec4_addv(Vec4_muln(Vec4_ortho2(pnt,cam.fwd),8),Vec4_divn(cam.fwd,2));/*/Vec3_rot(Vec3_angle(cam.fwd,pnt)-M_PI*2/5,pnt,pnt,cam.fwd,0);//*/
	}
	pnt=Vec4_subv(Vec4_muln(pnt,(1/Vec4_dot(pnt,cam.fwd))),cam.fwd);
  //printf("(%f,%f):(%f,%f)\n",dot,1/dot,Vec3_dot(pnt,cam.rght),Vec3_dot(pnt,up));
	return Vec3_new(Vec4_dot(pnt,cam.rght),Vec4_dot(pnt,up),Vec4_dot(pnt,cam.fwd));
}

void Draw_square2(struct Cam2 cam,struct Vec2 pnt,Uint32 color){
  float pnts[8];
  for(int i=0;i<4;i++){
    struct Vec2 vec=POINTS2[i];
    vec=Vec2_divn(Vec2_addv(Vec2_subv(vec,cam.pos),Vec2_muln(pnt,2)),fov);
    vec=Vec2_new(Vec2_dot(vec,cam.rght),Vec2_dot(vec,cam.up));
    pnts[i*2]=vec.x;
    pnts[i*2+1]=vec.y;
  }
  Render_poly(pnts,color,4);
}

void Draw_square3(struct Cam3 cam,struct Vec3 pnt,Uint32 color){
	int points[4]={0,1,3,2};
	struct Vec2 pnts[4];
	d=0;
	for(int i=0;i<4;i++){
		struct Vec2 vec=D3(cam,Vec3_addv(POINTS3[points[i]],pnt));
		pnts[i]=vec;
	}
	if(d!=4)
  	Fill_poly(pnts,color,4);
}

void Draw_cube3(struct Cam3 cam,struct Vec3 pnt,Uint32 color){
  int ds[8]={0};
  struct Vec2 points[8];
  struct Vec2 pnts[4];
  for(int i=0;i<8;i++){
    d=0;
    points[i]=D3(cam,Vec3_addv(POINTS3[i],pnt));
    ds[i]=d;
  }
  for(int i=0;i<6;i++){
    d=0;
    for(int j=0;j<4;j++){
      if(ds[j]==1)
        d++;
      pnts[j]=(points[FACE3[i][j]]);
    }
    if(d<4)
      Fill_poly(pnts,i*100,4);
  }//*/
}

void Draw_cuboid3(struct Cam3 cam,struct Vec3 pnt[8],Uint32 color){
  int ds[8]={0};
  struct Vec2 points[8];
  struct Vec2 pnts[4];
	for(int i=0;i<8;i++){
		d=0;
		points[i]=D3(cam,pnt[i]);
		ds[i]=d;
	}
  for(int i=0;i<6;i++){
    d=0;
    for(int j=0;j<4;j++){
      if(ds[j]==1)
        d++;
      pnts[j]=(points[WALL3[i][j]]);
    }
    if(d<4)
      Fill_poly(pnts,0,4);
  }
}

int test1[]={0,2,4,6};
int test2[]={7,8,10,11};

void Draw_wall4(struct Cam4 cam,struct Vec4 pnt[8],struct Texture3 texture){
	cam.fwd=Vec4_norm(cam.fwd);
	cam.rght=Vec4_norm(Vec4_ortho2(cam.rght,cam.fwd));
	cam.ana=Vec4_norm(Vec4_ortho3(cam.ana,cam.fwd,cam.rght));
	struct Vec4 up=Vec4_norm(Vec4_ortho4(cam.up,cam.fwd,cam.rght,cam.ana));
	float d=Vec4_dot(cam.ana,cam.pos);
	int nodes=0;
	struct Vec3 pnts[12];
	struct Vec4 pntz[8];
	int on=0;
	int ion[8]={0};
	int pos=0;
	int neg=0;
	int p[8]={0};
	for(int i=0;i<8;i++){
		float r=Vec4_dot(cam.ana,pnt[i]);
		if(r==d){
			ion[on++]=i;
		}if(r>d){
			pos++;
			p[i]=1;
		}if(r<d){
			neg++;
			p[i]=-1;
		}
		pntz[i]=Vec4_subv(pnt[i],cam.pos);
		//printf("%i:(%f,%f):%i\n",i,d,r,p[i]);
	}
	//printf(" %i,%i\n",pos,neg);
	if(pos==8)
		return;
	if(neg==8)
		return;
	if(on>0){
		for(int i=0;i<on;i++){
			pnts[nodes++]=Vec3_new(Vec4_dot(pntz[ion[i]],cam.rght),Vec4_dot(pntz[ion[i]],up),Vec4_dot(pntz[ion[i]],cam.fwd));
		}
	}
	int test=0;
	struct Vec3 src[12]={0};
	if(on<8){
		for(int i=0;i<12;i++){
			//printf("%f:%f,%f\n",d,r1,r2);

			/*struct Vec4 vec=Vec4_norm(Vec4_subv(pnt[WALL4[i][0]],pnt[WALL4[i][1]]));
			float T=(d-Vec4_dot(cam.ana,pnt[WALL4[i][0]]))/Vec4_dot(vec,cam.ana);
			vec=Vec4_addv(pntz[WALL4[i][0]],Vec4_muln(vec,T));
			struct Vec3 vec3=Vec3_new(Vec4_dot(vec,cam.rght),Vec4_dot(vec,up),Vec4_dot(vec,cam.fwd));
			if(vec3.z>1){
				Fill_point(D3(Cam3_zero(),vec3),100<<8,50/vec3.z);
			}//*/

			if(p[WALL4[i][0]]==1 && p[WALL4[i][1]]==-1 || p[WALL4[i][0]]==-1 && p[WALL4[i][1]]==1){
				if(nodes<4)
					if(test1[nodes]==i || test2[nodes]==i)
						test++;
				//printf("  %i\n",i);
				struct Vec4 vec=Vec4_subv(pnt[WALL4[i][0]],pnt[WALL4[i][1]]);
				float dist=Vec4_length(vec);
				vec=Vec4_norm(vec);
				float T=(d-Vec4_dot(cam.ana,pnt[WALL4[i][0]]))/Vec4_dot(vec,cam.ana);
				vec=Vec4_addv(pntz[WALL4[i][0]],Vec4_muln(vec,T));
				T=2*T/dist-1;
				switch(i){
					case 0: src[nodes]=Vec3_new(T,-1,-1);
					case 1: src[nodes]=Vec3_new(1,T,-1);
					case 2: src[nodes]=Vec3_new(-T,1,-1);
					case 3: src[nodes]=Vec3_new(-1,-T,-1);
					case 4: src[nodes]=Vec3_new(-1,-1,T);
					case 5: src[nodes]=Vec3_new(-1,T,1);
					case 6: src[nodes]=Vec3_new(-1,1,-T);
					case 7: src[nodes]=Vec3_new(T,1,1);
					case 8: src[nodes]=Vec3_new(1,1,-T);
					case 9: src[nodes]=Vec3_new(1,-T,1);
					case 10: src[nodes]=Vec3_new(-T,-1,1);
					case 11: src[nodes]=Vec3_new(1,-1,-T);
				}
				pnts[nodes++]=Vec3_new(Vec4_dot(vec,cam.rght),Vec4_dot(vec,up),Vec4_dot(vec,cam.fwd));//*/
			}
		}
	}
	//printf("   %i,%i\n",nodes,test);
	if(nodes<=1)
		return;
	if(nodes<=4){
		struct Vec2 pnts2[nodes];
		for(int i=0;i<nodes;i++){
			int j=i;
			if(test==4){
				if(j==0){
					j=1;
				}else if(j==1){
					j=0;
				}
			}
			pnts2[i]=D3(Cam3_zero(),pnts[j]);
			if(pnts[j].z>1){
				Fill_point(pnts2[i],i*63,(int)(50/pnts[j].z));
			}
		}
		if(test==4){
			struct Vec3 swap=src[0];
			src[0]=src[1];
			src[1]=swap;
		}
		Render_mappedTexture3(texture,pnts2,src,nodes);
		//Fill_poly(pnts2,0,nodes);
	}else{
		struct Face face[6];
		int nof;
		convexHull3(face,&nof,pnts,nodes);
		for(int i=0;i<nof;i++){
			struct Vec2 poly[face[i].size];
			for(int j=0;j<face[i].size;j++){
				poly[j]=D3(Cam3_zero(),pnts[face[i].f[j]]);
			}
			Fill_poly(poly,0,face[i].size);
		}
	}
}

//}
#endif//SPACE_H
