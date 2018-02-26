#ifndef D3_H
#define D3_H

float POINTS[14][3]={{-1,-1,-1},{-1,-1,1},{1,-1,1},{1,-1,-1},{-1,1,-1},{-1,1,1},{1,1,1},{1,1,-1},{0,0,-1},{1,0,0},{0,0,1},{-1,0,0},{0,-1,0},{0,1,0}};
float CUBE[24][3]={{0,1,8},{1,5,8},{5,4,8},{4,0,8},{1,2,9},{2,6,9},{6,5,9},{5,1,9},{2,3,10},{3,7,10},{7,6,10},{6,2,10},{3,1,11},{1,4,11},{4,7,11},{7,3,11},{0,1,12},{1,2,12},{2,3,12},{3,1,12},{4,5,13},{5,6,13},{6,7,13},{7,4,13}};
float EDGES[12][2]={{0,1},{0,3},{0,4},{1,2},{1,5},{2,3},{2,6},{3,7},{4,5},{4,7},{5,6},{6,7}};

#include <stdio.h>
#include <math.h>
#include "../math.h"
#include "player.h"
void Draw_triangle(short x[3],short y[3],Uint32 color);
void Draw_poly(short x[],short y[],int size,Uint32 color);
#include "render.h"

float* D3(struct Cam cam,struct Vec3 pnt,int i);
void Draw_cube(struct Cam cam,float pnt[3],Uint32 color);
void Draw_crossCube(struct Cam cam,float pnt[3],Uint32 color);

int draw=1;

//IMPLIMENT

/*float* D3(struct Cam cam,struct Vec3 pnt,int i){
	cam.fwd=Vec3_norm(cam.fwd);
	pnt=Vec3_norm(pnt);
	float theta=Vec3_angle(cam.fwd,pnt);
	if(theta>M_PI/2)
		draw=0;
	pnt=Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd);
	theta=Vec3_angle(cam.rght,pnt);
	if(Vec3_angle(cam.up,pnt)>M_PI/2)
		theta=-theta;
	float D2[2]={100*Vec3_length(pnt)*cos(theta)+(width/2),-100*Vec3_length(pnt)*sin(theta)+(height/2)};
	//if(i==2)
	//	printf("(%f,%f)\n",D2[0],D2[1]);
	return D2;
}/*/
float* D3(struct Cam cam,struct Vec3 pnt,int i){
	cam.fwd=Vec3_norm(cam.fwd);
	pnt=Vec3_norm(pnt);
	float theta=Vec3_angle(cam.fwd,pnt);
	float D2[2];
	float fov=5;
	//printf("%f\n",cos(M_PI/2-.01));
	float t=Vec3_angle(Vec3_newn(0,0,1),Vec3_newn(width,0,3*220));
	if(theta>t)
		draw=0;
	//if(i==0)
	//	printf("%f,%f,%f,%f\n",theta,cos(theta),1/cos(theta),M_PI/2);
	if(theta>M_PI/2-.1 && theta<M_PI/2+.1){
	//	printf("%f\n",cos(theta));
		theta=M_PI/2-.1;
	}
	if(theta>M_PI/2){
		pnt=Vec3_muln(Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd),fov);
		theta=Vec3_angle(cam.rght,pnt);
		if(Vec3_angle(cam.up,pnt)>M_PI/2)
			theta=-theta;
		D2[0]=-100*Vec3_length(pnt)*cos(theta)+(width/2);
		D2[1]=100*Vec3_length(pnt)*sin(theta)+(height/2);
	}else{
		pnt=Vec3_muln(Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd),fov);
		theta=Vec3_angle(cam.rght,pnt);
		if(Vec3_angle(cam.up,pnt)>M_PI/2)
			theta=-theta;
		D2[0]=100*Vec3_length(pnt)*cos(theta)+(width/2);
		D2[1]=-100*Vec3_length(pnt)*sin(theta)+(height/2);
	}
	//if(i==10)
	//	printf("(%f,%f,%f)\n",pnt.x,pnt.y,pnt.z);
	//	printf("(%f,%f)\n",D2[0],D2[1]);
	return D2;
}//*/

/*float* Cube(struct Cam cam,float pnt[3],int i){
	float D2[14][2];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int j=0;j<14;j++){
		//D2[j]=D3(cam,Vec3_newv(POINTS[i],coord),i);
	}
	//float[24][3][2] pt;
	for(int j=0;j<24;j++){
		//pt[j][
	}
}/*/
void Draw_cube(struct Cam cam,float pnt[3],Uint32 color){
	float arr[14][2];
	int d[14];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int i=0;i<14;i++){
		draw=1;
		float* D2=D3(cam,Vec3_newv(POINTS[i],coord),i);
		//printf("(%f,%f)\n",D2[0],D2[1]);
		arr[i][0]=D2[0];
		arr[i][1]=D2[1];
		if(draw==1){
			d[i]=1;
		}else{
			d[i]=0;
		}
	}
	int temp=0;
	for(int i=0;i<14;i++){
		//printf("%i",d[i]);
		if(d[i]==1)
			temp=1;
	}
	//printf("\n");
	if(temp==1){
		for(int i=0;i<24;i++){
			int index[3]={CUBE[i][0],CUBE[i][1],CUBE[i][2]};
			int num[6]={arr[index[0]][0],arr[index[1]][0],arr[index[2]][0],arr[index[0]][1],arr[index[1]][1],arr[index[2]][1]};
			short x[3]={(short)(num[0]),(short)(num[1]),(short)(num[2])};
			short y[3]={(short)(num[3]),(short)(num[4]),(short)(num[5])};
			Draw_triangle(x,y,color);
		}
	}
}//*/

