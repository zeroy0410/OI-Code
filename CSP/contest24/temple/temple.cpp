#include<bits/stdc++.h>
#define M 1000005
#define LL long long
const int mod=998244353;
int n,m,T;
LL fac[M],Ifac[M];
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
	fac[0]=1;
	for(int i=1;i<M;i++)fac[i]=fac[i-1]*i%mod;
	Ifac[M-1]=qkpow(fac[M-1],mod-2);
	for(int i=M-2;i>=0;i--)
		Ifac[i]=Ifac[i+1]*(i+1)%mod;
}
LL C(LL x,LL y){
	return fac[x]*Ifac[y]%mod*Ifac[x-y]%mod;
}
int main(){
	freopen("temple.in","r",stdin);
	freopen("temple.out","w",stdout);
	Init();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		printf("%lld\n",C((n+m)/2,m));
	}
	return 0;
}
