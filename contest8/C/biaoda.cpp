#include<bits/stdc++.h>
#define M 200005
using namespace std;
struct EDGE{
	int lt,to,v;
}edge[M<<1];
int tot,h[M],n,ans;
int dp[M],mx1[M],id1[M],mx2[M];
void add(int u,int v,int w){
	edge[++tot]=(EDGE){h[u],v,w};
	h[u]=tot;
}
void Change(int x,int id,int v){
	if (mx1[x]<v)
		mx2[x]=mx1[x],mx1[x]=v,id1[x]=id;
	else if (mx2[x]<v)
		mx2[x]=v;
}
void dfs(int x,int f){
	dp[x]=0;
	mx1[x]=mx2[x]=-1e9; id1[x]=0;
	for(int i=h[x];i;i=edge[i].lt){
		int y=edge[i].to;
		if (y==f) continue;
		dfs(y,x);
		int now=max(dp[y],dp[y]+mx1[y]+edge[i].v);
		Change(x,y,-now+dp[y]+edge[i].v);
		dp[x]+=now;
	}
	cout<<x<<' '<<mx1[x]<<' '<<mx2[x]<<endl;
}
void redfs(int x,int f){
	ans=max(ans,dp[x]);
	for(int i=h[x];i;i=edge[i].lt){
		int y=edge[i].to;
		if (y==f) continue;
		int now=max(dp[y],dp[y]+mx1[y]+edge[i].v);
		int New=max(dp[x]-now,dp[x]-now+edge[i].v+(id1[x]==y?mx2[x]:mx1[x]));
		Change(y,x,-now-New+dp[x]+edge[i].v);
		dp[y]+=New;
		redfs(y,x);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w); add(v,u,w);
	}
	dfs(1,0);
	redfs(1,0);
	printf("%d\n",ans);
	return 0;
}
