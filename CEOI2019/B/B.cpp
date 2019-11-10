#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,m,K,h[M],tt;
int T[M];LL W[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;	
}
map<int,LL>dp[M];
void dfs(int x){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		dfs(u);
		if(dp[x].size()<dp[u].size())swap(dp[x],dp[u]);
		for(auto t:dp[u])
			dp[x][t.first]+=t.second;
	}
	dp[x][T[x]]+=W[x];
	for(auto t=dp[x].upper_bound(T[x]);t!=dp[x].end();){
		if(t->second>W[x]){
			t->second-=W[x];
			break;
		}
		W[x]-=t->second;
		auto tmp=t++;
		dp[x].erase(tmp);
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&K);
	for(int i=2,f;i<=n;i++){
		scanf("%d",&f);
		Add(f,i);
	}
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		scanf("%d%d",&T[x],&W[x]);
	}
	dfs(1);
	LL ans=0;
	for(auto t:dp[1])ans+=t.second;
	printf("%lld\n",ans);
	return 0;
}
