#include<bits/stdc++.h>
#define M 5005
#define LL long long
using namespace std;
const int mod=998244353;
int n,K;
struct edge{
	int to,fr;
}E[M<<1];
int lst[M],tote;
void addedge(int a,int b){
	E[++tote]=(edge){b,lst[a]};
	lst[a]=tote;
}
LL Pow(LL x,int y){
	LL res=1;
	for(;y;y>>=1,x=x*x%mod)if(y&1)res=res*x%mod;
	return res;
}
namespace P0{
	LL fac[M],inv[M];
	LL Com(int a,int b){
		if(b<0||a<0||a<b)return 0;
		return fac[a]*inv[a-b]%mod*inv[b]%mod;
	}
	void Add(LL &x,LL y){if((x+=y)>=mod)x-=mod;}
	LL dp[M][M],DP[M][M];
	int sz[M];
	void dfs(int v,int f){
		DP[0][0]=1;
		int son=0;
		for(int i=lst[v];i;i=E[i].fr){
			int u=E[i].to;
			if(u==f)continue;
			dfs(u,v);
			sz[v]+=sz[u];
			for(int a=0;a<=sz[v];a++)
				for(int q=0,ed=min(a,sz[u]);q<=ed;q++)
					Add(DP[u][a],dp[u][q]*Com(a,q)%mod*DP[son][a-q]%mod*Com(sz[v]-a,sz[u]-q)%mod);
			son=u;
		}
		sz[v]++;
		for(int i=0;i<=sz[v];i++){
			dp[v][i]=DP[son][i]*(sz[v]-i)%mod;//不选根 
			if(i){
				Add(DP[son][i],DP[son][i-1]);
				Add(dp[v][i],DP[son][i-1]*K%mod);//选根 
			}
		}
	}
	void solve(){
		fac[0]=1;
		for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
		inv[n]=Pow(fac[n],mod-2);
		for(int i=n;i;i--)inv[i-1]=inv[i]*i%mod;
		dfs(1,0);
		cout<<dp[1][n]<<endl;
	}
}
namespace Pcha{
	void solve(){
		LL ans=1;
		for(int i=1;i<=n;i++)ans=ans*(i-1+K)%mod;
		cout<<ans<<endl;
	}
}
int main(){
	freopen("random.in","r",stdin);
	freopen("random.out","w",stdout);
	scanf("%d%d",&n,&K);
	bool cha=1;
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		if(a+1!=b)cha=0;
		addedge(a,b);
		addedge(b,a);
	}
	if(cha)Pcha::solve();
	else P0::solve();
	return 0;
}
