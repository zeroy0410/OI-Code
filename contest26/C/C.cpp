#include<bits/stdc++.h>
#define LL long long
#define M 50005
using namespace std;
const int mod=10007;
int n,K,h[M],tt;
int now,A,B,Q,L;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int dp[M][155],f[M][155],tmp[155];
int str[155][155],fac[M];
void Init(){
	str[0][0]=str[1][1]=1;
	for(int i=2;i<=K;i++)
		for(int j=1;j<=i;j++)
			str[i][j]=(str[i-1][j-1]+1LL*j*str[i-1][j])%mod;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1LL*fac[i-1]*i%mod;
}
void dfs(int x,int fa){
	dp[x][0]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==fa)continue;
		dfs(u,x);
		for(int j=1;j<=K;j++)dp[x][j]=(dp[x][j]+dp[u][j]+dp[u][j-1])%mod;
		dp[x][0]=(dp[x][0]+dp[u][0])%mod;
	}
}
void redfs(int x,int fa){
	for(int i=0;i<=K;i++)
		f[x][i]=dp[x][i];
	if(fa){
		for(int i=0;i<=K;i++)
			tmp[i]=(f[fa][i]-dp[x][i]+mod-dp[x][i-1]+mod)%mod;
		tmp[0]=(f[fa][0]-dp[x][0]+mod)%mod;
		for(int i=1;i<=K;i++)
			f[x][i]=(f[x][i]+tmp[i]+tmp[i-1])%mod;
		f[x][0]=(f[x][0]+tmp[0])%mod;
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==fa)continue;
		redfs(u,x);
	}
}
int main(){
	freopen("civilization.in","r",stdin);
	freopen("civilization.out","w",stdout);
	scanf("%d%d%d",&n,&K,&L);
	Init();
	scanf("%d%d%d%d",&now,&A,&B,&Q);
	int tmp,x,y;
	for(int i=1;i<n;i++){
	    now=(now*A+B)%Q,tmp=i<L?i:L;
	    x=i-now%tmp,y=i+1;
	    Add(x,y);Add(y,x);
	}
	dfs(1,0);
	redfs(1,0);
	for(int i=1;i<=n;i++){
		LL res=0;
		for(int j=0;j<=K;j++)
			res=(res+1LL*str[K][j]*fac[j]*f[i][j])%mod;
		printf("%lld\n",res);
	}
	return 0;
}
