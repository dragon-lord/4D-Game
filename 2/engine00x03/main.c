#include<stdio.h>

#include"render.h"
#include"player.h"
#include"3d.h"
#include"inputhandeler.h"
#include"map.h"

struct Cam3 cam3;
struct Cam4 cam4;
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
	/*float coord[3]={cam.x,cam.y,cam.z};
	int arr[4]={1,1,1,1};
	for(int i=0;i<4;i++){
		draw=1;
		float* D2=D3(cam,Vec3_newv(rect[i],coord));
		rx[i]=D2[0];
		ry[i]=D2[1];
		if(draw==0){
			arr[i]=0;
		}else{
			arr[i]=1;
		}
	}
	if(arr[0]==1||arr[1]==1||arr[2]==1||arr[3]==1)
		Draw_rect(rx,ry,0xFF0000FF);
	for(int j=0;j<4;j++){
		for(int i=0;i<3;i++){
			draw=1;
			float* D2=D3(cam,Vec3_newv(triangle[j][i],coord));
			x[i]=D2[0];
			y[i]=D2[1];
			if(draw==0){
				arr[i]=0;
			}else{
				arr[i]=1;
			}
		}
		if(arr[0]==1||arr[1]==1||arr[2]==1)
			Draw_triangle(x,y,0xFF00F0FF);
	}//*/
	/*farr=fopen("arr/arr.bin","wb+");
	float pnt[3]={0,0,0};
	Cube(farr,cam,pnt);
	Draw_cube(farr,0xFF0000FF);
	fclose(farr);//*/
	//float pnt[3]={0,0,0};
	//Draw_cube(cam,pnt,0xFF00F0FF);

	/*float coord[3]={cam3.x,cam3.y,cam3.z};
	float pnt1[3]={0,0,10};
	float* D2=D3(cam3,Vec3_newv(pnt1,coord));
	short x[4]={width/4,width*3/4,width*3/4,width/4};
	short y[4]={height*3/4,height*3/4,height/4,height/4};
	Draw_rect(x,y,0xFF00F0FF);
	printf("(%f,%f,%f)(%f,%f)\n",cam3.fwd.x,cam3.fwd.y,cam3.fwd.z,D2[0],D2[1]);//*/

	/*float verticies[10]={
		width/2+sin(ii)*width/2,height/2+cos(ii)*height/2,
		width/3,height/3,
		width*2/3,height/3,
		width*2/3,height*2/3,
		width/3,height*2/3
	};a
	ii+=0.1;

	printf("%f\n",ii);

	Draw_face(verticies);//,texture);//*/
	/*float pnt[3]={0,0,0};
	int tex[2]={0,0};
	Draw_texturedCube(cam,pnt,tex);//*/
	/*float pnt1[3]={1,0,0};
	int tex1[2]={1,0};
	Draw_texturedCube(cam,pnt1,tex1);//*/
	/*float pnt2[3]={2,0,0};
	int tex2[2]={1,1};
	Draw_texturedCube(cam,pnt2,tex2);//*/
	/*float pnt3[3]={3,0,0};
	int tex3[2]={0,1};
	Draw_texturedCube(cam,pnt3,tex3);//*/
	//printf("c:(%f,%f,%f)\n",cam.x/2,cam.y/2,cam.z/2);


	//int Map[5][5][5]={{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0}};
	//fwrite(Map,sizeof(int),(155),map);

	//Map3_load(cam,map,size);

	//float pnt[4]={0,0,0,0};
	//Draw_hyperCube(cam4,pnt,0xFF008000);
	/*/
	int tex[2]={0,0};
	Draw_texturedCube(cam,pnt,tex,map,size);//*/

	//printf("(%f,%f,%f,%f)\n",cam4.up.w,cam4.up.x,cam4.up.y,cam4.up.z);

	/*if((cam.z+1)/2>3 && (cam.z+1)/2<6 && (cam.x+1)/2>0 && (cam.x+1)/2<size[0]){
		cam.up=Vec3_newn(1,0,0);
	}else if((cam.z+1)/2>6 && (cam.z+1)/2<size[2] && (cam.x+1)/2>0 && (cam.x+1)/2<size[0]){
		cam.up=Vec3_norm(Vec3_newn(1,0,-1));
	}else{
		cam.up=Vec3_newn(0,1,0);
	}
	//*/

	/*x[0]=width/3;x[1]=width*2/3;x[2]=width/2;
	y[0]=height/3;y[1]=height/3;y[2]=height*2/3;
	Draw_triangle(x,y,0xFF00F0FF);//*/
	/*float verticies[10]={
		width/2,height/2,
		width/3,height/3,
		width*2/3,height/3,
		width*2/3,height*2/3,
		width/3,height*2/3
	};
	Draw_face(verticies);//*/
}

int main(int argc, char* argv[]){
	cam3=Cam3_new(0,0,0,Vec3_newn(0,0,1),Vec3_newn(1,0,0),Vec3_newn(0,1,0));
	//cam4=Cam4_new(0,0,0,0,Vec4_newn(0,0,0,1),Vec4_newn(1,0,0,0),Vec4_newn(0,1,0,0),Vec4_newn(0,0,1,0));
	if(!Render_init("Game",width,height)){
	return 1;
	}
	/*map=fopen("arr/map.bin","wb+");

	int Map[10][10][10][10];
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			for(int k=0;k<10;k++){
				for(int l=0;l<10;l++){
					Map[i][j][k][l]=0;
				}
			}
		}
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			Map[i][0][j][0]=1;
		}
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			Map[i][0][0][j]=2;
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

	fclose(map);/*/
	while(!quit){
		//map=fopen("arr/map.bin","rb+");
		Render_update(game);
		//cam3=Cam_update(cam3,map,size);
		//cam3=Cam3_update(cam3);
		//cam4=Cam4_update(cam4);
		//cam3=Input_update3(cam3);
		//cam4=Input_update4(cam4);
		//fclose(map);
	}//*/
	Render_destroy();
	return 0;
}
