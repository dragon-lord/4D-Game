#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "../math.h"

struct Cam3{
	int shift;
	int grounded;
	float x;
	float y;
	float z;
	struct Vec3 fwd;
	struct Vec3 rght;
	struct Vec3 up;
	struct Vec3 vel;
};

struct Cam4{
	int shift;
	int grounded;
	float w;
	float x;
	float y;
	float z;
	struct Vec4 fwd;
	struct Vec4 ana;
	struct Vec4 rght;
	struct Vec4 up;
	struct Vec4 vel;
};
int col[3];

struct Cam3 Cam3_new(float x,float y,float z,struct Vec3 fwd,struct Vec3 rght,struct Vec3 up);
struct Cam4 Cam4_new(float w,float x,float y,float z,struct Vec4 fwd,struct Vec4 ana,struct Vec4 rght,struct Vec4 up);
struct Cam3 Cam3_frm4(struct Cam4 cam4);
struct Cam4 Cam4_frm3(struct Cam3 cam3);
struct Cam4 Cam4_update(struct Cam4 cam);
struct Cam3 Cam3_update(struct Cam3 cam);
struct Cam3 Cam_update(struct Cam3 cam,FILE *map,int size[3]);

//IMPLIMENT

struct Cam3 Cam3_new(float x,float y,float z,struct Vec3 fwd,struct Vec3 rght,struct Vec3 up){
	struct Cam3 cam;
	cam.x=x;
	cam.y=y;
	cam.z=z;
	cam.fwd=fwd;
	cam.rght=rght;
	cam.up=up;
	cam.vel=Vec3_newn(0,-1,0);
	cam.shift=0;
	cam.grounded=1;
	for(int i=0;i<3;i++){
		col[i]=1;
	}
	return(cam);
}

struct Cam4 Cam4_new(float w,float x,float y,float z,struct Vec4 fwd,struct Vec4 ana,struct Vec4 rght,struct Vec4 up){
	struct Cam4 cam;
	cam.w=x;
	cam.x=x;
	cam.y=y;
	cam.z=z;
	cam.fwd=fwd;
	cam.ana=ana;
	cam.rght=rght;
	cam.up=up;
	cam.vel=Vec4_newn(0,0,0,0);
	cam.shift=0;
	cam.grounded=1;
	for(int i=0;i<3;i++){
		col[i]=1;
	}
	return(cam);
}

struct Cam3 Cam3_frm4(struct Cam4 cam4){
	struct Cam3 cam3;
	cam3.x=cam4.x;
	cam3.y=cam4.y;
	cam3.z=cam4.z;
	cam3.fwd=Vec3_newn(cam4.fwd.x,cam4.fwd.y,cam4.fwd.z);
	cam3.rght=Vec3_newn(cam4.rght.x,cam4.rght.y,cam4.rght.z);
	cam3.up=Vec3_newn(cam4.up.x,cam4.up.y,cam4.up.z);
	cam3.vel=Vec3_newn(0,-1,0);
	cam3.shift=0;
	cam3.grounded=1;
	return(cam3);
}

struct Cam4 Cam4_frm3(struct Cam3 cam3){
	struct Cam4 cam4;
	cam4.w=0;
	cam4.x=cam3.x;
	cam4.y=cam3.y;
	cam4.z=cam3.z;
	cam4.fwd=Vec4_newn(0,cam3.fwd.x,cam3.fwd.y,cam3.fwd.z);
	cam4.ana=Vec4_newn(0,0,0,0);
	cam4.rght=Vec4_newn(0,cam3.rght.x,cam3.rght.y,cam3.rght.z);
	cam4.up=Vec4_newn(0,cam3.up.x,cam3.up.y,cam3.up.z);
	cam4.vel=Vec4_newn(0,0,0,0);
	cam4.shift=0;
	cam4.grounded=1;
	return(cam4);
}

