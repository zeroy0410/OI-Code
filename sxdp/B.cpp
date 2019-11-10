#include<stdio.h>
#include<algorithm>
#define M 500005
using namespace std;
int n,K,h[M],tt,sz[M];
double dp[M];
struct edge{int nxt,to;}G[M];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void dfs(int x,int f){
	sz[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		sz[x]+=sz[u];
	}
	if(sz[x]==1)dp[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dp[x]=max(dp[x],min(dp[u],1.0*sz[u]/(sz[x]-1)));
	}
}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=2,x;i<=n;i++){
		scanf("%d",&x);
		Add(x,i);
	}
	dfs(1,0);double ans=0;
	for(int i=1;i<=n;i++)
		if(sz[i]>K)
			ans=max(ans,dp[i]);
	printf("%.8lf\n",ans);
	return 0;
}
