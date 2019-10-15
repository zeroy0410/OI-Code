#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#pragma GCC optimize("Ofast")
#define M 20005
#define LL long long
using namespace __gnu_pbds;
using namespace std;
int n,m,h[M],tt,K;
struct edge{
	int nxt,to;
	LL co;
}G[M*20];
void Add(int a,int b,LL c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
LL dis[M];
bool vis[M];
struct node{
	int x;LL v;
	bool operator < (const node& res)const{
		return v>res.v;
	}
};
__gnu_pbds::priority_queue<node>Q;
void Dijkstra(int st){
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[st]=0;Q.push((node){st,0});
	while(!Q.empty()){
		node e=Q.top();Q.pop();
		if(vis[e.x])continue;
		vis[e.x]=1;
		for(int i=h[e.x];i;i=G[i].nxt){
			int u=G[i].to;LL v=G[i].co;
			if(dis[u]>dis[e.x]+v){
				dis[u]=dis[e.x]+v;
				Q.push((node){u,dis[u]});
			}
		}
	}
}
LL Dis[25][25],dp[1<<20][20];
int g[25],q,gg[25];
int main(){
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	for(int i=1;i<=K+1;i++){
		Dijkstra(i);
		for(int j=1;j<=K+1;j++)
			Dis[i][j]=dis[j];
		Dis[i][K+2]=dis[n];
	}
	scanf("%d",&q);
	for(int i=1,a,b;i<=q;i++){
		scanf("%d%d",&a,&b);
		g[b]|=1<<(a-2);
	}
	if(K==0){printf("%lld\n",Dis[1][K+2]);return 0;}
	memset(dp,0x3f,sizeof(dp));LL inf=dp[0][0];
	for(int i=0;i<K;i++)if(g[i+2]==0)dp[1<<i][i]=Dis[1][i+2];
	for(int i=0;i<1<<K;i++){
		for(int j=0;j<K;j++){
			if(!(i&1<<j))continue;
			if(dp[i][j]==inf)continue;
			for(int k=0;k<K;k++){
				if(i&1<<k)continue;
				if((g[k+2]&i)!=g[k+2])continue;
				dp[i|1<<k][k]=min(dp[i|1<<k][k],dp[i][j]+Dis[j+2][k+2]);
			}
		}
	}
	LL ans=inf;
	for(int i=0;i<K;i++)
		ans=min(ans,dp[(1<<K)-1][i]+Dis[i+2][K+2]);
	printf("%lld\n",ans);
	return 0;
}
