#include<stdio.h>
#include<string.h>
#include<algorithm>
#define M 500005
#define LL long long
using namespace std;
int n,K,h[M],tt;
LL dp[M];
int sz[M];
struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
LL mi[M][2],inf;
void update(LL* T,int d){
	if(d<T[0])
		T[1]=T[0],T[0]=d;
	else if(d<T[1])
		T[1]=d;
}
void dfs(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,v=G[i].co;
		if(u==f)continue;
		dfs(u,x);
		sz[x]+=sz[u];
		if(sz[u]==0)continue;
		dp[x]+=dp[u]+2*v;
		update(mi[x],mi[u][0]-v);
	}
}
void redfs(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,v=G[i].co;
		if(u==f)continue;
		if(mi[x][0]==mi[u][0]-v)update(mi[u],mi[x][1]-v);
		else update(mi[u],mi[x][0]-v);
		if(!sz[u])dp[u]=dp[x]+v*2;
		else if(sz[u]==K)dp[u]=dp[x]-2*v;
		else dp[u]=dp[x];
		redfs(u,x);
	}
}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	for(int i=1,x;i<=K;i++){
		scanf("%d",&x);
		sz[x]=1;
	}
	dfs(1,0);
	redfs(1,0);
	for(int i=1;i<=n;i++)
		printf("%lld\n",dp[i]+mi[i][0]);
   	return 0;
}