struct Cam4 Cam4_update(struct Cam4 cam){
	cam.w+=cam.vel.w;
	cam.x+=cam.vel.x;
	cam.y+=cam.vel.y;
	cam.z+=cam.vel.z;
	cam.vel=Vec4_divn(cam.vel,2);
	//printf("(%f,%f,%f,%f)\n",cam.vel.w,cam.vel.x,cam.vel.y,cam.vel.z);

	return cam;
}

struct Cam3 Cam3_update(struct Cam3 cam){
	cam.x+=cam.vel.x;
	cam.y+=cam.vel.y;
	cam.z+=cam.vel.z;
	cam.vel=Vec3_divn(cam.vel,2);
	//printf("(%f,%f,%f)\n",cam.vel.x,cam.vel.y,cam.vel.z);

	return cam;
}

struct Cam3 Cam_update(struct Cam3 cam,FILE *map,int size[3]){
	int x=(int)(cam.x+1)/2;
	int y=(int)(cam.y+1)/2;
	int z=(int)(cam.z+1)/2;
	struct Vec3 vec=Vec3_subv(Vec3_newn(cam.x,cam.y,cam.z),Vec3_muln(cam.up,2));
	int x1=(int)(vec.x+1)/2;
	int y1=(int)(vec.y+1)/2;
	int z1=(int)(vec.z+1)/2;
	if((int)cam.x>=0 && (int)cam.z>=0 && x<size[0] && z<size[2]){
		int num[6];
		//*if(cam.y>-10 && cam.y<50){
		//	cam.y+=cam.vel.y;
		//}else{cam.grounded=1;}///
		if(cam.y<0 || (cam.y+1)/2>size[1]){
			cam.x+=cam.vel.x;
			cam.z+=cam.vel.z;
			if(cam.y>-10 && cam.y<100){
				cam.y+=cam.vel.y;
			}else{cam.grounded=1;}
		}else{
			fseek(map,(size[0]*size[1]*z+size[0]*y+(x+1))*sizeof(int),SEEK_SET);
			fread(&num[0],sizeof(int),1,map);
			if(num[0]==0){
				fseek(map,(size[0]*size[1]*z1+size[0]*y1+(x1+1))*sizeof(int),SEEK_SET);
				fread(&num[0],sizeof(int),1,map);
			}
			fseek(map,(size[0]*size[1]*z+size[0]*y+(x-1))*sizeof(int),SEEK_SET);
			fread(&num[1],sizeof(int),1,map);
			if(num[1]==0){
				fseek(map,(size[0]*size[1]*z1+size[0]*y1+(x1-1))*sizeof(int),SEEK_SET);
				fread(&num[1],sizeof(int),1,map);
			}
			fseek(map,(size[0]*size[1]*(z+1)+size[0]*y+x)*sizeof(int),SEEK_SET);
			fread(&num[2],sizeof(int),1,map);
			if(num[2]==0){
				fseek(map,(size[0]*size[1]*(z1+1)+size[0]*y1+x1)*sizeof(int),SEEK_SET);
				fread(&num[2],sizeof(int),1,map);
			}
			fseek(map,(size[0]*size[1]*(z-1)+size[0]*y+x)*sizeof(int),SEEK_SET);
			fread(&num[3],sizeof(int),1,map);
			if(num[3]==0){
				fseek(map,(size[0]*size[1]*(z1-1)+size[0]*y1+x1)*sizeof(int),SEEK_SET);
				fread(&num[3],sizeof(int),1,map);
			}
			fseek(map,(size[0]*size[1]*z+size[0]*(y+1)+x)*sizeof(int),SEEK_SET);
			fread(&num[4],sizeof(int),1,map);
			if(num[4]==0){
				fseek(map,(size[0]*size[1]*z+size[0]*(y+1)+x)*sizeof(int),SEEK_SET);
				fread(&num[4],sizeof(int),1,map);
			}
			fseek(map,(size[0]*size[1]*z+size[0]*(y-1)+x)*sizeof(int),SEEK_SET);
			fread(&num[5],sizeof(int),1,map);
			if(num[5]==0){
				fseek(map,(size[0]*size[1]*z1+size[0]*(y1-1)+x1)*sizeof(int),SEEK_SET);
				fread(&num[5],sizeof(int),1,map);
			}
			if(x+1>=size[0]){
				num[0]=0;
			}else if(x-1<0){
				num[1]=0;
			}if(z+1>=size[2]){
				num[2]=0;
			}else if(z-1<0){
				num[3]=0;
			}if(y+1>=size[1]){
				num[4]=0;
			}else if(y-1<0){
				num[5]=0;
			}
			if((cam.vel.x>0 && num[0]==0 /*|| cam.x/2-x<-0.1*/)==1 || (cam.vel.x<0 && num[1]==0 /*|| cam.x/2-x>0.1*/)==1){
				cam.x+=cam.vel.x;
				col[0]=0;
			}else if(cam.vel.x>0){
				cam.x=x*2;
				col[0]=1;
			}else if(cam.vel.x<0){
				cam.x=x*2;
				col[0]=1;
			}
			if((cam.vel.y>0 && num[4]==0 /*|| cam.y/2-y<-0.1*/)==1 || (cam.vel.y<0 && num[5]==0 /*|| cam.y/2-y>0.1*/)==1){
				cam.y+=cam.vel.y;
				col[1]=0;
			}else if(cam.vel.y>0){
				cam.y=y*2;
				col[1]=1;
			}else if(cam.vel.y<0){
				cam.y=y*2;
				col[1]=1;
			}
			if((cam.vel.z>0 && num[2]==0 /*|| cam.z/2-z<-0.1*/)==1 || (cam.vel.z<0 && num[3]==0 /*|| cam.z/2-z>0.1*/)==1){
				cam.z+=cam.vel.z;
				col[2]=0;
			}else if(cam.vel.z>0){
				cam.z=z*2;
				col[2]=1;
			}else if(cam.vel.z<0){
				cam.z=z*2;
				col[2]=1;
			}
			if(col[0]==1 || col[1]==1 || col[2]==1){
				cam.grounded=1;
			}else{
				cam.grounded=0;
			}

		}
		if(cam.grounded==1){
			cam.vel=Vec3_divn(cam.vel,1.1);
			if(cam.shift==1){// && cam.y/2-y>=0){
				cam.x=x*2-cam.up.x+(cam.x-x*2);
				cam.y=y*2-cam.up.y+(cam.y-y*2);
				cam.z=z*2-cam.up.z+(cam.z-z*2);
			}/*else if(cam.shift==0 && cam.y/2-y<0 && cam.y>0){
				//cam.x=x*2*cam.up.x;
				//cam.y=y*2*cam.up.y;
				//cam.z=z*2*cam.up.z;
			}//*/
		}else{
			cam.vel=Vec3_divn(cam.vel,1.01);
		}
		fseek(map,(size[0]*size[1]*z1+size[0]*y1+x1)*sizeof(int),SEEK_SET);
		fread(&num[0],sizeof(int),1,map);
		if(num[0]!=0){
			cam.x+=cam.up.x*2;
			cam.y+=cam.up.y*2;
			cam.z+=cam.up.z*2;
		}
		cam.vel=Vec3_subv(cam.vel,Vec3_divn(cam.up,50));//.y-=.02;
		//struct Vec3 vec=Vec3_subv(Vec3_newn(cam.x,cam.y,cam.z),Vec3_muln(cam.up,2));
		//printf("(%i,%i,%i),(%i,%i,%i)\n",x,y,z,x1,y1,z1);//(int)(vec.x+1)/2,(int)(vec.y+1)/2,(int)(vec.z+1)/2);
		//printf("%i,%f,%f\n",num[4],cam.vel.y,cam.y/2-y);
		//printf("((%i,%i),(%i,%i),(%i,%i))\n",num[0],num[1],num[2],num[3],num[4],num[5]);
		//printf("(%i,%i,%i),(%f,%f,%f)\n",x,y,z,cam.x,cam.y,cam.z);
		//printf("(%f,%f,%i),%f\n",cam.z/2,cam.z/2-z,z,cam.vel.z);
		//printf("(%f,%f,%i),%f\n",cam.x/2,cam.x/2-x,x,cam.vel.x);
		//printf("(%f,%f,%i),%f,%i,%i\n",cam.y/2,cam.y/2-y,y,cam.vel.y,cam.grounded,col[1]);
	}else{
		if(cam.shift==1){
			cam.y+=1;
		}
		if(cam.y<1){
			cam.grounded=1;
			cam.vel.y=0;
			cam.y=1;
		}else if(cam.y>1){
			cam.grounded=0;
		}

		if(cam.grounded==1){
			cam.vel=Vec3_divn(cam.vel,1.1);
		}else{
			cam.vel=Vec3_divn(cam.vel,1.01);
			cam.vel.y-=.02;
		}

		cam.x+=cam.vel.x;
		cam.y+=cam.vel.y;
		cam.z+=cam.vel.z;
		if(cam.shift==1){
			cam.y-=1;
		}
		//printf("by,%i\n",y);
	}

