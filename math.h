#ifndef MATH_H
#define MATH_H

#define printfc(c) printf("%.1f%+.1fi\n",creal(c),cimag(c))

#include <math.h>
#include <complex.h>
#include <string.h>

struct Func{
  int insize;
  int outsize;
  struct Exp* func;
};

struct Exp{
  int type;
  float num;
  struct Exp* parem1;
  struct Exp* parem2;
};

struct Vec{
  int size;
  double complex *vec;
};

struct Vec2{
	float x;
	float y;
};

struct Vec3{
	float x;
	float y;
	float z;
};

struct Vec4{
	float w;
	float x;
	float y;
	float z;
};

struct Face{
	int size;
	int f[20];
};

struct Vec Vec_new(size_t size,...);
struct Vec Vec_newComp(size_t size,...);
struct Vec Vec_zero(size_t size);

struct Vec2 Vec2_new(float x,float y);
struct Vec3 Vec3_new(float x,float y,float z);
struct Vec4 Vec4_new(float w,float x,float y,float z);

struct Vec Vec_norm(struct Vec v);
struct Vec Vec_neg(struct Vec v);
struct Vec Vec_ortho(struct Vec a,struct Vec b);
struct Vec Vec_rot(float theata,struct Vec a,struct Vec b,struct Vec c);
double Vec_length(struct Vec v);
double Vec_dot(struct Vec a,struct Vec b);
double Vec_angle(struct Vec a,struct Vec b);
double Vec_det(struct Vec a,struct Vec b);

struct Vec2 Vec2_norm(struct Vec2 v);
struct Vec2 Vec2_neg(struct Vec2 v);
struct Vec2 Vec2_ortho2(struct Vec2 a,struct Vec2 b);
struct Vec2 Vec2_rot(float theata,struct Vec2 v);
float Vec2_length(struct Vec2 v);
float Vec2_dot(struct Vec2 a,struct Vec2 b);
float Vec2_angle(struct Vec2 a,struct Vec2 b);
float Vec2_det(struct Vec2 a,struct Vec2 b);

