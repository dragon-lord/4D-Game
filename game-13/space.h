#ifndef SPACE_H
#define SPACE_H

#include<stdio.h>
#include<unistd.h>

#include "../math.h"

float fov=10;
int d=0;
float ind=0;

#include "object.h"
#include "render.h"
#include "inputhandeler.h"

const struct Vec2 POINTS2[4]={{-1,-1},{1,-1},{1,1},{-1,1}};
//                            0           1         2         3         4       5         6       7
const struct Vec3 POINTS3[8]={{-1,-1,-1},{1,-1,-1},{-1,1,-1},{1,1,-1},{-1,-1,1},{1,-1,1},{-1,1,1},{1,1,1}};
const int FACE3[6][4]={{0,1,3,2},{0,1,5,4},{0,2,6,4},{1,3,7,5},{2,3,7,6},{4,5,7,6}};
const int WALL3[6][4]={{0,1,2,3},{0,1,5,4},{0,4,7,3},{1,5,6,2},{2,3,7,6},{4,5,6,7}};
const int WALL4[12][2]={{0,1},{1,2},{2,3},{3,0},{0,7},{7,4},{4,3},{4,5},{5,2},{5,6},{6,7},{6,1}};
//												0			1			2			3			4			5			6			7			8			9			10		11
struct Vec2 D3(struct Cam3 cam,struct Vec3 pnt);
struct Vec3 D4(struct Cam4 cam,struct Vec4 pnt);

void Draw_cell2(struct Cam2 cam,struct Map2 map);
void Draw_cell2other(struct Vec2 clip[2],struct Cam2 cam,struct Map2 map,int cell,int wall);
void Draw_square2(struct Cam2 cam,struct Vec2 pnt,Uint32 color);
void Draw_square3(struct Cam3 cam,struct Vec3 pnt,Uint32 color);
void Draw_cube3(struct Cam3 cam,struct Vec3 pnt,Uint32 color);
void Draw_cuboid3(struct Cam3 cam,struct Vec3 pnt[8],Uint32 color);
void Draw_Wall3(struct Cam3 cam,struct Vec3 pnt[4],struct Texture3 texture);
void Draw_wall4(struct Cam4 cam,struct Vec4 pnt[8],struct Texture3 texture);

//IMPLIMENT

struct Vec2 D3(struct Cam3 cam,struct Vec3 pnt){
	if(Vec3_equal(cam.pos,pnt))
		return Vec2_new(0,0);
	struct Vec3 up=Vec3_norm(Vec3_ortho3(cam.up,cam.fwd,cam.rght));
  cam.fwd=Vec3_norm(cam.fwd);
	cam.rght=Vec3_norm(cam.rght);
	pnt=Vec3_norm(Vec3_subv(pnt,cam.pos));
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
	if(Vec4_dot(pnt,cam.fwd)<0.1){
		d+=1;
		pnt=Vec4_addv(Vec4_muln(Vec4_ortho2(pnt,cam.fwd),8),Vec4_divn(cam.fwd,2));/*/Vec3_rot(Vec3_angle(cam.fwd,pnt)-M_PI*2/5,pnt,pnt,cam.fwd,0);//*/
	}
	pnt=Vec4_subv(Vec4_muln(pnt,(1/Vec4_dot(pnt,cam.fwd))),cam.fwd);
  //printf("(%f,%f):(%f,%f)\n",dot,1/dot,Vec3_dot(pnt,cam.rght),Vec3_dot(pnt,up));
	return Vec3_new(Vec4_dot(pnt,cam.rght),Vec4_dot(pnt,up),Vec4_dot(pnt,cam.fwd));
}