	return cam;
}

/*/struct Cam Cam_update(struct Cam cam,FILE *map,int size[3]){
	int x=(int)(cam.x+1)/2;
	int y=(int)(cam.y+1)/2;
	int z=(int)(cam.z+1)/2;
	if((int)cam.x>=0 && (int)cam.z>=0 && x<size[0] && z<size[2]){
		int num[4];
		fseek(map,(size[0]*size[1]*z+size[0]*(y-1)+x)*sizeof(int),SEEK_SET);
		fread(&num[0],sizeof(int),1,map);
		fseek(map,(size[0]*size[1]*z+size[0]*(y-2)+x)*sizeof(int),SEEK_SET);
		fread(&num[1],sizeof(int),1,map);
		if(num[1]!=0 && cam.grounded==0 && cam.y>0){
			cam.grounded=1;
			cam.vel.y=0;
			cam.y=y*2;
		}else if(cam.vel.y>0.4 || cam.y/2-y>0 && cam.vel.y<0.1 || num[1]==0 && cam.y>0){
			cam.grounded=0;
		}
		if(cam.grounded==1){
			cam.vel=Vec3_divn(cam.vel,1.1);
			if(cam.shift==1 && cam.y/2-y>=0){
				cam.y=y*2-.5*2;
			}else if(cam.shift==0 && cam.y/2-y<0 && cam.y>0){
				cam.y=y*2;
			}
		}else{
			cam.vel=Vec3_divn(cam.vel,1.01);
			cam.vel.y-=.02;
		}
		if(cam.y>-10 && cam.y<50){
			cam.y+=cam.vel.y;
		}else{cam.grounded=1;}
		if(cam.y<0 || cam.y>size[1]){
			cam.x+=cam.vel.x;
			cam.z+=cam.vel.z;
		}else{
			fseek(map,(size[0]*size[1]*z+size[0]*y+(x+1))*sizeof(int),SEEK_SET);
			fread(&num[0],sizeof(int),1,map);
			if(num[0]==0){
				fseek(map,(size[0]*size[1]*z+size[0]*(y-1)+(x+1))*sizeof(int),SEEK_SET);
				fread(&num[0],sizeof(int),1,map);
			}
			fseek(map,(size[0]*size[1]*z+size[0]*y+(x-1))*sizeof(int),SEEK_SET);
			fread(&num[1],sizeof(int),1,map);
			if(num[1]==0){
				fseek(map,(size[0]*size[1]*z+size[0]*(y-1)+(x-1))*sizeof(int),SEEK_SET);
				fread(&num[1],sizeof(int),1,map);
			}
			fseek(map,(size[0]*size[1]*(z+1)+size[0]*y+x)*sizeof(int),SEEK_SET);
			fread(&num[2],sizeof(int),1,map);
			if(num[2]==0){
				fseek(map,(size[0]*size[1]*(z+1)+size[0]*(y-1)+x)*sizeof(int),SEEK_SET);
				fread(&num[2],sizeof(int),1,map);
			}
			fseek(map,(size[0]*size[1]*(z-1)+size[0]*y+x)*sizeof(int),SEEK_SET);
			fread(&num[3],sizeof(int),1,map);
			if(num[3]==0){
				fseek(map,(size[0]*size[1]*(z-1)+size[0]*(y-1)+x)*sizeof(int),SEEK_SET);
				fread(&num[3],sizeof(int),1,map);
			}
			if(x+1>=size[0]){
				num[0]=0;
			}else if(x-1<0){
				num[1]=0;
			}if(z+1>=size[2]){
				num[2]=0;
			}else if(z-1<0){
				num[3]=0;
			}
			//printf("(%i,%i,%i,%i)\n",num[0],num[1],num[2],num[3]);
			//printf("(%i,%i,%i),(%f,%f,%f)\n",x,y,z,cam.x,cam.y,cam.z);
			//printf("(%f,%f,%i),%f\n",cam.z/2,cam.z/2-z,z,cam.vel.z);
			//printf("(%f,%f,%i),%f\n",cam.x/2,cam.x/2-x,x,cam.vel.x);
			if((cam.vel.x>0 && num[0]==0 || cam.x/2-x<-0.1)==1 || (cam.vel.x<0 && num[1]==0 || cam.x/2-x>0.1)==1){
				cam.x+=cam.vel.x;
			}else if(cam.vel.x>0){
				cam.x=x*2;
			}else if(cam.vel.x<0){
				cam.x=x*2;
			}
			if((cam.vel.z>0 && num[2]==0 || cam.z/2-z<-0.1)==1 || (cam.vel.z<0 && num[3]==0 || cam.z/2-z>0.1)==1){
				cam.z+=cam.vel.z;
			}else if(cam.vel.z>0){
				cam.z=z*2;
			}else if(cam.vel.z<0){
				cam.z=z*2;
			}
		}
		//printf("hi,%i\n",cam.grounded);
		printf("(%f,%f,%i),%f,%i\n",cam.y/2,cam.y/2-y,y,cam.vel.y,cam.grounded);
	}else{
		if(cam.shift==1){
			cam.y+=1;
		}
		if(cam.y<1){
			cam.grounded=1;
			cam.vel.y=0;
			cam.y=1;
		}else if(cam.y>2){
			cam.grounded=0;
		}

		if(cam.grounded==1){
			cam.vel=Vec3_divn(cam.vel,1.1);
		}else{
			cam.vel=Vec3_divn(cam.vel,1.01);
			cam.vel.y-=.02;
		}

		cam.x+=cam.vel.x;
		cam.y+=cam.vel.y;
		cam.z+=cam.vel.z;
		if(cam.shift==1){
			cam.y-=1;
		}
		//printf("by,%i\n",y);
	}
	return cam;
}//*/