struct Vec3 Vec3_norm(struct Vec3 v);
struct Vec3 Vec3_neg(struct Vec3 v);
struct Vec3 Vec3_ortho2(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_ortho3(struct Vec3 a,struct Vec3 b,struct Vec3 c);
struct Vec3 Vec3_rot(float theata,struct Vec3 a,struct Vec3 b,struct Vec3 c);
float Vec3_length(struct Vec3 v);
float Vec3_dot(struct Vec3 a,struct Vec3 b);
float Vec3_angle(struct Vec3 a,struct Vec3 b);
float Vec3_det(struct Vec3 a,struct Vec3 b,struct Vec3 c);

struct Vec4 Vec4_norm(struct Vec4 v);
struct Vec4 Vec4_neg(struct Vec4 v);
struct Vec4 Vec4_ortho2(struct Vec4 a,struct Vec4 b);
struct Vec4 Vec4_ortho3(struct Vec4 a,struct Vec4 b,struct Vec4 c);
struct Vec4 Vec4_ortho4(struct Vec4 a,struct Vec4 b,struct Vec4 c,struct Vec4 d);
struct Vec4 Vec4_rot(float theata,struct Vec4 a,struct Vec4 b,struct Vec4 c);
float Vec4_length(struct Vec4 v);
float Vec4_dot(struct Vec4 a,struct Vec4 b);
float Vec4_angle(struct Vec4 a,struct Vec4 b);
float Vec4_det(struct Vec4 a,struct Vec4 b,struct Vec4 c,struct Vec4 d);

struct Vec Vec_addn(struct Vec v,float n);
struct Vec Vec_addv(struct Vec a,struct Vec b);
struct Vec Vec_subn(struct Vec v,float n);
struct Vec Vec_subv(struct Vec a,struct Vec b);
struct Vec Vec_muln(struct Vec v,float n);
struct Vec Vec_mulv(struct Vec a,struct Vec b);
struct Vec Vec_divn(struct Vec v,float n);
struct Vec Vec_divv(struct Vec a,struct Vec b);

struct Vec2 Vec2_addn(struct Vec2 v,float n);
struct Vec2 Vec2_addv(struct Vec2 a,struct Vec2 b);
struct Vec2 Vec2_subn(struct Vec2 v,float n);
struct Vec2 Vec2_subv(struct Vec2 a,struct Vec2 b);
struct Vec2 Vec2_muln(struct Vec2 v,float n);
struct Vec2 Vec2_mulv(struct Vec2 a,struct Vec2 b);
struct Vec2 Vec2_divn(struct Vec2 v,float n);
struct Vec2 Vec2_divv(struct Vec2 a,struct Vec2 b);

struct Vec3 Vec3_addn(struct Vec3 v,float n);
struct Vec3 Vec3_addv(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_subn(struct Vec3 v,float n);
struct Vec3 Vec3_subv(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_muln(struct Vec3 v,float n);
struct Vec3 Vec3_mulv(struct Vec3 a,struct Vec3 b);
struct Vec3 Vec3_divn(struct Vec3 v,float n);
struct Vec3 Vec3_divv(struct Vec3 a,struct Vec3 b);

struct Vec4 Vec4_addn(struct Vec4 v,float n);
struct Vec4 Vec4_addv(struct Vec4 a,struct Vec4 b);
struct Vec4 Vec4_subn(struct Vec4 v,float n);
struct Vec4 Vec4_subv(struct Vec4 a,struct Vec4 b);
struct Vec4 Vec4_muln(struct Vec4 v,float n);
struct Vec4 Vec4_mulv(struct Vec4 a,struct Vec4 b);
struct Vec4 Vec4_divn(struct Vec4 v,float n);
struct Vec4 Vec4_divv(struct Vec4 a,struct Vec4 b);

double complex grammer(struct Exp* exp,struct Vec in);
struct Vec function(struct Func func,struct Vec in);

void convexHull3(struct Face face[],int *nof,const struct Vec3 *points,int n);
void convexHull2(int *order,int *size,struct Vec2 *points,int n);

//IMPLIMENT

struct Vec3 intersection3(struct Vec3 norm,struct Vec3 zero,struct Vec3 vec,struct Vec3 pos){
	//float d=Vec3_dot(norm,zero);
	//vec=Vec3_subv(vec,pos);
	//struct Vec3 temp=Vec3_mulv(pos,norm);
	//d=d-Vec3_dot(pos,norm);//(temp.x+temp.y+temp.z);
	//temp=Vec3_mulv(vec,norm);
	//d=d/Vec3_dot(vec,norm);//(temp.x+temp.y+temp.z);
	return Vec3_addv(Vec3_muln(vec,(Vec3_dot(norm,zero)-Vec3_dot(pos,norm))/Vec3_dot(vec,norm)),pos);
}

struct Vec4 intersection4(struct Vec4 norm,struct Vec4 zero,struct Vec4 vec,struct Vec4 pos){
	/*float d=Vec4_dot(norm,zero);
	//vec=Vec3_subv(vec,pos);
	struct Vec4 temp=Vec4_mulv(pos,norm);
	d=d-(temp.x+temp.y+temp.z);
	temp=Vec4_mulv(vec,norm);
	d=d/(temp.x+temp.y+temp.z);
	return Vec4_addv(Vec4_muln(vec,d),pos);//*/
return Vec4_addv(Vec4_muln(vec,(Vec4_dot(norm,zero)-Vec4_dot(pos,norm))/Vec4_dot(vec,norm)),pos);
}

int Vec2_equal(struct Vec2 a,struct Vec2 b){
	if(a.x==b.x && a.y==b.y)
		return 1;
	return 0;
}

int Vec3_equal(struct Vec3 a,struct Vec3 b){
	if(a.x==b.x&&a.y==b.y&&a.z==b.z)
		return 1;
	return 0;
}

int Vec4_equal(struct Vec4 a,struct Vec4 b){
	if(a.w==b.w&&a.x==b.x&&a.y==b.y&&a.z==b.z)
		return 1;
	return 0;
}

struct Vec Vec_new(size_t size,...){
  struct Vec vec;
  vec.size=size;
  vec.vec=malloc(sizeof(double complex)*size);
  va_list args;
  va_start(args,size);
  for(size_t i=0;i<size;i++){
    vec.vec[i]=va_arg(args,double);
  }
  va_end(args);
  return vec;
}

struct Vec Vec_newComp(size_t size,...){
  struct Vec vec;
  vec.size=size;
  vec.vec=malloc(sizeof(double complex)*size);
  va_list args;
  va_start(args,size);
  for(size_t i=0;i<size;i++){
    vec.vec[i]=va_arg(args,double complex);
  }
  va_end(args);
  return vec;
}

struct Vec Vec_zero(size_t size){
  struct Vec vec;
  vec.size=size;
  vec.vec=malloc(sizeof(double complex)*size);
  for(size_t i=0;i<size;i++){
    vec.vec[i]=0;
  }
  return vec;
}

struct Vec2 Vec2_new(float x,float y){
	struct Vec2 vec;
	vec.x=x;
	vec.y=y;
	return vec;
}

struct Vec3 Vec3_new(float x,float y,float z){
	struct Vec3 vec;
	vec.x=x;
	vec.y=y;
	vec.z=z;
	return vec;
}

struct Vec4 Vec4_new(float w,float x,float y,float z){
	struct Vec4 vec;
	vec.w=w;
	vec.x=x;
	vec.y=y;
	vec.z=z;
	return vec;
}

struct Vec Vec_norm(struct Vec v){
	return Vec_divn(v,Vec_length(v));
}

struct Vec Vec_neg(struct Vec v){
	for(size_t i=0;i<v.size;i++){
		v.vec[i]=-v.vec[i];
	}
	return v;
}
/*
struct Vec Vec_ortho(struct Vec a,...){
	c=Vec_norm(c);
	b=Vec_norm(Vec_ortho(b,c));
	return Vec3_subv(a,Vec3_addv(Vec3_muln(b,Vec3_dot(a,b)),Vec3_muln(c,Vec3_dot(a,c))));
}//*/

///////////////////////////////////
/*
struct Vec Vec_rot(float theata,struct Vec a,struct Vec b,struct Vec c){
	c=Vec_norm(c);
	b=Vec_norm(Vec_ortho(b,c));

	struct Vec2 vec=Vec2_new(Vec3_dot(a,b),Vec3_dot(a,c));
	if(tag==1)
		printf("(%f,%f)\n",vec.x,vec.y);
	//printf("%f,%f,%f\n",a.x,a.y,a.z);
	a=Vec3_ortho3(a,b,c);
	vec=Vec2_rot(theata,vec);
	//printf("%f:%f,%f\n",theata,vec.x,vec.y);
	a=Vec3_addv(a,Vec3_addv(Vec3_muln(b,vec.x),Vec3_muln(c,vec.y)));
	//printf("%f,%f,%f\n",a.x,a.y,a.z);
	return a;
}//*/

double Vec_length(struct Vec v){
	double n=0;
	for(size_t i=0;i<v.size;i++)
		n+=(v.vec[i]*v.vec[i]);
	return csqrt(n);
}

double Vec_dot(struct Vec a,struct Vec b){
	double n=0;
	if(a.size!=b.size)
		return n;
	for(size_t i=0;i<a.size;i++)
		n+=(a.vec[i]*b.vec[i]);
	return n;
}

double Vec_angle(struct Vec a,struct Vec b){
	return cacos(Vec_dot(a,b)/(Vec_length(a)*Vec_length(b)));
}
/*
double Vec_det(struct Vec a,struct Vec b){
	return (a.x*b.y)-(b.x*a.y);
}//*/

struct Vec2 Vec2_norm(struct Vec2 v){
	return Vec2_divn(v,Vec2_length(v));
}

struct Vec2 Vec2_neg(struct Vec2 v){
	return Vec2_subv(Vec2_new(0,0),v);
}

struct Vec2 Vec2_ortho2(struct Vec2 a,struct Vec2 b){
	b=Vec2_norm(b);
	return Vec2_subv(a,Vec2_muln(b,Vec2_dot(a,b)));
}

struct Vec2 Vec2_rot(float theata,struct Vec2 v){
	float cos=cosf(theata);
	float sin=sinf(theata);
	return Vec2_new(v.x*cos-v.y*sin,v.x*sin+v.y*cos);
}

float Vec2_length(struct Vec2 v){
	return sqrt(v.x*v.x+v.y*v.y);
}

float Vec2_dot(struct Vec2 a,struct Vec2 b){
	return (a.x*b.x+a.y*b.y);
}

float Vec2_angle(struct Vec2 a,struct Vec2 b){
	return acosf(Vec2_dot(a,b)/(Vec2_length(a)*Vec2_length(b)));
}

float Vec2_det(struct Vec2 a,struct Vec2 b){
	return (a.x*b.y)-(b.x*a.y);
}

struct Vec3 Vec3_norm(struct Vec3 v){
	if(Vec3_length(v)==0){
		return v;
	}
	return Vec3_divn(v,Vec3_length(v));
}

struct Vec3 Vec3_neg(struct Vec3 v){
	return Vec3_subv(Vec3_new(0,0,0),v);
}

struct Vec3 Vec3_ortho2(struct Vec3 a,struct Vec3 b){
	//if(Vec3_equal(a,b) || Vec3_equal(b,Vec3_new(0,0,0)))
	//	return Vec3_new(0,0,0);
	b=Vec3_norm(b);
	return Vec3_subv(a,Vec3_muln(b,Vec3_dot(a,b)));
}

struct Vec3 Vec3_ortho3(struct Vec3 a,struct Vec3 b,struct Vec3 c){
	//if(Vec3_equal(a,b) || Vec3_equal(a,c) || Vec3_equal(b,c) || Vec3_equal(a,Vec3_new(0,0,0) || Vec3_equal(b,Vec3_new(0,0,0) || Vec3_equal(c,Vec3_new(0,0,0)))
	//	return Vec3_new(0,0,0);
	c=Vec3_norm(c);
	b=Vec3_norm(Vec3_ortho2(b,c));
	return Vec3_subv(a,Vec3_addv(Vec3_muln(b,Vec3_dot(a,b)),Vec3_muln(c,Vec3_dot(a,c))));
}

struct Vec3 Vec3_rot(float theata,struct Vec3 a,struct Vec3 b,struct Vec3 c){
	c=Vec3_norm(c);
	b=Vec3_norm(Vec3_ortho2(b,c));

	struct Vec2 vec=Vec2_new(Vec3_dot(a,b),Vec3_dot(a,c));
	a=Vec3_ortho3(a,b,c);
	vec=Vec2_rot(theata,vec);
	//printf("%f:%f,%f\n",theata,vec.x,vec.y);
	a=Vec3_addv(a,Vec3_addv(Vec3_muln(b,vec.x),Vec3_muln(c,vec.y)));
	//printf("%f,%f,%f\n",a.x,a.y,a.z);
	return a;
}

float Vec3_length(struct Vec3 v){
	return sqrtf(v.x*v.x+v.y*v.y+v.z*v.z);
}

float Vec3_dot(struct Vec3 a,struct Vec3 b){
	return (a.x*b.x+a.y*b.y+a.z*b.z);
}

float Vec3_angle(struct Vec3 a,struct Vec3 b){
	return acosf(Vec3_dot(a,b)/(Vec3_length(a)*Vec3_length(b)));
}

float Vec3_det(struct Vec3 a,struct Vec3 b,struct Vec3 c){
	return (a.x*b.y*c.z)+(b.x*c.y*a.z)+(c.x*a.y*b.z)-(c.x*b.y*a.z)-(b.x*a.y*c.z)-(a.x*c.y*b.z);
}

struct Vec4 Vec4_norm(struct Vec4 v){
	if(Vec4_length(v)==0){
		return v;
	}
	return Vec4_divn(v,Vec4_length(v));
}

struct Vec4 Vec4_neg(struct Vec4 v){
	return Vec4_subv(Vec4_new(0,0,0,0),v);
}

struct Vec4 Vec4_ortho2(struct Vec4 a,struct Vec4 b){
	b=Vec4_norm(b);
	return Vec4_subv(a,Vec4_muln(b,Vec4_dot(a,b)));
}

struct Vec4 Vec4_ortho3(struct Vec4 a,struct Vec4 b,struct Vec4 c){
	//if(Vec3_equal(a,b) || Vec3_equal(a,c) || Vec3_equal(b,c) || Vec3_equal(a,Vec3_new(0,0,0)))
	//	return Vec3_new(0,0,0);
	c=Vec4_norm(c);
	b=Vec4_norm(Vec4_ortho2(b,c));
	return Vec4_subv(a,Vec4_addv(Vec4_muln(b,Vec4_dot(a,b)),Vec4_muln(c,Vec4_dot(a,c))));
}

struct Vec4 Vec4_ortho4(struct Vec4 a,struct Vec4 b,struct Vec4 c,struct Vec4 d){
	//if(Vec3_equal(a,b) || Vec3_equal(a,c) || Vec3_equal(b,c) || Vec3_equal(a,Vec3_new(0,0,0)))
	//	return Vec3_new(0,0,0);
	d=Vec4_norm(d);
	c=Vec4_norm(Vec4_ortho2(c,d));
	b=Vec4_norm(Vec4_ortho3(b,c,d));
	return Vec4_subv(a,Vec4_addv(Vec4_muln(b,Vec4_dot(a,b)),Vec4_addv(Vec4_muln(c,Vec4_dot(a,c)),Vec4_muln(d,Vec4_dot(a,d)))));
}

struct Vec4 Vec4_rot(float theata,struct Vec4 a,struct Vec4 b,struct Vec4 c){
	c=Vec4_norm(c);
	b=Vec4_norm(Vec4_ortho2(b,c));

	struct Vec2 vec=Vec2_new(Vec4_dot(a,b),Vec4_dot(a,c));
	a=Vec4_ortho3(a,b,c);
	vec=Vec2_rot(theata,vec);
	//printf("%f:%f,%f\n",theata,vec.x,vec.y);
	a=Vec4_addv(a,Vec4_addv(Vec4_muln(b,vec.x),Vec4_muln(c,vec.y)));
	//printf("%f,%f,%f\n",a.x,a.y,a.z);
	return a;
}

float Vec4_length(struct Vec4 v){
	return sqrtf(v.w*v.w+v.x*v.x+v.y*v.y+v.z*v.z);
}

float Vec4_dot(struct Vec4 a,struct Vec4 b){
	return (a.w*b.w+a.x*b.x+a.y*b.y+a.z*b.z);
}

float Vec4_angle(struct Vec4 a,struct Vec4 b){
	return acosf(Vec4_dot(a,b)/(Vec4_length(a)*Vec4_length(b)));
}

float Vec4_det(struct Vec4 a,struct Vec4 b,struct Vec4 c,struct Vec4 d){
	return (a.w*b.x*c.y*d.z)+(b.w*c.x*d.y*a.z)+(c.w*d.x*a.y*b.z)+(d.w*a.x*b.y*c.z)
				-(d.w*c.x*b.y*a.z)-(c.w*b.x*a.y*d.z)-(b.w*a.x*d.y*c.z)-(a.w*d.x*c.y*b.z);
}

struct Vec Vec_addn(struct Vec v,float n){
	for(size_t i=0;i<v.size;i++)
		v.vec[i]+=n;
	return v;
}

struct Vec Vec_addv(struct Vec a,struct Vec b){
	if(a.size!=b.size)
		return a;
	for(size_t i=0;i<a.size;i++)
		a.vec[i]+=b.vec[i];
	return a;
}

struct Vec Vec_subn(struct Vec v,float n){
	for(size_t i=0;i<v.size;i++)
		v.vec[i]-=n;
	return v;
}

struct Vec Vec_subv(struct Vec a,struct Vec b){
	if(a.size!=b.size)
		return a;
	for(size_t i=0;i<a.size;i++)
		a.vec[i]-=b.vec[i];
	return a;
}

struct Vec Vec_muln(struct Vec v,float n){
	for(size_t i=0;i<v.size;i++)
		v.vec[i]*=n;
	return v;
}

struct Vec Vec_mulv(struct Vec a,struct Vec b){
	if(a.size!=b.size)
		return a;
	for(size_t i=0;i<a.size;i++)
		a.vec[i]*=b.vec[i];
	return a;
}

struct Vec Vec_divn(struct Vec v,float n){
	for(size_t i=0;i<v.size;i++)
		v.vec[i]/=n;
	return v;
}

struct Vec Vec_divv(struct Vec a,struct Vec b){
	if(a.size!=b.size)
		return a;
	for(size_t i=0;i<a.size;i++)
		a.vec[i]/=b.vec[i];
	return a;
}

struct Vec2 Vec2_addn(struct Vec2 v,float n){
	v.x+=n;
	v.y+=n;
	return v;
}

struct Vec2 Vec2_addv(struct Vec2 a,struct Vec2 b){
	a.x+=b.x;
	a.y+=b.y;
	return a;
}

struct Vec2 Vec2_subn(struct Vec2 v,float n){
	v.x-=n;
	v.y-=n;
	return v;
}

struct Vec2 Vec2_subv(struct Vec2 a,struct Vec2 b){
	a.x-=b.x;
	a.y-=b.y;
	return a;
}

struct Vec2 Vec2_muln(struct Vec2 v,float n){
	v.x*=n;
	v.y*=n;
	return v;
}

struct Vec2 Vec2_mulv(struct Vec2 a,struct Vec2 b){
	a.x*=b.x;
	a.y*=b.y;
	return a;
}

struct Vec2 Vec2_divn(struct Vec2 v,float n){
	v.x/=n;
	v.y/=n;
	return v;
}

struct Vec2 Vec2_divv(struct Vec2 a,struct Vec2 b){
	a.x/=b.x;
	a.y/=b.y;
	return a;
}

struct Vec3 Vec3_addn(struct Vec3 v,float n){
	v.x+=n;
	v.y+=n;
	v.z+=n;
	return v;
}

struct Vec3 Vec3_addv(struct Vec3 a,struct Vec3 b){
	a.x+=b.x;
	a.y+=b.y;
	a.z+=b.z;
	return a;
}

struct Vec3 Vec3_subn(struct Vec3 v,float n){
	v.x-=n;
	v.y-=n;
	v.z-=n;
	return v;
}

struct Vec3 Vec3_subv(struct Vec3 a,struct Vec3 b){
	a.x-=b.x;
	a.y-=b.y;
	a.z-=b.z;
	return a;
}

struct Vec3 Vec3_muln(struct Vec3 v,float n){
	v.x*=n;
	v.y*=n;
	v.z*=n;
	return v;
}

struct Vec3 Vec3_mulv(struct Vec3 a,struct Vec3 b){
	a.x*=b.x;
	a.y*=b.y;
	a.z*=b.z;
	return a;
}

struct Vec3 Vec3_divn(struct Vec3 v,float n){
	v.x/=n;
	v.y/=n;
	v.z/=n;
	return v;
}

struct Vec3 Vec3_divv(struct Vec3 a,struct Vec3 b){
	a.x/=b.x;
	a.y/=b.y;
	a.z/=b.z;
	return a;
}

struct Vec4 Vec4_addn(struct Vec4 v,float n){
	v.w+=n;
	v.x+=n;
	v.y+=n;
	v.z+=n;
	return v;
}

struct Vec4 Vec4_addv(struct Vec4 a,struct Vec4 b){
	a.w+=b.w;
	a.x+=b.x;
	a.y+=b.y;
	a.z+=b.z;
	return a;
}

struct Vec4 Vec4_subn(struct Vec4 v,float n){
	v.w-=n;
	v.x-=n;
	v.y-=n;
	v.z-=n;
	return v;
}

struct Vec4 Vec4_subv(struct Vec4 a,struct Vec4 b){
	a.w-=b.w;
	a.x-=b.x;
	a.y-=b.y;
	a.z-=b.z;
	return a;
}

struct Vec4 Vec4_muln(struct Vec4 v,float n){
	v.w*=n;
	v.x*=n;
	v.y*=n;
	v.z*=n;
	return v;
}

struct Vec4 Vec4_mulv(struct Vec4 a,struct Vec4 b){
	a.w*=b.w;
	a.x*=b.x;
	a.y*=b.y;
	a.z*=b.z;
	return a;
}

struct Vec4 Vec4_divn(struct Vec4 v,float n){
	v.w/=n;
	v.x/=n;
	v.y/=n;
	v.z/=n;
	return v;
}

struct Vec4 Vec4_divv(struct Vec4 a,struct Vec4 b){
	a.w/=b.w;
	a.x/=b.x;
	a.y/=b.y;
	a.z/=b.z;
	return a;
}

double orientation(struct Vec2 p,struct Vec2 q,struct Vec2 r);

void convexHull3(struct Face face[],int *nof,const struct Vec3 *points,int n){
	int i,j;
	struct Vec2 points2[n+1];
	int p=0;
	int l;
	for(i=0;i<n;i++){
		points2[i]=Vec2_new(points[i].x,points[i].y);
		if(points2[p].x>points2[i].x){
			p=i;
		}else if(points2[p].x==points2[i].x && points2[p].y>points2[i].y){
			p=i;
		}
	}
	l=p;
	if(n>0){
		int q=(p+1)%n;
		for(i=0;i<n;i++){
			if(orientation(points2[p],points2[i],points2[q])==2){
				q=i;
			}
		}
		p=q;
		q=(p+1)%n;
	}
	//struct Face face[n+1];
	//int nof=0;
	int edge[n+1][n];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			edge[i][j]=0;
		}
	}
	int dir[n+1][n];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			dir[i][j]=0;
		}
	}
	if(l<p)
		edge[l][p]=1;
	else
		edge[p][l]=1;//*/
	int e[2]={0};
	int edges=1;
	int test=0;
	while(edges>0){
		//printf("__%i:%i,%i__\n",edges,e[0],e[1]);
		if(edge[e[0]][e[1]]==1){
			//if(e[0]==l && e[1]==p || e[0]==p && e[1]==l)
			//	edge[e[0]][e[1]]=0;
			//edges=0;
			face[*nof].size=2;
			face[*nof].f[0]=e[0];
			face[*nof].f[1]=e[1];
			struct Vec3 A=points[e[0]];
			//printf("%f,%f,%f\n",A.x,A.y,A.z);
			struct Vec3 B=Vec3_subv(points[e[1]],A);
			struct Vec3 C,X;
			float det;
			//printf("/%i,%i\\\n",e[0],e[1]);
			for(i=0;i<n;i++){
				if(i!=e[0] && i!=e[1]){
					C=Vec3_subv(points[i],A);
					int neg=0;
					int pos=0;
					for(j=0;j<n;j++){
						if(j!=e[0] && j!=e[1] && j!=i){
							X=Vec3_subv(points[j],A);
							det=Vec3_det(B,C,X);
							//printf("%i::%f\n",i,det);
							if(det>-0.00001 && det<0.00001)
								det=0;
							if(det<0){
								neg++;
							}else if(det>0){
								pos++;
							}
							//printf("(A:%i,B:%i,C:%i,X:%i):%f\n",l,p,i,j,det);
						}
					}
					if(neg==0 && dir[e[0]][e[1]]==0 || pos==0 && dir[e[0]][e[1]]==1){
						//printf(":%i,%i,%i,%i\n",edge[e[0]][i],edge[e[1]][i],edge[i][e[0]],edge[i][e[1]]);
						//printf(":%i..%i\n",dir[e[0]][e[1]],i);
						face[*nof].f[face[*nof].size]=i;
						face[*nof].size++;
						//printf("%i\n",i);
					}
				}
			}
			//printf("(%i,%i),%i,%i\n",e[0],e[1],face[*nof].size,*nof);
			struct Vec2 vertices[face[*nof].size];
			//printf(">>>>>>>%i<<<<<<<\n",face[*nof].size);
			if(face[*nof].size>3){
				B=Vec3_norm(B);
				C=Vec3_norm(Vec3_ortho2(Vec3_subv(points[face[*nof].f[2]],A),B));
				//printf(">>%i<<\n",face[*nof].f[2]);
				for(i=0;i<face[*nof].size;i++){
					X=Vec3_subv(points[face[*nof].f[i]],A);
					vertices[i]=Vec2_new(Vec3_dot(X,B),Vec3_dot(X,C));
					//printf("(%f,%f,%f),\n(%f,%f,%f),\n(%f,%f,%f)\n",B.x,B.y,B.z,C.x,C.y,C.z,X.x,X.y,X.z);
					//printf("\n%i>%f,%f\n\n",face[*nof].f[i],vertices[i].x,vertices[i].y);
				}
				int order[face[*nof].size];
				int ftemp[face[*nof].size];
				int size=0;
				convexHull2(order,&size,vertices,face[*nof].size);
				face[*nof].size=size;
				for(i=0;i<face[*nof].size;i++){
					ftemp[i]=face[*nof].f[i];
					if(order[i]>i){
						face[*nof].f[i]=face[*nof].f[order[i]];
					}else{
						face[*nof].f[i]=ftemp[order[i]];
					}
					//printf("%i:(%f,%f)\n",face[*nof].f[i],points[face[*nof].f[i]].x,points[face[*nof].f[i]].y,points[face[*nof].f[i]].z);
				}
			}
			for(i=0;i<face[*nof].size;i++){
				int f[2];
				if(i==face[*nof].size-1){
					if(face[*nof].f[i]>face[*nof].f[0]){
						f[0]=face[*nof].f[0];
						f[1]=face[*nof].f[i];
					}else{
						f[0]=face[*nof].f[i];
						f[1]=face[*nof].f[0];
					}
				}else{
					if(face[*nof].f[i]>face[*nof].f[i+1]){
						f[0]=face[*nof].f[i+1];
						f[1]=face[*nof].f[i];
					}else{
						f[0]=face[*nof].f[i];
						f[1]=face[*nof].f[i+1];
					}
				}

				//printf("%i:%i,%i>%i\n",face[*nof].f[i],f[0],f[1],edge[f[0]][f[1]]);
				edge[f[0]][f[1]]++;
				if(edge[f[0]][f[1]]==1){
					A=points[f[0]];
					B=Vec3_subv(points[f[1]],A);
					if(i==0){
						C=Vec3_subv(points[face[*nof].f[2]],A);
					}else{
						C=Vec3_subv(points[face[*nof].f[i-1]],A);
					}
					X=Vec3_subv(points[0],A);
					det=Vec3_det(B,C,X);
					if(det>-0.00001 && det<0.00001)
						det=0;
					for(j=0;det==0 && j<50;j++){
						X=Vec3_subv(points[j],A);
						det=Vec3_det(B,C,X);
							//printf("%i,%f\n",j,det);
						if(det>-0.00001 && det<0.00001)
							det=0;
					}
					//printf("%f\n",det);
					if(det<0){
						dir[f[0]][f[1]]=0;
					}else{
						dir[f[0]][f[1]]=1;
					}
					edges++;
				}else if(edge[f[0]][f[1]]==2){
					edges--;
				}
			}
			//printf("<<%i,%i>>\n",*nof,face[*nof].size);
			if(face[*nof].size>2)
				(*nof)++;
		}
		if(e[0]>=e[1]){
			e[0]=0;
			e[1]++;
			//edges--;
		}else{
			e[0]++;
		}
		if(e[1]>n){
			e[0]=0;
			e[1]=0;
			test++;
			//edges=0;
		}else if(test>10){
			edges=0;
		}
	}
	//(*nof)--;
	//printf("---------%i,%i---------\n",test,*nof);
}

