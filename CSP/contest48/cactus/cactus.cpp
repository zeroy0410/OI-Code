#include<bits/stdc++.h>
#define M 500005
#define LL long long
using namespace std;
int n,m,h[M],tt,aa[M],bb[M],tot,mk[M],fe[M];
struct edge{
	int nxt,to;
}G[M<<2];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int dfn[M],ret[M],fa[M];
void dfs_Init(int x,int f){//mark loop
	dfn[x]=++tot;fa[x]=f;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		if(dfn[u]){
			if(dfn[u]>dfn[x])continue;
			mk[i]=1;
			mk[i^1]=1;
			ret[x]++;ret[u]--;
		}
		else {
			fe[u]=i;
			dfs_Init(u,x);ret[x]+=ret[u];
		}
	}
	if(ret[x]){
		mk[fe[x]]=1;
		mk[fe[x]^1]=1;
	}
}
int dp[M][2],g[M][2];
void dfs(int x,int f){
	dp[x][0]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		if(fa[u]==x)dfs(u,x);
		if(dfn[u]<dfn[x])continue;
		if(!mk[i]){
			dp[x][0]+=dp[u][0];
			dp[x][1]+=dp[u][1];
		}
		else dp[x][1]+=dp[u][0];
	}
}
void redfs(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f){
			if(mk[fe[x]])g[x][1]+=dp[f][0]+g[f][0];
			else {
				g[x][0]+=g[f][0]+dp[f][0]-dp[x][0];
				g[x][1]+=g[f][1]+dp[f][1]-dp[x][1];
			}
		}
		else if(dfn[x]<dfn[u])g[x][1]+=dp[u][0]+g[i][0];
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		if(fa[u]==x)redfs(u,x);
	}
}
int main(){
//	freopen("cactus.in","r",stdin);
//	freopen("cactus.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		aa[i]=a;bb[i]=b;
		Add(a,b);Add(b,a);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]){
			dfs_Init(i,0);
			dfs(i,0);
			redfs(i,0);
		}
	for(int i=1;i<=m;i++){
		int x=aa[i],y=bb[i];
		if(dfn[x]>dfn[y])swap(x,y);
		LL ans=0;
		if(mk[i*2-1])ans=(g[x][0]+dp[x][0])*dp[y][0];
		else {
			ans=(g[x][0]+dp[x][0]-dp[y][0])*(dp[y][0]+dp[y][1]);
			ans+=(g[x][1]+dp[x][1]-dp[y][1])*dp[y][0];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
