#include<bits/stdc++.h>
#define M 1005
#define LL long long
using namespace std;
bool mm1;
int n,m,tt;
int dxy[4][2]={1,0,0,1,-1,0,0,-1};
LL now[M][M],A[M][M];
struct node{
	int x,y;
	bool operator < (const node& res)const{
		return now[x][y]>now[res.x][res.y];
	}
};
priority_queue<node>Q;
LL ans;
bool vis[M][M];
int ID(int x,int y){
	return (x-1)*m+y;
}
bool mm2;
int main(){
//	printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	freopen("rain.in","r",stdin);
	freopen("rain.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&A[i][j]);
		}
	}
	memset(now,60,sizeof(now));
	for(int i=1;i<=n;i++){
		now[i][1]=A[i][1];
		now[i][m]=A[i][m];
		vis[i][1]=vis[i][m]=1;
		Q.push((node){i,1});
		Q.push((node){i,m});
	}
	for(int i=1;i<=m;i++){
		now[1][i]=A[1][i];
		now[n][i]=A[n][i];
		vis[1][i]=vis[n][i]=1;
		Q.push((node){1,i});
		Q.push((node){n,i});
	}
	while(!Q.empty()){
		node e=Q.top();Q.pop();
		for(int i=0;i<4;i++){
			int nx=e.x+dxy[i][0];
			int ny=e.y+dxy[i][1];
			if(nx<0||nx>n||ny<0||ny>m||vis[nx][ny])continue;
			now[nx][ny]=max(A[nx][ny],now[e.x][e.y]);
			vis[nx][ny]=1;
			Q.push((node){nx,ny});
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans+=now[i][j]-A[i][j];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
