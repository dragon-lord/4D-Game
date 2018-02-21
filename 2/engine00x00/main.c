#include<stdio.h>

#include"render.h"
#include"player.h"
#include"3d.h"
#include"inputhandeler.h"

struct Cam cam;
short x[3];//a={width/3,2*width/3,width/2};
short y[3];//={height/2,height/2,height/4};
short rx[4];
short ry[4];
//int t=0;
//float triangle[3][3]={{-1,0,1},{1,0,1},{0,1,1}};
float triangle[4][3][3]={{{-1,0,1},{1,0,1},{0,1,0}},{{-1,0,1},{-1,0,-1},{0,1,0}},{{-1,0,-1},{1,0,-1},{0,1,0}},{{1,0,-1},{1,0,1},{0,1,0}}};
float rect[4][3]={{-5,-2,-5},{5,-2,-5},{5,-2,5},{-5,-2,5}};

void game(float delta){
	//printf("%f\n",delta);
	/*if(t==0)x[1]+=1;
	if(t==1)x[1]-=1;
	if(x[1]>width)t=1;
	if(x[1]<0)t=0;//*/
	//float coord[3]={cam.x,cam.y,cam.z};
	/*draw=1;
	for(int i=0;i<3;i++){
		//printf("%d\n",triangle[i][0]);
		float* D2=D3(cam,Vec3_newv(triangle[i],coord),i);
		x[i]=D2[0];
		y[i]=D2[1];
	}
	if(draw==1)
		Draw_triangle(x,y,0xFF00FFFF);//*/
	//Draw_groundplane(cam,0xFF0000FF);
	/*int arr[4]={1,1,1,1};
	for(int i=0;i<4;i++){
		draw=1;
		float* D2=D3(cam,Vec3_newv(rect[i],coord),i);
		rx[i]=D2[0];
		ry[i]=D2[1];
		//printf("(%f,%f)\n",rx[i],ry[i]);
		if(draw==0){
			arr[i]=0;
		}else{
			arr[i]=1;
		}
	}
	//printf("(%i,%i,%i,%i)\n",arr[0],arr[1],arr[2],arr[3]);
	//printf("\n");
	if(arr[0]==1||arr[1]==1||arr[2]==1||arr[3]==1)
		Draw_rect(rx,ry,0xFF0000FF);
	for(int j=0;j<4;j++){
		for(int i=0;i<3;i++){
			draw=1;
			float* D2=D3(cam,Vec3_newv(triangle[j][i],coord),10);
			x[i]=D2[0];
			y[i]=D2[1];
			if(draw==0){
				arr[i]=0;
			}else{
				arr[i]=1;
			}
		}
		//printf("(%i,%i,%i)\n",arr[0],arr[1],arr[2]);
		if(arr[0]==1||arr[1]==1||arr[2]==1)
			Draw_triangle(x,y,0xFF00FFFF);//,0xFF0000FF);
	}//*/
	
	float pnt[3]={0,0,0};
	Draw_crossCube(cam,pnt,0xFF0000FF);
	
}

void game2(float delta){
	float pnt[3]={0,0,0};
	Draw_cube(cam,pnt,0xFF0000FF);
}

int main(int argc, char* argv[]){
	cam=Cam_new(0,0,0,Vec3_newn(0,0,1),Vec3_newn(1,0,0),Vec3_newn(0,1,0));
	if(!Render_init("Game",width,height)){
	return 1;
	}
	if(!Input_init()){
	return 1;
	}
	while(!quit){
		Render_update(game);
		//Render_update(game2,1);
		cam=Input_update(cam);
	}
	Render_destroy();
	return 0;
}
