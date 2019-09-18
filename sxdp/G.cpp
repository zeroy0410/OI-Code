#include<stdio.h>
#include<algorithm>
#pragma GCC optimize(3)
#define LL long long
#define M 100005
using namespace std;
int n,h[M],tt;
struct edge{
	int nxt,to;
}G[M];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int dp[M][520],len[M];
LL ans[520];
void dfs(int x,int f){
	dp[x][0]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		for(int j=0;j<=len[x];j++)
			for(int k=0;k<=len[u];k++)
				ans[j^(k+1)]+=1LL*dp[x][j]*dp[u][k];
		len[x]=max(len[x],len[u]+1);
		for(int j=1;j<=len[x];j++)
			dp[x][j]+=dp[u][j-1];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=2,x;i<=n;i++){
		scanf("%d",&x);
		Add(x,i);
	}
	dfs(1,0);
	for(int i=0;;i++){
		if(ans[i]==0)break;
		printf("%lld\n",ans[i]);
	}
	return 0;
}
