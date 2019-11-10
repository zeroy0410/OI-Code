#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
const int mod=998244353;
int n,m;
char H[M],L[M];
LL fac[M],Ifac[M];
LL qkpow(LL a,LL b){
	a=(a%mod+mod)%mod;
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
	for(int i=M-2;i>=0;i--)Ifac[i]=Ifac[i+1]*(i+1)%mod;
}
LL C(LL x,LL y){
	return fac[x]*Ifac[y]%mod*Ifac[x-y]%mod;
}
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
LL a,b;
struct P100{
	void solve(){
		LL ans=qkpow(2,a*b);
		for(int i=1;i<=a;i++){
			if(i&1)Add(ans,-C(a,i)*qkpow(2,(a-i)*b)%mod);
			else Add(ans,C(a,i)*qkpow(2,(a-i)*b)%mod);
		}
		for(int i=1;i<=b;i++){
			if(i&1)Add(ans,-C(b,i)*(qkpow(qkpow(2,b-i)-1,a))%mod);
			else Add(ans,C(b,i)*(qkpow(qkpow(2,b-i)-1,a))%mod);
		}
		printf("%lld\n",ans);
	}
}p100;
int main(){
	freopen("box.in","r",stdin);
	freopen("box.out","w",stdout);
	Init();
	scanf("%d%d",&n,&m);
	scanf("%s",H+1);
	scanf("%s",L+1);
	for(int i=1;i<=n;i++)if(H[i]=='B')a++;
	for(int i=1;i<=m;i++)if(L[i]=='B')b++;
	p100.solve();
	return 0;
}
