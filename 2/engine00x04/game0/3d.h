#ifndef D3_H
#define D3_H
#include <stdio.h>
#include <math.h>
#include "math.h"
#include "player.h"
#include "render.h"

float POINTS[14][3]={{-1,-1,-1},{-1,-1,1},{1,-1,1},{1,-1,-1},{-1,1,-1},{-1,1,1},{1,1,1},{1,1,-1},{0,0,-1},{1,0,0},{0,0,1},{-1,0,0},{0,-1,0},{0,1,0}};
float CUBE[24][3]={{0,3,8},{3,7,8},{7,4,8},{4,0,8},{2,3,9},{3,7,9},{7,6,9},{6,2,9},{1,2,10},{2,6,10},{6,5,10},{5,1,10},{0,1,11},{1,5,11},{5,4,11},{4,0,11},{0,1,12},{1,2,12},{2,3,12},{3,0,12},{4,5,13},{5,6,13},{6,7,13},{7,4,13}};
float CUBET[6][5]={{8,0,3,7,4},{9,2,3,7,6},{10,1,2,6,5},{11,0,1,5,4},{12,0,1,2,3},{13,4,5,6,7}};

float* D3(struct Cam cam,struct Vec3 pnt);
/*float* Cube(struct Cam cam,float pnt[3]);/*/
//float* intemediary(struct Cam cam, struct Vec3 pnt);
struct Vec3 intemediary(struct Cam cam,float pnt[3]);
void Draw_cube(struct Cam cam,float pnt[3],Uint32 color);
void Draw_texturedCube(struct Cam cam,float pnt[3],int tex[2],FILE *map,int size[3]);
//*/

int draw=1;

//IMPLIMENT0347

float* D3(struct Cam cam,struct Vec3 pnt){
	cam.fwd=Vec3_norm(cam.fwd);
	pnt=Vec3_norm(pnt);
	float theta=Vec3_angle(cam.fwd,pnt);
	float D2[2];
	float fov=5;
	if(theta>0.770015)
		draw=0;
	if(theta>M_PI/2-.1 && theta<M_PI/2+.1)
		theta=M_PI/2-.1;
	if(theta>M_PI/2){
		pnt=Vec3_muln(Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd),fov);
		theta=Vec3_angle(cam.rght,pnt);
		if(Vec3_angle(cam.up,pnt)>M_PI/2)
			theta=-theta;
		D2[0]=-100*Vec3_length(pnt)*cos(theta)+(width/2);
		D2[1]=-100*Vec3_length(pnt)*sin(theta)+(height/2);
	}else{
		pnt=Vec3_muln(Vec3_subv(Vec3_muln(pnt,1/cos(theta)),cam.fwd),fov);
		theta=Vec3_angle(cam.rght,pnt);
		if(Vec3_angle(cam.up,pnt)>M_PI/2)
			theta=-theta;
		D2[0]=100*Vec3_length(pnt)*cos(theta)+(width/2);
		D2[1]=100*Vec3_length(pnt)*sin(theta)+(height/2);
	}
	/*if(cam.shift==1){
		D2[1]+=100;
	}//*/
	return D2;
}

/*float* intemediary(struct Cam cam, struct Vec3 pnt){
	//pnt=Vec3_rot(pnt,cam.up,Vec3_angle(pnt,cam.fwd)*2/3);
	return D3(cam,pnt);
}//*/

struct Vec3 intemediary(struct Cam cam,float pnt0[3]){
	float coord[3]={cam.x,cam.y,cam.z};
	struct Vec3 pnt=Vec3_newv(pnt0,coord);

	if(pnt0[0]>5 && pnt0[0]<12 && pnt0[2]>10 && pnt0[2]<14){
		//pnt=Vec3_rot(pnt,Vec3_cross(cam.fwd,pnt),Vec3_angle(pnt,cam.fwd)*2/3);
		pnt0[0]=(pnt0[0]-5)/2+5;
	}

	pnt=Vec3_newv(pnt0,coord);
	printf("(%f,%f,%f)\n",cam.x,cam.y,cam.z);
	return pnt;
}

