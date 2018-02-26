#ifndef MAP_H
#define MAP_H

#include<stdio.h>

#include"3d.h"
#include"../math.h"

struct block{
	int id;
	int x;
	int y;
	int z;
	float dist;
};

void Map3_load(struct Cam3 cam,FILE *map,int size[3]);

//IMPLIMENT

void Map3_load(struct Cam3 cam,FILE *map,int size[3]){
	int mapSize=0;
	struct block blocks[size[0]*size[1]*size[2]];
	for(int i=0;i<size[0];i++){
		for(int j=0;j<size[1];j++){
			for(int k=0;k<size[2];k++){
				int num;
				fseek(map,(size[0]*size[1]*k+size[0]*j+i)*sizeof(int),SEEK_SET);
				fread(&num,sizeof(int),1,map);
				if(num!=0){
					blocks[mapSize].x=i;
					blocks[mapSize].y=j;
					blocks[mapSize].z=k;
					blocks[mapSize].id=num;
					struct Vec3 vec=Vec3_subv(Vec3_newn(i,j,k),Vec3_newn((int)(cam.x+1)/2,(int)(cam.y+1)/2,(int)(cam.z+1)/2));
					blocks[mapSize].dist=Vec3_length(vec);
					//if(num>1)
					//	printf("%i:%f\n",num,blocks[mapSize].dist);
					mapSize++;
					/*float pnt[3]={i,j,k};
					int num0=0;
					if(num>2){
						num0=1;
						num-=2;
					}
					int tex[2]={num-1,num0};
					Draw_texturedCube(cam,pnt,tex);//*/
				}//*/
			}
		}
	}
	//printf("hi\n");
	int order[mapSize];
	double k[mapSize];
	for(int i=0;i<mapSize;i++){
		k[i]=(double)(blocks[i].dist);
		order[i]=i;
	}
	double temp;
	int tempr;
	for (int a = 0; a < mapSize-1; a++){
		for (int b = 0; b < mapSize-1; b++){
			if(k[b] < k[b + 1]){
				temp = k[b];
				tempr = order[b];
				order[b] = order[b + 1];
				k[b] = k[b + 1];

				order[b + 1] = tempr;
				k[b + 1] = temp;
			}
		}
	}
	for(int i=0;i<mapSize;i++){
		float pnt[3]={blocks[order[i]].x,blocks[order[i]].y,blocks[order[i]].z};
		int num=blocks[order[i]].id;
		int num0=0;
		if(num>2){
			num0=1;
			num-=2;
		}
		int tex[2]={num-1,num0};
		Draw_texturedCube(cam,pnt,tex,map,size);
	}
}

#endif //MAP_H
