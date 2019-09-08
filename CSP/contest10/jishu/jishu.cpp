#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
const int mod=1e9+7;
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
LL fac[M],Ifac[M];
void Init(){
	fac[0]=1;Ifac[0]=Ifac[1]=1;
	for(int i=1;i<M;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<M;i++)Ifac[i]=Ifac[i-1]*qkpow(i,mod-2)%mod;
}
LL C(LL a,LL b){
	return fac[a]*Ifac[b]%mod*Ifac[a-b]%mod;
}
int T,n,m;
LL dp[M];
void inf(){
	dp[0]=1;dp[1]=0;dp[2]=1;
	for(int i=3;i<M;i++)
		dp[i]=(dp[i-1]+dp[i-2])*(i-1)%mod;
}
int main(){
	freopen("jishu.in","r",stdin);
	freopen("jishu.out","w",stdout);
	Init();
	inf();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		LL ans=C(n,m)*dp[n-m]%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