/*void Draw_cube(struct Cam cam,float pnt[3]){
	float coord[3]={cam.x,cam.y,cam.z};
	int arr[3]={1,1,1};
	for(int i=0;i<24;i++){
		for(int j=0;j<3;j++){
			draw=1;
			int k=CUBE[i][j];
			float* D2=D3(cam,Vec3_newv(POINTS[k],coord));
			x[i]=D2[0];
			y[i]=D2[1];
			if(draw==0){
				arr[i]=0;
			}else{
				arr[i]=1;
			}
		}
		if(arr[0]==1||arr[1]==1||arr[2]==1)
			Draw_triangle(x,y,0xFF00FFFF);
	}
}/*/
void Draw_cube(struct Cam cam,float pnt[3],Uint32 color){
	float arr[14][2];
	int d[14];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int i=0;i<14;i++){
		draw=1;
		float* D2=D3(cam,Vec3_newv(POINTS[i],coord));
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

void Draw_texturedCube(struct Cam cam,float pnt[3],int tex[2],FILE *map,int size[3]){
	float arr[14][2];
	int d[14];
	float coord[3]={cam.x,cam.y,cam.z};
	for(int i=0;i<14;i++){
		draw=1;
		float pnt1[3]={POINTS[i][0]+pnt[0]*2,POINTS[i][1]+pnt[1]*2,POINTS[i][2]+pnt[2]*2};
		float* D2=D3(cam,/*intemediary(cam,pnt1));/*/Vec3_newv(pnt1,coord));//*/
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
		/*for(int i=0;i<24;i++){
			int index[3]={CUBE[i][0],CUBE[i][1],CUBE[i][2]};
			int num[6]={arr[index[0]][0],arr[index[1]][0],arr[index[2]][0],arr[index[0]][1],arr[index[1]][1],arr[index[2]][1]};
			short x[3]={(short)(num[0]),(short)(num[1]),(short)(num[2])};
			short y[3]={(short)(num[3]),(short)(num[4]),(short)(num[5])};
			Draw_triangle(x,y,color);
		}//*/
		int e[3]={3,4,0};
		int num=0;
		if(cam.x>pnt[0]*2+1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]+1)*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[0]!=size[0]-1){
				e[0]=6;
			}else{
				e[0]=1;
			}
		}else if(cam.x<pnt[0]*2-1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]-1)*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[0]!=0){
				e[0]=6;
			}else{
				e[0]=3;
			}
		}else{e[0]=6;}
		if(cam.y>pnt[1]*2+1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]+size[0])*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[1]!=size[1]-1){
				e[1]=6;
			}else{
				e[1]=5;
			}
		}else if(cam.y<pnt[1]*2-1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]-size[0])*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[1]!=0){
				e[1]=6;
			}else{
				e[1]=4;
			}
		}else{e[1]=6;}
		if(cam.z>pnt[2]*2+1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]+size[0]*size[1])*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			//if(num==5&&pnt[2]==4)
			//	printf("hi\n");
			if(num!=0 && pnt[2]!=size[2]-1){
				e[2]=6;
			}else{
				e[2]=2;
			}
		}else if(cam.z<pnt[2]*2-1){
			fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0]-size[0]*size[1])*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,map);
			if(num!=0 && pnt[2]!=0){
				e[2]=6;
			}else{
				e[2]=0;
			}
		}else{e[2]=6;}
		/*if(tex[0]==1 && tex[1]==1){
			printf("p:(%f,%f,%f)\n",pnt[0],pnt[1],pnt[2]);
			printf("e:(%i,%i,%i)\n",e[0],e[1],e[2]);
		}//*/
		fseek(map,(size[0]*size[1]*pnt[2]+size[0]*pnt[1]+pnt[0])*sizeof(int),SEEK_SET);
		fread(&num,sizeof(int),1,map);
		//if(num==5)
		//	printf("%i:(%i,%i,%i),(%f,%f,%f)\n",num,e[0],e[1],e[2],pnt[0],pnt[1],pnt[2]);
		for(int i=0;i<3;i++){
			if(e[i]!=6){
				int index[5]={CUBET[e[i]][0],CUBET[e[i]][1],CUBET[e[i]][2],CUBET[e[i]][3],CUBET[e[i]][4]};
				float verticies[10]={
					arr[index[0]][0],arr[index[0]][1],
					arr[index[1]][0],arr[index[1]][1],
					arr[index[2]][0],arr[index[2]][1],
					arr[index[3]][0],arr[index[3]][1],
					arr[index[4]][0],arr[index[4]][1],
				};
				Draw_face(verticies,tex);//*/
			}
		}
	}
}

#endif //D3_H
