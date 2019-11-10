#include<bits/stdc++.h>
#define M 6005
using namespace std;
int n,sx,sy,ex,ey,tot;
struct node{
	int id,x,y1,y2;
	bool operator < (const node& res)const{return x<res.x;}
}A[M<<1];
double dis[2][M];
double calc(int x1,int y1,int x2,int y2){
	return 1.0*(y2-y1)/(x2-x1);
}
double Dis(int x1,int y1,int x2,int y2){
	return sqrt(1.0*(y2-y1)*(y2-y1)+1.0*(x2-x1)*(x2-x1));
}
void solve(int f,int s){
	int x=A[s].x,y=f?A[s].y1:A[s].y2;
	double k1=-2e100,k2=2e100;
	for(int i=s+1;i<=tot;i++){
		for(int j=0;j<2;j++){
			int nx=A[i].x;
			int ny=(j?A[i].y1:A[i].y2);
			if(x==nx){
				dis[j][i]=min(dis[j][i],dis[f][s]+Dis(x,y,nx,ny));
				if(j==1&&ny>y)k1=2e100;
				if(j==0&&ny<y)k2=-2e100;
			}else {
				double k=calc(x,y,nx,ny);
				if(j==1)k1=max(k1,k);
				if(j==0)k2=min(k2,k);
				if(k>=k1&&k<=k2){
					dis[j][i]=min(dis[j][i],dis[f][s]+Dis(x,y,nx,ny));
				}
			}
		}
	}
}
int main(){
	freopen("car.in","r",stdin);
	freopen("car.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,x1,y1,x2,y2;i<=n;i++){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		A[++tot]=(node){i,x1,y1,y2};
		A[++tot]=(node){i,x2,y1,y2};
	}
	scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
	A[++tot]=(node){0,sx,sy,sy};
	A[++tot]=(node){n+1,ex,ey,ey};
	sort(A+1,A+tot+1);
	for(int i=1;i<=tot;i++)
		dis[0][i]=dis[1][i]=2e100;
	double v,ans;
	scanf("%lf",&v);
	for(int i=1;i<=tot;i++){
		if(A[i].id==0)dis[0][i]=dis[1][i]=0;
		else if(A[i].id==n+1)ans=dis[0][i]/v;
		solve(0,i);solve(1,i);
	}
	printf("%.10lf\n",ans);
	return 0;
}