void Draw_crossCube(struct Cam cam,float pnt[3],Uint32 color){
	/*struct Vec3 vec=Vec3_subv(Vec3_newn(cam.x,cam.y,cam.z),Vec3_newn(pnt[0],pnt[1],pnt[2]));
	if((Vec3_equal(cam.fwd,Vec3_norm(Vec3_cross(cam.rght,vec)))==1 || Vec3_equal(cam.fwd,Vec3_norm(Vec3_cross(cam.rght,vec)))==1)!=1){
		printf("1\n");
		//end;
	}//*/
	struct Vec3 zed=Vec3_newn(cam.x+pnt[0],cam.y+pnt[1],cam.z+pnt[2]);
	struct Vec3 up=Vec3_cross(cam.fwd,cam.rght);
	//printf("(%f,%f,%f)\n",cam.rght.x,cam.rght.y,cam.rght.z);
	float d=cam.fwd.x*zed.x+cam.fwd.y*zed.y+cam.fwd.z*zed.z;
	int e[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	int p[8];
	int pnts=0;
	int pos=0;
	int neg=0;
	int on=0;
	for(int i=0;i<8;i++){
		float r=cam.fwd.x*POINTS[i][0]+cam.fwd.y*POINTS[i][1]+cam.fwd.z*POINTS[i][2];
		if(r==d){
			on++;
			p[i]=0;
		}else if(r>d){
			pos++;
			p[i]=1;
		}else{
			neg++;
			p[i]=-1;
		}
		//printf("%i\n",p[i]);
	}
	//printf(" %i,%i,%i\n",on,pos,neg);
	for(int i=0;i<12;i++){
		int temp[2]={EDGES[i][0],EDGES[i][1]};
		if((p[temp[0]]==-1 && p[temp[1]]==1) || (p[temp[0]]==1 && p[temp[1]]==-1)){
			e[pnts]=i;
			pnts++;
		}
	}/*/
	for(int i=0;i<12;i++){
		int temp[2]={edges[i][0],edges[i][1]};
		if((p[temp[0]]==-1 && p[temp[1]]==1) || (p[temp[0]]==1 && p[temp[1]]==-1)){
			e[pnts]=i;
			pnts++;
		}
	}//*/
	int f[on];
	int g=0;
	for(int i=0;i<8;i++){
		if(p[i]==0){
			f[g]=i;
			g++;
		}
	}
	//struct Vec3 up=Vec3_ortho
	short x[pnts+on];
	short y[pnts+on];
	struct Vec2 points[pnts+on];
	for(int i=0;i<pnts;i++){
		int temp0=EDGES[e[i]][0];
		int temp1=EDGES[e[i]][1];
		struct Vec3 p0=Vec3_newn(POINTS[temp0][0],POINTS[temp0][1],POINTS[temp0][2]);
		struct Vec3 p1=Vec3_newn(POINTS[temp1][0],POINTS[temp1][1],POINTS[temp1][2]);
		//struct Vec3 pp=Vec3_addv(Vec3_subv(intersection(cam.fwd,Vec3_newn(cam.x,cam.y,cam.z),Vec3_subv(p0,p1),p0),Vec3_newn(cam.x,cam.y,cam.z)),Vec3_newn(pnt[0],pnt[1],pnt[2]));
		struct Vec3 pp=intersection3(cam.fwd,zed,Vec3_subv(p0,p1),p0);
		points[i]=Vec2_newn((width/2)+((Vec3_dot(pp,cam.rght)-Vec3_dot(zed,cam.rght))*100),(height/2)-((Vec3_dot(pp,up)-Vec3_dot(zed,up))*100));
		//printf("(%f,%f)\n",Vec3_dot(pp,cam.rght),Vec3_dot(pp,up));
		//printf("p0:(%f,%f,%f)\n p1:(%f,%f,%f)\n",p0.x,p0.y,p0.z,p1.x,p1.y,p1.z);
		//x[i]=(short)(points[i].x);
		//y[i]=(short)(points[i].y);
		//printf("%i:(%i,%i)\n",i,x[i],y[i]);
	}/*/
	struct Vec2 points[pnts+on];
	short x[pnts+on];
	short y[pnts+on];
	for(int i=0;i<pnts;i++){
		int temp=EDGES[e[i]][0];
		struct Vec3 p0=Vec3_newn(POINTS[temp][0]+pnt[0]-cam.x,POINTS[temp][1]+pnt[1]-cam.y,POINTS[temp][2]+pnt[2]-cam.z);
		temp=EDGES[e[i]][1];
		struct Vec3 vec=Vec3_subv(Vec3_newn(POINTS[temp][0]+pnt[0]-cam.x,POINTS[temp][1]+pnt[1]-cam.y,POINTS[temp][2]+pnt[2]-cam.z),p0);
		struct Vec3 pp=intersection(cam.fwd,Vec3_newn(cam.x,cam.y,cam.z),vec,p0);
		points[i]=Vec2_newn((width/2)+100*Vec3_dot(pp,cam.rght),(height/2)-(100*Vec3_dot(pp,cam.up)));
		printf("%i:(%i,%i)\n",i,x[i],y[i]);
	}/*/
	for(int i=0;i<on;i++){

		struct Vec3 pp=Vec3_newn(POINTS[f[i]][0],POINTS[f[i]][1],POINTS[f[i]][2]);
		points[i+pnts]=Vec2_newn((width/2)+(Vec3_dot(pp,cam.rght)*100),(height/2)-(Vec3_dot(pp,up)*100));
	}//*/
	points=convexHull(points,pnts+on);
	for(int i=0;i<pnts+on;i++){
		x[i]=(short)points[i].x;
		y[i]=(short)points[i].y;
	}
	Draw_poly(x,y,pnts,color);
}

#endif //D3_H
