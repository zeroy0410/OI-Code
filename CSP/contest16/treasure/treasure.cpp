#include<stdio.h>
#include<algorithm>
#define M 100005
#define LL long long
using namespace std;
const int mod=998244353;
int n,h[M],tt;
LL fac[M],Ifac[M],ans;
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
struct edge{
	int nxt,to;
}G[M];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void dfs(int x,int f,int d){
	if(x!=0)
		ans=(ans+fac[n]*Ifac[d+1]%mod)%mod;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x,d+1);
	}
}
int main(){
	freopen("treasure.in","r",stdin);
	freopen("treasure.out","w",stdout);
	fac[0]=1;Ifac[0]=Ifac[1]=1;
	for(int i=1;i<M;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<M;i++)Ifac[i]=Ifac[i-1]*qkpow(i,mod-2)%mod;
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		if(x==-1)Add(0,i);
		else Add(x,i);
	}
	dfs(0,0,-1);
	printf("%lld\n",ans*Ifac[n]%mod);
	return 0;
}
