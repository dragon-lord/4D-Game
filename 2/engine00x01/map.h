#ifndef MAP_H
#define MAP_H

#include <stdio.h>

#include "../math.h"
#include "3d.h"

void Map3_load(struct Cam cam,FILE *map,int size[3]);

//IMPLIMENT

void Map3_load(struct Cam cam,FILE *map,int size[3]){
	for(int i=0;i<size[0];i++){
		for(int j=0;j<size[1];j++){
			int num;
			int pln[3];
			if(cam.fwd.z!=0){
				pln[0]=i;
				pln[1]=j;
				pln[2]=(cam.x*cam.fwd.x+cam.y*cam.fwd.y+cam.z*cam.fwd.z-j*cam.fwd.y-i*cam.fwd.x)/cam.fwd.z;
			}else if(cam.fwd.x!=0){
				pln[0]=(cam.x*cam.fwd.x+cam.y*cam.fwd.y+cam.z*cam.fwd.z-j*cam.fwd.y-i*cam.fwd.z)/cam.fwd.x;
				pln[1]=j;
				pln[2]=i;
			}
			if(pln[0]<=size[0] && pln[0]>=0 && pln[1]<=size[1] && pln[1]>=0 && pln[2]<=size[2] && pln[2]>=0){
				//printf("(%f,%f,%f),(%f,%f,%f)\n",cam.x,cam.y,cam.z,cam.fwd.x,cam.fwd.y,cam.fwd.z);
				fseek(map,(size[1]*size[0]*pln[2]+size[0]*pln[1]+pln[0])*sizeof(int),SEEK_SET);
				fread(&num,sizeof(int),1,map);
				if(num!=0){
					//printf("(%i,%i)\n",i,j);
					//if(num>1)
					//	printf("%i:%f\n",num,blocks[mapSize].dist);
					float pnt[3]={pln[0],pln[1],pln[2]};//={i*100+(width/2)+cam.x*100,j*-100+(height/2)+cam.y*100};
					printf("(%f,%f,%f)\n",pnt[0],pnt[1],pnt[2]);
					Draw_crossCube(cam,pnt,0xFF0000FF);//*/
				}
			}
		}
	}
}

#endif //MAP_H
