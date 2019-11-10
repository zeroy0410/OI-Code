#include<stdio.h>
#define M 1000005
#define LL long long
const int mod=1e9+7;
int n;
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
struct node{LL a,b;}dp[M];//a*dp[1]+b
LL p1[M],p2[M];
int main(){
	freopen("mine.in","r",stdin);
	freopen("mine.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b;i<=n;i++){
		scanf("%d%d",&a,&b);
		p1[i]=1LL*a*qkpow(b,mod-2)%mod;
		p2[i]=1LL*(b-a)*qkpow(b,mod-2)%mod;
	}
	dp[n]=(node){p2[n],1};
	for(int i=n-1;i>=1;i--)
		dp[i]=(node){(dp[i+1].a*p1[i]%mod+p2[i])%mod,(dp[i+1].b*p1[i]%mod+1)%mod};
	LL a=dp[1].a,b=dp[1].b;
	LL ans=((-b)%mod+mod)%mod*qkpow(((a-1)%mod+mod)%mod,mod-2)%mod;
	printf("%lld\n",ans);
	return 0;
}
