#include<bits/stdc++.h>
#define M 1005
#define LL long long
using namespace std;
const int mod=1e9+7;
int n,K,h[M],tt,A[M];
int stk[M],top;
int ch[M][2],rt,sz[M];
LL dp[M][M>>1];
LL fac[M*M],Ifac[M*M];
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
void Init(){
	fac[0]=1;Ifac[0]=Ifac[1]=1;
	for(int i=1;i<M*M;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<M*M;i++)Ifac[i]=Ifac[i-1]*qkpow(i,mod-2)%mod;
}
LL C(LL x,LL y){
	if(x<y)return 0;
	return fac[x]*Ifac[y]%mod*Ifac[x-y]%mod;
}
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
}
void dfs(int x,int f){
	sz[x]=1;dp[x][0]=1;
	for(int i=0;i<=1;i++){
		int u=ch[x][i];
		if(u==0)continue;
		dfs(u,x);
		for(int j=min(K,sz[x]);j>=0;j--)
			for(int k=min(K,sz[u]);k>=1;k--){
				if(j+k>K)continue;
				Add(dp[x][j+k],1LL*dp[x][j]*dp[u][k]%mod);
			}
		sz[x]+=sz[u];
	}
	int dif=A[x]-A[f];
	for(int j=min(K,sz[x]);j>=0;j--)
		for(int k=sz[x]-j;k>=1;k--){
			if(j+k>K)continue;
			Add(dp[x][j+k],1LL*dp[x][j]*C(sz[x]-j,k)%mod*C(dif,k)%mod*fac[k]%mod);
		}
}
int main(){
	Init();
	scanf("%d%d",&n,&K);rt=1;
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n;i++){
		int res=-1;
		while(top&&A[i]<=A[stk[top]])res=stk[top--];
		if(res!=-1){
			if(rt==res)rt=i;
			ch[i][0]=res;
		}
		if(top)ch[stk[top]][1]=i;
		stk[++top]=i;
	}
	dfs(rt,0);
	printf("%lld\n",dp[rt][K]);
	return 0;
}
