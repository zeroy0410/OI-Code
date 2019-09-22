#include<stdio.h>
#include<algorithm>
#define M 100005
#define LL long long
using namespace std;
const int mod=998244353;
int n,m,K;
LL sum[M],fac[M],Ifac[M];
LL S(int l,int r){
	if(l<=r)return sum[r]-sum[l-1];
	return sum[n]-sum[l-1]+sum[r];
}
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
void Init(){
	fac[0]=1;Ifac[0]=Ifac[1]=1;
	for(int i=1;i<M;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<M;i++)Ifac[i]=Ifac[i-1]*qkpow(i,mod-2)%mod;
}
LL Com(LL a,LL b){
	if(a<b||a<0||b<0)return 0;
	return fac[a]*Ifac[b]%mod*Ifac[a-b]%mod;
}
LL Per(LL a,LL b){
	if(a<b||a<0||b<0)return 0;
	return fac[a]*Ifac[a-b]%mod;
}
LL calc0(int c1,int c2){
	LL res=0;
	Add(res,Com(m,c1+c2)*Com(c1+c2,c1)%mod*Per(n-c1-c2-1,m-c1-c2)%mod);
	Add(res,Com(m,c1+c2+1)*Com(c1+c2,c1+1)%mod*Per(n-c1-c2-1,m-c1-c2-1)%mod);
	Add(res,Com(m,c1+c2+1)*Com(c1+c2,c2+1)%mod*Per(n-c1-c2-1,m-c1-c2-1)%mod);
	return res;
}
LL calc1(int c1,int c2){
	LL res=0;
	Add(res,Com(m,c1+c2+1)*Com(c1+c2,c1+1)%mod*Per(n-c1-c2-1,m-c1-c2-1)%mod);
	Add(res,Com(m,c1+c2+1)*Com(c1+c2,c2+1)%mod*Per(n-c1-c2-1,m-c1-c2-1)%mod);
	return res;
}
int main(){
	Init();
	int T;cin>>T;
	while(T--){
		scanf("%d%d%d",&n,&m,&K);
		for(int i=1,x;i<=n;i++)scanf("%d",&x),sum[i]=sum[i-1]+x;
		if(K==0)puts("1");
		LL ans=0;
		for(int l=2,r=3;l<n;l++)
	}
	return 0;
}
