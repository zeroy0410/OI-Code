#include<bits/stdc++.h>
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
int n,m;
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n>m)swap(n,m);
	if(n==1)printf("%lld\n",qkpow(2,m));
	else if(n==2)printf("%lld\n",12LL*qkpow(3,m-2)%mod);
	else if(n==3)printf("%lld\n",112LL*qkpow(3,m-3)%mod);
	else if(n==m)printf("%lld\n",(qkpow(2,3*n-7)*83%mod+5LL*qkpow(2,n)%mod)*qkpow(3,mod-2)%mod);
	else printf("%lld\n",qkpow(3,m-n-1)*(qkpow(2,3*n-7)*83%mod+qkpow(2,n+1))%mod);
	return 0;
}
