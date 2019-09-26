#include<cstdio>
#include<string.h>
#include<algorithm>
#define M 1005
using namespace std;
const int mod=1e9+7;
int T,n,h[M],tt; struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
void calc(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
char S[M];
int dp[M][M],C[M][M],sz[M],tmp[M];
void dfs(int x,int f){
	dp[x][1]=1;sz[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,v=G[i].co;
		if(u==f)continue;
		dfs(u,x);
		for(int a=1;a<=sz[x];a++){
			for(int b=0;b<=sz[u];b++){
				if(v)calc(tmp[a+b],1LL*dp[x][a]*dp[u][b]%mod*C[a+b-1][a-1]%mod*C[sz[x]+sz[u]-a-b][sz[x]-a]%mod);
				else calc(tmp[a+b],1LL*dp[x][a]*(dp[u][sz[u]]-dp[u][b]+mod)%mod*C[a+b-1][a-1]%mod*C[sz[x]+sz[u]-a-b][sz[x]-a]%mod);
			}
		}
		sz[x]+=sz[u];
		for(int j=1;j<=sz[x];j++)dp[x][j]=tmp[j],tmp[j]=0;
	}
	for(int i=2;i<=sz[x];i++)calc(dp[x][i],dp[x][i-1]);
}
int main(){
	C[0][0]=1;
	for(int i=1;i<M;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	memset(h,0,sizeof(h));tt=0;
	memset(dp,0,sizeof(dp));
	scanf("%d",&n);
	scanf("%s",S+2);
	for(int i=2;i<=n;i++){
		if(S[i]=='<')Add(i,i>>1,0),Add(i>>1,i,1);
		else Add(i,i>>1,1),Add(i>>1,i,0);
	}
	dfs(1,0);
	printf("%d\n",dp[1][n]);
	return 0;
}
