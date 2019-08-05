#include<bits/stdc++.h>
#define M 200005
using namespace std;
int n,h[M],tot;
struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tot]=(edge){h[a],b,c};
	h[a]=tot;
}
int dp[M],mx[2][M],ID[M];
void calc(int x,int id,int v){
	if(mx[0][x]<v)mx[1][x]=mx[0][x],mx[0][x]=v,ID[x]=id;
	else if(mx[1][x]<v)mx[1][x]=v;
}
void dfs(int x,int f){
	dp[x]=0;mx[0][x]=mx[1][x]=-1e9;ID[x]=0;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		int res=max(dp[u],dp[u]+mx[0][u]+G[i].co);
		calc(x,u,-res+dp[u]+G[i].co);
		dp[x]+=res;
	}
}
int ans=0;
void redfs(int x,int f){
	ans=max(ans,dp[x]);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		int res=max(dp[u],dp[u]+mx[0][u]+G[i].co);
		int New=max(dp[x]-res,dp[x]-res+G[i].co+(ID[x]==u?mx[1][x]:mx[0][x]));
		calc(u,x,-res-New+dp[x]+G[i].co);
		dp[u]+=New;
		redfs(u,x);
	}
}
int main(){
	freopen("beads.in","r",stdin);
	freopen("beads.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	dfs(1,0);
	redfs(1,0);
	printf("%d\n",ans);
	return 0;
}
