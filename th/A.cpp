#include<bits/stdc++.h>
#define M 1005
using namespace std;
const double eps=1e-15;
int n;
struct node{ double x,y,w; }A[M];
double ansx,ansy;
double calc(double x,double y){
	double res=0;
	for(int i=1;i<=n;i++){
		double tx=x-A[i].x;
		double ty=y-A[i].y;
		res+=sqrt(tx*tx+ty*ty)*A[i].w;
	}
	return res;
}
void SA(){
	double T=100;
	while(T>eps){
		double nowx=ansx+(rand()*2-RAND_MAX)*T;
		double nowy=ansy+(rand()*2-RAND_MAX)*T;
		double cj=calc(nowx,nowy)-calc(ansx,ansy);
		if(cj<0)ansx=nowx,ansy=nowy;
		else if(exp(-cj/T)*RAND_MAX>rand())ansx=nowx,ansy=nowy;
		T*=0.998;
	}
}
int main(){
	srand(time(NULL));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",&A[i].x,&A[i].y,&A[i].w);
		ansx+=A[i].x;ansy+=A[i].y;
	}
	ansx/=1.0*n;ansy/=1.0*n;
	SA(); SA(); SA(); SA();
	SA(); SA(); 
	printf("%.3lf %.3lf\n",ansx,ansy);
	return 0;
}
