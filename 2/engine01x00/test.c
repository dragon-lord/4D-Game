#include<stdio.h>

#include"render.h"


short x[3];//a={width/3,2*width/3,width/2};
short y[3];//={height/2,height/2,height/4};
short rx[4]={0,0,100,100};
short ry[4]={0,100,100,0};
//int t=0;
//float triangle[3][3]={{-1,0,1},{1,0,1},{0,1,1}};
float triangle[4][3][3]={{{-1,0,1},{1,0,1},{0,1,0}},{{-1,0,1},{-1,0,-1},{0,1,0}},{{-1,0,-1},{1,0,-1},{0,1,0}},{{1,0,-1},{1,0,1},{0,1,0}}};
float rect[4][3]={{-5,-2,-5},{5,-2,-5},{5,-2,5},{-5,-2,5}};

void game(float delta){
	Draw_rect(rx,ry,0xFF0000FF);

}

int main(int argc, char* argv[]){
	Render_update(game);
	return 0;
}
