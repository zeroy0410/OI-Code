#include<bits/stdc++.h>
#define N 2000
using namespace std;
template<typename T>inline void read(T &x){
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}
struct node{
    double x,y,w;
}e[N];
int n;
double ansx,ansy;
const double eps=1e-15;
double f(double x,double y){
    double tot=0;
    for(int i=1;i<=n;i++){
        double delx=x-e[i].x;
        double dely=y-e[i].y;
        tot+=sqrt(delx*delx+dely*dely)*e[i].w;
    }
    return tot;
}
void mnth(){
    double T=200;
    while(T>eps){
        double nowx=ansx+(rand()*2-RAND_MAX)*T;
        double nowy=ansy+(rand()*2-RAND_MAX)*T;
        double delta=f(nowx,nowy)-f(ansx,ansy);
        if(delta<0)ansx=nowx,ansy=nowy;
        else if(exp(-delta/T)*RAND_MAX>rand())ansx=nowx,ansy=nowy;
        T*=0.998;
    }
}
int main(){
    srand((int)time(NULL));
    read(n);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf%lf",&e[i].x,&e[i].y,&e[i].w);
        ansx+=e[i].x;ansy+=e[i].y;
    }
    ansx/=(double)n;ansy/=(double)n;
    mnth();
    printf("%.3lf %.3lf\n",ansx,ansy);
    return 0;
}
