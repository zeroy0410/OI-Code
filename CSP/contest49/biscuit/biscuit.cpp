#include<bits/stdc++.h>
#define M 2005
#define LL long long
using namespace std;
const int mod=1e9+7;
int n,x,q;
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
}
LL dp[M][2],sum[M],ret[M],Pow[M],ans;
int R[M];
int main(){
//	freopen("biscuit.in","r",stdin);
//	freopen("biscuit.out","w",stdout);
	scanf("%d%d%d",&n,&x,&q);
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
			R[r]=max(R[r],l);
		}
		for(int i=1;i<=n;i++)
			R[i]=max(R[i],R[i-1]);
		for(int v=1;v<=x;v++){//mi<=v
			memset(dp,0,sizeof(dp));
			Pow[0]=1;
			for(int i=1;i<=n;i++)Pow[i]=Pow[i-1]*(x-v)%mod;
			dp[0][0]=1;dp[0][1]=1;
			sum[0]=dp[0][1]*qkpow(Pow[0],mod-2)%mod;
			for(int i=1;i<=n;i++){
				if(i==1)dp[i][1]=v;
				else dp[i][1]=(dp[i-1][0]+dp[i-1][1])*v%mod;
				dp[i][0]=(sum[i-1]-sum[R[i]-1]+mod)*Pow[i]%mod;
				sum[i]=(sum[i-1]+dp[i][1]*qkpow(Pow[i],mod-2)%mod)%mod;
			}
			ret[v]=(dp[n][0]+dp[n][1])%mod;
		}
		LL tot=qkpow(x,n);
		for(int i=1;i<=x;i++){
			Add(ans,(ret[i]-ret[i-1])*i%mod);
			ans=(ans+mod)%mod;
		}
		printf("%lld\n",ans*qkpow(tot,mod-2)%mod);

	return 0;
}
