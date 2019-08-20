#include<bits/stdc++.h>
#define debug(x) cerr<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl
#define debug2(a,x) cerr<<#a<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl
using namespace std;
const int maxn=6e3+100;
int n,sx,sy,tx,ty;
int id;
struct node{
	int id,x,y1,y2;
	bool operator <(const node &_)const{
		return x!=_.x?x<_.x:id<_.id;
	}
}A[maxn<<1];
double dis[2][maxn];
double calc(int x1,int y1,int x2,int y2){
	return 1.0*(y2-y1)/(x2-x1);
}
long long PF(int x){
	return 1LL*x*x;
}
double distence(int x,int y,int a,int b){
	return sqrt(PF(x-a)+PF(y-b));
}
void solve(int p,int s){
	int x=A[s].x,y=p?A[s].y1:A[s].y2;
	double k1=-2e100,k2=2e100;
	for(int i=s+1;i<=id;i++){
		for(int j=0;j<2;j++){
			int nx=A[i].x;
			int ny=(j?A[i].y1:A[i].y2);
			if(x==nx){
				dis[j][i]=min(dis[j][i],dis[p][s]+distence(x,y,nx,ny));
				if(j==1&&ny>y)k1=2e100;
				if(j==0&&ny<y)k2=-2e100;
			}else {
				double k=calc(x,y,nx,ny);
				if(j==1)k1=max(k1,k);
				if(j==0)k2=min(k2,k);
				if(k>=k1&&k<=k2){
					dis[j][i]=min(dis[j][i],dis[p][s]+distence(x,y,nx,ny));
				}
			}
		}
	}
}
int main(){
	cin>>n;
	for(int i=1,x1,y1,x2,y2;i<=n;i++){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		A[++id]=(node){i,x1,y1,y2};
		A[++id]=(node){i,x2,y1,y2};
	}
	scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
	if(sx>tx)swap(sx,tx),swap(sy,ty);
	A[++id]=(node){0,sx,sy,sy};
	A[++id]=(node){n+1,tx,ty,ty};
	sort(A+1,A+1+id);
	for(int i=1;i<=id;i++)
		dis[0][i]=dis[1][i]=2e100;
	double v,ans;
	cin>>v;
	for(int i=1;i<=id;i++){
		if(A[i].id==0)dis[0][i]=dis[1][i]=0;
		else if(A[i].id==n+1)ans=dis[0][i]/v;
		solve(0,i);
		solve(1,i);
	}
	printf("%.10f\n",ans);
	return 0;
}
