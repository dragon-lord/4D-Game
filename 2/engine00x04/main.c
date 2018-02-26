#include<stdio.h>

#include"render.h"
#include"player.h"
#include"3d.h"
#include"inputhandeler.h"
#include"map.h"

struct Cam4 cam;
FILE *map;
int size[3]={10,10,10};
float ii=0;
short x[3];
short y[3];
short rx[4];
short ry[4];
float triangle[4][3][3]={{{-1,0,1},{1,0,1},{0,1,0}},{{-1,0,1},{-1,0,-1},{0,1,0}},{{-1,0,-1},{1,0,-1},{0,1,0}},{{1,0,-1},{1,0,1},{0,1,0}}};
float rect[4][3]={{-5,-2,-5},{5,-2,-5},{5,-2,5},{-5,-2,5}};

void game(float delta){

	//Map3_load(cam,map,size);
	//float pnt[3]={0,0,4};
	//Draw_cube(cam,pnt,0xFF008000);
	float pnt[4]={0,0,0,0};
	Draw_hyperCube(cam,pnt,0xFF008000);
	//float pnt[2]={swidth/2,sheight/2};
	//Draw_pnt(pnt,0xFF008000);
	//printf("(%f,%f,%f,%f)\n",cam.w,cam.x,cam.y,cam.z);
	//printf(" (%f,%f,%f,%f)\n",cam.fwd.w,cam.fwd.x,cam.fwd.y,cam.fwd.z);

}

int main(int argc, char* argv[]){
	cam=Cam4_new(0,0,0,0,Vec4_newn(0,0,0,1),Vec4_newn(1,0,0,0),Vec4_newn(0,1,0,0),Vec4_newn(0,0,1,0));
	//cam=Cam3_new(0,0,0,Vec3_newn(0,0,1),Vec3_newn(1,0,0),Vec3_newn(0,1,0));
	if(!Render_init("Game",width,height)){
	return 1;
	}
	/*map=fopen("arr/map.bin","wb+");

	int Map[10][10][10];
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			for(int k=0;k<10;k++){
				Map[i][j][k]=0;
			}
		}
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			Map[i][0][j]=1;
		}
	}
	//for(int i=3;i<7;i++){
	//	for(int j=1;j<4;j++){
	//		Map[5][j][i]=2;
	//		Map[7][j][i]=2;
	//	}
	//	Map[6][3][i]=2;
	//}
	fwrite(Map,sizeof(int),(1000),map);
	//int size[3]={5,5,5};
	//Map3_load(cam,map,size);

	fclose(map);//*/
	while(!quit){
		map=fopen("arr/map.bin","rb+");
		Render_update(game);
		cam=Cam4_update(cam);
		cam=Input_update4(cam);
		fclose(map);
	}
	Render_destroy();
	return 0;
}