void convexHull2(int *order,int *size,struct Vec2 *points,int n){
	int count=0;
	if(n<3){
		for(int i=0;i<n-1;i++){
			order[i]=i;
		}
	}else{
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

		do{
			order[count]=p;
			//printf("=%i,%i\n",p,count);
			count++;
			for(int i=0;i<n;i++){
				if(orientation(points[p],points[i],points[q])==2){
					q=i;
				}
			}
			p=q;
			q=(p+1)%n;
		}while(p!=l);
		(*size)=count;
	}
}

double orientation(struct Vec2 p,struct Vec2 q,struct Vec2 r){
	double val=(q.y-p.y)*(r.x-q.x)-(q.x-p.x)*(r.y-q.y);
	if(val==0)
		return 0;
	else if(val>0)
		return 1;
	else
		return 2;
}

double complex grammer(struct Exp* exp,struct Vec in){
  if(exp->type==0)
    return exp->num;
  if(exp->type==1)
    return in.vec[(int)(exp->num)];
  else if(exp->type==2)
    return grammer(exp->parem1,in)+grammer(exp->parem2,in);
  else if(exp->type==3)
    return grammer(exp->parem1,in)-grammer(exp->parem2,in);
  else if(exp->type==4)
    return grammer(exp->parem1,in)*grammer(exp->parem2,in);
  else if(exp->type==5)
    return grammer(exp->parem1,in)/grammer(exp->parem2,in);
  else if(exp->type==6)
    return cpow(grammer(exp->parem1,in),grammer(exp->parem2,in));
  return 0;
}

struct Vec function(struct Func func,struct Vec in){
  struct Vec out;
  if(in.size!=func.insize)
    return out;
  out.size=func.outsize;
  out.vec=malloc(sizeof(double complex)*out.size);
  for(int i=0;i<func.outsize;i++)
    out.vec[i]=grammer(&(func.func[i]),in);
  return out;
}

//}
#endif //MATH_H