void Draw_cell2(struct Cam2 cam,struct Map2 map){
	if(cam.cell>map.size || cam.cell<0)
		return;
	struct Vec2 pnts[map.cell[cam.cell].size];
	int dp[map.cell[cam.cell].size];
	int dpp[map.cell[cam.cell].size];
	int dd=0;
	for(int i=0;i<map.cell[cam.cell].size;i++){
		pnts[i]=Vec2_subv(map.cell[cam.cell].Wall[i],cam.pos);
		if(Vec2_dot(cam.fwd,pnts[i])>=0){
			dp[dd++]=i;
			dpp[i]=1;
		}else{
			dpp[i]=0;
		}
	}
	for(int i=0;i<dd;i++){
		int l=dp[i]-1;
		if(dp[i]==0) l=map.cell[cam.cell].size-1;
		int m=dp[i]+1;
		if(dp[i]==map.cell[cam.cell].size-1) m=0;
		if(dpp[m]){
			if(map.cell[cam.cell].state[dp[i]]){
				Render_line((struct Vec2[2]){{Vec2_dot(cam.rght,pnts[dp[i]]),Vec2_dot(cam.fwd,pnts[dp[i]])},{Vec2_dot(cam.rght,pnts[m]),Vec2_dot(cam.fwd,pnts[m])}},0);
			}else{
				Draw_cell2other((struct Vec2[2]){pnts[dp[i]],pnts[m]},cam,map,map.cell[cam.cell].id[dp[i]],dp[i]);
			}
		}else{
			struct Vec2 vec=Vec2_norm(Vec2_subv(pnts[m],pnts[dp[i]]));
			float T=(0-Vec2_dot(pnts[dp[i]],cam.fwd))/Vec2_dot(vec,cam.fwd);
			vec=Vec2_addv(pnts[dp[i]],Vec2_muln(vec,T));
			if(map.cell[cam.cell].state[dp[i]]){
				Render_line((struct Vec2[2]){{Vec2_dot(cam.rght,pnts[dp[i]]),Vec2_dot(cam.fwd,pnts[dp[i]])},{Vec2_dot(cam.rght,vec),Vec2_dot(cam.fwd,vec)}},0);
			}else{
				//Draw_cell2other((struct Vec2[2]){pnts[dp[i]],vec},cam,map,map.cell[cam.cell].id[dp[i]],dp[i]);
			}
		}if(!dpp[l]){
			struct Vec2 vec=Vec2_norm(Vec2_subv(pnts[l],pnts[dp[i]]));
			float T=(0-Vec2_dot(pnts[dp[i]],cam.fwd))/Vec2_dot(vec,cam.fwd);
			vec=Vec2_addv(pnts[dp[i]],Vec2_muln(vec,T));
			if(map.cell[cam.cell].state[l]){
				Render_line((struct Vec2[2]){{Vec2_dot(cam.rght,pnts[dp[i]]),Vec2_dot(cam.fwd,pnts[dp[i]])},{Vec2_dot(cam.rght,vec),Vec2_dot(cam.fwd,vec)}},0);
			}else{
				Draw_cell2other((struct Vec2[2]){pnts[dp[i]],vec},cam,map,map.cell[cam.cell].id[l],l);
			}
		}
	}
}

void Draw_cell2other(struct Vec2 clip[2],struct Cam2 cam,struct Map2 map,int cell,int wall){
	if(cell>map.size || cell<0)
		return;
	struct Vec2 pnts[map.cell[cell].size];
	int dp[map.cell[cell].size];
	int dpp[map.cell[cell].size];
	int dd=0;
	struct Vec2 left;
	struct Vec2 rght;
	for(int i=0;i<map.cell[cell].size;i++){
		pnts[i]=Vec2_subv(map.cell[cell].Wall[i],cam.pos);
		if(Vec2_dot(cam.fwd,pnts[i])>=0){
			dp[dd++]=i;
			dpp[i]=1;
		}else{
			dpp[i]=0;
		}
	}
}

void Draw_square2(struct Cam2 cam,struct Vec2 pnt,Uint32 color){
  float pnts[8];
  for(int i=0;i<4;i++){
    struct Vec2 vec=POINTS2[i];
    vec=Vec2_divn(Vec2_addv(Vec2_subv(vec,cam.pos),Vec2_muln(pnt,2)),fov);
    vec=Vec2_new(Vec2_dot(vec,cam.rght),Vec2_dot(vec,cam.fwd));
    pnts[i*2]=vec.x;
    pnts[i*2+1]=vec.y;
  }
  Render_poly(pnts,color,4);
}

