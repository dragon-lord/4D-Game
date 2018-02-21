#ifndef MATH_H
#define MATH_H

#include<stdio.h>
#include<math.h>

struct Vec3{
	float x;
	float y;
	float z;
};

struct Vec2{
	float x;
	float y;
};

struct Complex{
	float r;
	float i;
};

struct Line{
	float m;
	float b;
};

struct Vec3 Vec3_newn(float x,float y,float z);
struct Vec3 Vec3_newv(float a[3],float b[3]);
struct Vec3 Vec3_addn(struct Vec3 vec,float num);
struct Vec3 Vec3_addv(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_subn(struct Vec3 vec,float num);
struct Vec3 Vec3_subv(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_muln(struct Vec3 vec,float num);
struct Vec3 Vec3_mulv(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_divn(struct Vec3 vec,float num);
struct Vec3 Vec3_divv(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_neg(struct Vec3 vec);

struct Vec2 Vec2_newn(float x,float y);
struct Vec2 Vec2_newv(float a[2],float b[2]);
struct Vec2 Vec2_addn(struct Vec2 vec,float num);
struct Vec2 Vec2_addv(struct Vec2 a,struct Vec2 b);
struct Vec2 Vec2_subn(struct Vec2 vec,float num);
struct Vec2 Vec2_subv(struct Vec2 a,struct Vec2 b);
struct Vec2 Vec2_muln(struct Vec2 vec,float num);
struct Vec2 Vec2_mulv(struct Vec2 a,struct Vec2 b);
struct Vec2 Vec2_divn(struct Vec2 vec,float num);
struct Vec2 Vec2_divv(struct Vec2 a,struct Vec2 b);
struct Vec2 Vec2_neg(struct Vec2 vec);

struct Line Line_newn(float m,float b);
struct Line Line_newv(struct Vec2 a,float x,float y);
float* Line_intercept(struct Line a,struct Line b);

struct Complex Complex_new(float r,float i);
struct Complex Complex_add(struct Complex a,struct Complex b);
struct Complex Complex_sub(struct Complex a,struct Complex b);
struct Complex Complex_mul(struct Complex a,struct Complex b);
struct Complex Complex_div(struct Complex a,struct Complex b);

float Vec2_length(struct Vec2 vec);
struct Vec2 Vec2_perp(struct Vec2 vec);
struct Vec2 Vec2_norm(struct Vec2 vec);

float Vec3_length(struct Vec3 vec);
float Vec3_dot(struct Vec3 a,struct Vec3 b);
float Vec3_angle(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_norm(struct Vec3 vec);
struct Vec3 Vec3_cross(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_rot(struct Vec3 a,struct Vec3 b,float theta);

void printarr(FILE *arr,int width,int height,int depth);
void printarr2(FILE *arr,int width,int height);

struct Vec2 *convexHull(struct Vec2 points[],int n);

//IMPLIMENT

struct Vec3 intersection(struct Vec3 norm,struct Vec3 zero,struct Vec3 vec,struct Vec3 pos){
	float d=Vec3_dot(norm,zero);
	//vec=Vec3_subv(vec,pos);
	struct Vec3 temp=Vec3_mulv(pos,norm);
	d=d-(temp.x+temp.y+temp.z);
	temp=Vec3_mulv(vec,norm);
	d=d/(temp.x+temp.y+temp.z);
	return Vec3_addv(Vec3_muln(vec,d),pos);
}

int Vec3_equal(struct Vec3 a,struct Vec3 b){
	if(a.x==b.x && a.y==b.y && a.z==b.z){
		return 1;
	}
	return 0;
}

int Vec2_equal(struct Vec2 a,struct Vec2 b){
	if(a.x==b.x && a.y==b.y){
		return 1;
	}
	return 0;
}

struct Vec3 Vec3_newn(float x,float y,float z){
	struct Vec3 vec;
	vec.x=x;
	vec.y=y;
	vec.z=z;
	return vec;
}

struct Vec3 Vec3_newv(float a[3],float b[3]){
	struct Vec3 vec;
	vec.x=a[0]-b[0];
	vec.y=a[1]-b[1];
	vec.z=a[2]-b[2];
	return vec;
}

struct Vec3 Vec3_addn(struct Vec3 vec,float num){
	vec.x+=num;
	vec.y+=num;
	vec.z+=num;
	return vec;
}

struct Vec3 Vec3_addv(struct Vec3 a,struct Vec3 b){
	a.x+=b.x;
	a.y+=b.y;
	a.z+=b.z;
	return a;
}

struct Vec3 Vec3_subn(struct Vec3 vec,float num){
	vec.x-=num;
	vec.y-=num;
	vec.z-=num;
	return vec;
}

struct Vec3 Vec3_subv(struct Vec3 a,struct Vec3 b){
	a.x-=b.x;
	a.y-=b.y;
	a.z-=b.z;
	return a;
}

struct Vec3 Vec3_muln(struct Vec3 vec,float num){
	vec.x*=num;
	vec.y*=num;
	vec.z*=num;
	return vec;
}

struct Vec3 Vec3_mulv(struct Vec3 a,struct Vec3 b){
	a.x*=b.x;
	a.y*=b.y;
	a.z*=b.z;
	return a;
}

struct Vec3 Vec3_divn(struct Vec3 vec,float num){
	vec.x/=num;
	vec.y/=num;
	vec.z/=num;
	return vec;
}

struct Vec3 Vec3_divv(struct Vec3 a,struct Vec3 b){
	a.x/=b.x;
	a.y/=b.y;
	a.z/=b.z;
	return a;
}

struct Vec3 Vec3_neg(struct Vec3 vec){
	vec.x=1-vec.x;
	vec.y=1-vec.y;
	vec.z=1-vec.z;
	return vec;
}

struct Vec2 Vec2_newn(float x,float y){
	struct Vec2 vec;
	vec.x=x;
	vec.y=y;
	return vec;
}

struct Vec2 Vec2_newv(float a[2],float b[2]){
	struct Vec2 vec;
	vec.x=a[0]-b[0];
	vec.y=a[1]-b[1];
	return vec;
}

struct Vec2 Vec2_addn(struct Vec2 vec,float num){
	vec.x+=num;
	vec.y+=num;
	return vec;
}

struct Vec2 Vec2_addv(struct Vec2 a,struct Vec2 b){
	a.x+=b.x;
	a.y+=b.y;
	return a;
}

struct Vec2 Vec2_subn(struct Vec2 vec,float num){
	vec.x-=num;
	vec.y-=num;
	return vec;
}

struct Vec2 Vec2_subv(struct Vec2 a,struct Vec2 b){
	a.x-=b.x;
	a.y-=b.y;
	return a;
}

struct Vec2 Vec2_muln(struct Vec2 vec,float num){
	vec.x*=num;
	vec.y*=num;
	return vec;
}

struct Vec2 Vec2_mulv(struct Vec2 a,struct Vec2 b){
	a.x*=b.x;
	a.y*=b.y;
	return a;
}

struct Vec2 Vec2_divn(struct Vec2 vec,float num){
	vec.x/=num;
	vec.y/=num;
	return vec;
}

struct Vec2 Vec2_divv(struct Vec2 a,struct Vec2 b){
	a.x/=b.x;
	a.y/=b.y;
	return a;
}

struct Vec2 Vec2_neg(struct Vec2 vec){
	vec.x=1-vec.x;
	vec.y=1-vec.y;
	return vec;
}

struct Line Line_newn(float m,float b){
	struct Line line;
	line.m=m;
	line.b=b;
	return line;
}

struct Line Line_newv(struct Vec2 a,float x,float y){
	struct Line line;
	line.m=a.y/a.x;
	line.b=(line.m*-x)+y;
	return line;
}

float* Line_intercept(struct Line a,struct Line b){
	float arr[2];

	float m=a.m-b.m;

	float b1=b.b-a.b;

	arr[0]=b1/m;

	arr[1]=a.m*arr[0]+a.b;

	if(arr[1]!=b.m*arr[0]+b.b)
		printf("error\n");
	printf("((%f,%f),(%f,%f)),(%f,%f)\n",a.m,a.b,b.m,b.b,arr[0],arr[1]);
	return arr;
}

struct Complex Complex_new(float r,float i){
	struct Complex complex;
	complex.r=r;
	complex.i=i;
	return complex;
}

struct Complex Complex_add(struct Complex a,struct Complex b){
	a.r+=b.r;
	a.i+=b.i;
	return a;
}

struct Complex Complex_sub(struct Complex a,struct Complex b){
	a.r-=b.r;
	a.i-=b.i;
	return a;
}

struct Complex Complex_mul(struct Complex a,struct Complex b){
	int r=(a.r*b.r)-(a.i*b.i);
	int i=(a.r*b.i)+(a.i*b.r);
	a.r=r;
	a.i=i;
	return a;
}
struct Complex Complex_div(struct Complex a,struct Complex b){
	b.i=-b.i;
	struct Complex ans;
	ans=Complex_mul(a,b);
	ans.r=ans.r/((b.r*b.r)+(b.i*b.i));
	ans.i=ans.i/((b.r*b.r)+(b.i*b.i));
	return ans;
}

float Vec2_length(struct Vec2 vec){
	return(sqrt(vec.x*vec.x+vec.y*vec.y));
}

struct Vec2 Vec2_perp(struct Vec2 vec){
	float temp=vec.x;
	vec.x=-vec.y;
	vec.y=temp;
	return vec;
}

struct Vec2 Vec2_norm(struct Vec2 vec){
	vec=Vec2_divn(vec,Vec2_length(vec));
	return(vec);
}

float Vec3_length(struct Vec3 vec){
	return(sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z));
}

float Vec3_dot(struct Vec3 a,struct Vec3 b){
	return(a.x*b.x+a.y*b.y+a.z*b.z);
}

float Vec3_angle(struct Vec3 a,struct Vec3 b){
	return(acos(Vec3_dot(a,b)/(Vec3_length(a)*Vec3_length(b))));
}

struct Vec3 Vec3_norm(struct Vec3 vec){
	vec=Vec3_divn(vec,Vec3_length(vec));
	return(vec);
}

struct Vec3 Vec3_cross(struct Vec3 a,struct Vec3 b){
	struct Vec3 c;
	c.x=a.y*b.z-a.z*b.y;
	c.y=a.z*b.x-a.x*b.z;
	c.z=a.x*b.y-a.y*b.x;
	return(c);
}

struct Vec3 Vec3_rot(struct Vec3 a,struct Vec3 b,float theta){
	struct Vec3 c;
	float cs=cos(theta);
	float sn=sin(theta);
	c.x=a.x*(cs+(b.x*b.x)*(1-cs))+a.y*(b.x*b.y*(1-cs)-b.z*sn)+a.z*(b.x*b.z*(1-cs)+b.y*sn);
	c.y=a.x*(b.y*b.x*(1-cs)+b.z*sn)+a.y*(cs+(b.y*b.y)*(1-cs))+a.z*(b.y*b.z*(1-cs)-b.x*sn);
	c.z=a.x*(b.z*b.x*(1-cs)-b.y*sn)+a.y*(b.z*b.y*(1-cs)+b.x*sn)+a.z*(cs+(b.z*b.z)*(1-cs));
	return(c);
}

void printarr(FILE *arr,int width,int height,int depth){
	int num;
	for(int k=0;k<depth;k++){
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				fseek(arr,(k*width*height+j*width+i)*sizeof(int),SEEK_SET);
				fread(&num,sizeof(int),1,arr);
				printf("%i ",num);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void printarr2(FILE *arr,int width,int height){
	int num;
	for(int j=0;j<height;j++){
		for(int i=0;i<width;i++){
			fseek(arr,(j*width+i)*sizeof(int),SEEK_SET);
			fread(&num,sizeof(int),1,arr);
			printf("%i ",num);
		}
		printf("\n");
	}
	printf("\n");
}

double orientation(struct Vec2 p,struct Vec2 q,struct Vec2 r);

struct Vec2 *convexHull(struct Vec2 points[],int n){
	if(n<3)
		return points;
	int p=0;
	int l;
	for(int i=1;i<n;i++){
		if(points[p].x>points[i].x){
			p=i;
		}else if(points[p].x==points[i].x && points[p].y>points[i].y){
			p=i;
		}
	}
	l=p;
	int q=(p+1)%n;

	struct Vec2 result[n+1];
	int count=0;
	if(n<3){
		for(int i=0;i<n-1;i++){
			//printf("%lf %lf\n",points[i].x,points[i].y);
			result[count]=points[i];
			count++;
		}
	}else{
		do{
			//printf(" %f,%f\n",points[p].x,points[p].y);
			result[count]=points[p];
			count++;
			for(int i=0;i<n;i++){
				if(orientation(points[p],points[i],points[q])==2){
					q=i;
				}
			}
			p=q;
			q=(p+1)%n;
		}while(p!=l);
	}
	return result;
}

double orientation(struct Vec2 p,struct Vec2 q,struct Vec2 r){
	double val = (q.y - p.y) * (r.x - q.x)-(q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return 0;
	else if(val>0)
		return 1;
	else
		return 2;
}

#endif //MATH_H