/*struct Cam Cam_update(struct Cam cam,FILE *map,int size[3]){
	int x=(int)cam.x/2;
	int y=(int)cam.y/2;
	int z=(int)cam.z/2;
	int num[4];
	fseek(map,(size[0]*size[1]*z+size[0]*y+x)*sizeof(int),SEEK_SET);
	fread(&num[0],sizeof(int),1,map);
	fseek(map,(size[0]*size[1]*z+size[0]*(y-1)+x)*sizeof(int),SEEK_SET);
	fread(&num[1],sizeof(int),1,map);
	/*if(cam.shift==1){
		cam.y+=1;
	}//* /
	//cam.grounded=0;
	if(x<0 || x>size[0] || z<0 || z>size[2]){
	if(cam.y<1){// || num[0]!=0){
		cam.vel.y=0;
		cam.y=1;
		cam.grounded=1;
	}else /** /if(num[1]!=0 && cam.grounded==0 && y!=0){
		cam.vel.y=0;
		cam.grounded=1;
	//}else if(num[0]!=0){
	//	cam.y=y*2+4;
	}else if(num[0]==0 && num[1]==0 && cam.y>1){
		cam.grounded=0;
	}else if(cam.y-y*2>1){
		if(cam.shift==1){
			cam.y-=1;
		}
	}else if(cam.y-y*2<1){
		if(cam.shift==0){
			cam.y+=1;
		}
	}//* /
	if(y>size[1]){
		cam.grounded=0;
		cam.vel.y=0;
		cam.y=size[1]*2-1;
	}//* /
	/* /if(num[0]==0 && num[1]!=0 || cam.y<1){
		cam.vel.y=0;
		cam.y=(int)(cam.y)+1;
		cam.grounded=1;
	}else if((num[0]<=0 || num[0]>5)==1 && cam.y>1){
		cam.vel.y-=.02;
		cam.grounded=0;
	}//* /
	//printf("(%f,%f,%i),%i\n",cam.y-y*2,cam.y,y*2,cam.grounded);
	/*if(cam.y<1){
		cam.vel.y=0;
		cam.y=1;
		cam.grounded=1;
	}else if(cam.y>1){
		cam.vel.y-=.02;
		cam.grounded=0;
	}//* /
	if(cam.grounded==1){
		cam.vel=Vec3_divn(cam.vel,1.1);
	}else{
		cam.vel=Vec3_divn(cam.vel,1.01);
		cam.vel.y-=.02;
	}
	x=(int)(cam.x*4/6);
	y=(int)(cam.y*4/6);
	z=(int)(cam.z*4/6);
	fseek(map,(size[0]*size[1]*z+size[0]*y+(x+1))*sizeof(int),SEEK_SET);
	fread(&num[0],sizeof(int),1,map);
	if(num[0]==0){
	fseek(map,(size[0]*size[1]*z+size[0]*(y+1)+(x+1))*sizeof(int),SEEK_SET);
	fread(&num[0],sizeof(int),1,map);
	}
	fseek(map,(size[0]*size[1]*z+size[0]*y+(x-1))*sizeof(int),SEEK_SET);
	fread(&num[1],sizeof(int),1,map);
	if(num[1]==0){
	fseek(map,(size[0]*size[1]*z+size[0]*(y+1)+(x-1))*sizeof(int),SEEK_SET);
	fread(&num[1],sizeof(int),1,map);
	}
	fseek(map,(size[0]*size[1]*(z+1)+size[0]*y+x)*sizeof(int),SEEK_SET);
	fread(&num[2],sizeof(int),1,map);
	if(num[2]==0){
	fseek(map,(size[0]*size[1]*(z+1)+size[0]*(y+1)+x)*sizeof(int),SEEK_SET);
	fread(&num[2],sizeof(int),1,map);
	}
	fseek(map,(size[0]*size[1]*(z-1)+size[0]*y+x)*sizeof(int),SEEK_SET);
	fread(&num[3],sizeof(int),1,map);
	if(num[3]==0){
	fseek(map,(size[0]*size[1]*(z-1)+size[0]*(y+1)+x)*sizeof(int),SEEK_SET);
	fread(&num[3],sizeof(int),1,map);
	}//*/
	/*if(cam.shift==1){
		cam.y-=1;
	}//* /
	//num[2]=0;num[3]=0;
	printf("(%i,%i,%i,%i)\n",num[0],num[1],num[2],num[3]);
	if((cam.vel.x>0 && num[0]==0/* && cam.x*3/5<size[0]* /)==1 || (cam.vel.x<0 && num[1]==0/* && cam.x*3/5>0* /)==1){
		cam.x+=cam.vel.x;
	}
	if((cam.vel.y>0 && cam.y*3/5<size[1])==1 || (cam.vel.y<0 && cam.y*3/5>0)==1){
		cam.y+=cam.vel.y;
	}
	if((cam.vel.z>0 && num[2]==0/* && cam.z*3/5<size[2]* /)==1 || (cam.vel.z<0 && num[3]==0/* && cam.z*3/5>0* /)==1){
		cam.z+=cam.vel.z;
	}
	}else{
		cam.x+=cam.vel.x;
		//cam.y+=cam.vel.y;
		cam.z+=cam.vel.z;
	}
	return(cam);
}//*/

#endif //PLAYER_H