void Draw_square3(struct Cam3 cam,struct Vec3 pnt,Uint32 color){
	int points[4]={0,1,3,2};
	struct Vec2 pnts[5];
	struct Vec3 pnt3[4];
	float dot[4];
	d=0;
	for(int i=0;i<4;i++){
		pnt3[i]=Vec3_subv(Vec3_addv(POINTS3[points[i]],pnt),cam.pos);
		dot[i]=Vec3_dot(cam.fwd,pnt3[i]);
		if(dot[i]<1){
			d++;
		}
		printf("%i,%f\n",i,dot[i]);
	}
	printf("  %i\n",d);
	if(d!=4){
		struct Vec3 up=Vec3_ortho2(cam.up,cam.fwd);
		struct Vec3 vec;
		float T;
		int t=0;
		int f=0;
		for(int i=0;i<4;i++){
			if(dot[i]<.1 && f<2){
				int l=i-1;
				if(i==0) l=3;
				int m=i+1;
				if(i==3) m=0;
				if(d==1){
					vec=Vec3_subv(pnt3[l],pnt3[i]);
					T=(.1-Vec3_dot(pnt3[i],cam.fwd))/Vec3_dot(vec,cam.fwd);
					vec=Vec3_addv(pnt3[i],Vec3_muln(vec,T));
					printf(" %i,%f\n",i,Vec3_dot(vec,cam.fwd));
					vec=Vec3_subv(Vec3_divn(vec,Vec3_dot(vec,cam.fwd)),cam.fwd);
					pnts[t]=Vec2_new(Vec3_dot(vec,cam.rght),Vec3_dot(vec,cam.up));
					f++;
					t++;
					vec=Vec3_subv(pnt3[m],pnt3[i]);
					T=(.1-Vec3_dot(pnt3[i],cam.fwd))/Vec3_dot(vec,cam.fwd);
					vec=Vec3_addv(pnt3[i],Vec3_muln(vec,T));
					printf(" %i,%f\n",i+1,Vec3_dot(vec,cam.fwd));
					vec=Vec3_subv(Vec3_divn(vec,Vec3_dot(vec,cam.fwd)),cam.fwd);
					pnts[t]=Vec2_new(Vec3_dot(vec,cam.rght),Vec3_dot(vec,cam.up));
					t++;
					f++;
				}else if(d==2){
					if(dot[l]<.1){
						vec=Vec3_subv(pnt3[m],pnt3[i]);
						T=(.1-Vec3_dot(pnt3[i],cam.fwd))/Vec3_dot(vec,cam.fwd);
						printf("--%f:(%f,%f,%f),(%f,%f,%f)\n",Vec3_dot(vec,cam.fwd),vec.x,vec.y,vec.z,cam.fwd.x,cam.fwd.y,cam.fwd.z);
						vec=Vec3_addv(pnt3[i],Vec3_muln(vec,T));
						printf(" %i,%f	%f\n",i,Vec3_dot(vec,cam.fwd),T);
						vec=Vec3_subv(Vec3_divn(vec,Vec3_dot(vec,cam.fwd)),cam.fwd);
						pnts[t]=Vec2_new(Vec3_dot(vec,cam.rght),Vec3_dot(vec,cam.up));
						t++;
						f++;
					}else{
						vec=Vec3_subv(pnt3[l],pnt3[i]);
						T=(.1-Vec3_dot(pnt3[i],cam.fwd))/Vec3_dot(vec,cam.fwd);
						printf("--%f:(%f,%f,%f),(%f,%f,%f)\n",Vec3_dot(vec,cam.fwd),vec.x,vec.y,vec.z,cam.fwd.x,cam.fwd.y,cam.fwd.z);
						vec=Vec3_addv(pnt3[i],Vec3_muln(vec,T));
						printf(" %i,%f	%f\n",i,Vec3_dot(vec,cam.fwd),T);
						vec=Vec3_subv(Vec3_divn(vec,Vec3_dot(vec,cam.fwd)),cam.fwd);
						pnts[t]=Vec2_new(Vec3_dot(vec,cam.rght),Vec3_dot(vec,cam.up));
						t++;
						f++;
					}
				}else if(d==3){
					vec=Vec3_subv(pnt3[l],pnt3[i]);
					T=(.1-Vec3_dot(pnt3[i],cam.fwd))/Vec3_dot(vec,cam.fwd);
					vec=Vec3_addv(pnt3[i],Vec3_muln(vec,T));
					printf(" %i,%i,%f\n",t,i,Vec3_dot(vec,cam.fwd));
					vec=Vec3_subv(Vec3_divn(vec,Vec3_dot(vec,cam.fwd)),cam.fwd);
					pnts[t]=Vec2_new(Vec3_dot(vec,cam.rght),Vec3_dot(vec,cam.up));
					f++;
					t++;
					vec=Vec3_subv(pnt3[m],pnt3[i]);
					T=(.1-Vec3_dot(pnt3[i],cam.fwd))/Vec3_dot(vec,cam.fwd);
					vec=Vec3_addv(pnt3[i],Vec3_muln(vec,T));
					printf(" %i,%i,%f\n",t,i+1,Vec3_dot(vec,cam.fwd));
					vec=Vec3_subv(Vec3_divn(vec,Vec3_dot(vec,cam.fwd)),cam.fwd);
					pnts[t]=Vec2_new(Vec3_dot(vec,cam.rght),Vec3_dot(vec,cam.up));
					t++;
					f++;
				}
			}else if(dot[i]>=.1){
				vec=Vec3_subv(Vec3_divn(pnt3[i],dot[i]),cam.fwd);
				printf(" %i,%f\n",t,Vec3_dot(vec,cam.fwd));
				pnts[t]=Vec2_new(Vec3_dot(vec,cam.rght),Vec3_dot(vec,cam.up));
				t++;
			}
			if(d==3 && t>2)
				i=4;
		}
		if(d==0 || d==2)
			Fill_poly(pnts,color,4);
		else if(d==1)
			Fill_poly(pnts,color,5);
		else if(d==3)
			Fill_poly(pnts,color,3);
	}
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
      Fill_poly(pnts,color,4);
  }
}

