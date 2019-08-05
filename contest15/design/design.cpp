#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,m,h[M],tt,sz[M];
LL dp[M][3],Q,g[M][15][3];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
LL add(LL a,LL b){return (a+b)%Q;}
LL mul(LL a,LL b){return (a*b)%Q;}
void dfs(int x,int f){
	dp[x][0]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		LL t0=dp[x][0],t1=dp[x][1],t2=dp[x][2];
		dp[x][0]=max(t0,dp[u][2]+1);
		dp[x][1]=min(max(t1,dp[u][2]+1),max(t0,dp[u][1]));
		dp[x][2]=min(max(t2,dp[u][2]+1),max(t1,dp[u][1]));
	}
	for(int i=1;i<=2;i++)dp[x][i]=min(dp[x][i],dp[x][i-1]);
}
void dfs2(int x,int f){
	for(int i=1;i<=dp[1][2];i++)g[x][i][0]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs2(u,x);
		for(int j=1;j<=dp[1][2];j++){
			LL t0=g[x][j][0],t1=g[x][j][1],t2=g[x][j][2];
			g[x][j][0]=mul(t0,g[u][j-1][2]);
			g[x][j][1]=add(mul(t1,g[u][j-1][2]),mul(t0,g[u][j][1]));
			g[x][j][2]=add(mul(t2,g[u][j-1][2]),mul(t1,g[u][j][1]));
		}
	}
	for(int j=1;j<=dp[1][2];j++){
		g[x][j][1]=add(g[x][j][1],g[x][j][0]);
		g[x][j][2]=add(g[x][j][1],g[x][j][2]);
	}
}
int main(){
	freopen("design.in","r",stdin);
	freopen("design.out","w",stdout);
	memset(dp,60,sizeof(dp));
	scanf("%d%d%d",&n,&m,&Q);
	if(m!=n-1){puts("-1");puts("-1");return 0;}
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	dfs(1,0);dfs2(1,0);
	printf("%lld\n%lld\n",dp[1][2]-1,g[1][dp[1][2]][2]);
	return 0;
}