void Draw_Wall3(struct Cam3 cam,struct Vec3 pnt[4],struct Texture3 texture){
	struct Vec2 pnts[4];
	struct Vec3 src[4];
	d=0;
	for(int i=0;i<4;i++){
		src[i]=Vec3_new(POINTS2[i].x,POINTS2[i].y,ind);
		pnts[i]=D3(cam,pnt[i]);
	}
	if(d<4)
		Render_mappedTexture3(texture,pnts,src,4);
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

			if((p[WALL4[i][0]]==1 && p[WALL4[i][1]]==-1) || (p[WALL4[i][0]]==-1 && p[WALL4[i][1]]==1)){
				if(nodes<4)
					if(test1[nodes]==i || test2[nodes]==i)
						test++;
				struct Vec4 vec=Vec4_subv(pnt[WALL4[i][1]],pnt[WALL4[i][0]]);
				float dist=Vec4_length(vec);
				vec=Vec4_norm(vec);
				float T=(d-Vec4_dot(cam.ana,pnt[WALL4[i][0]]))/Vec4_dot(vec,cam.ana);
				vec=Vec4_addv(pntz[WALL4[i][0]],Vec4_muln(vec,T));
				T=2*T/dist-1;
				switch(i){
					case 0: src[nodes]=Vec3_new(T,-1,-1);  break;
					case 1: src[nodes]=Vec3_new(1,T,-1);   break;
					case 2: src[nodes]=Vec3_new(-T,1,-1);  break;
					case 3: src[nodes]=Vec3_new(-1,-T,-1); break;
					case 4: src[nodes]=Vec3_new(-1,-1,T);  break;
					case 5: src[nodes]=Vec3_new(-1,T,1);   break;
					case 6: src[nodes]=Vec3_new(-1,1,-T);  break;
					case 7: src[nodes]=Vec3_new(T,1,1);    break;
					case 8: src[nodes]=Vec3_new(1,1,-T);   break;
					case 9: src[nodes]=Vec3_new(1,-T,1);   break;
					case 10: src[nodes]=Vec3_new(-T,-1,1); break;
					case 11: src[nodes]=Vec3_new(1,-1,-T); break;
				}
				pnts[nodes++]=Vec3_new(Vec4_dot(vec,cam.rght),Vec4_dot(vec,up),Vec4_dot(vec,cam.fwd));//*/
			}
		}
	}
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
