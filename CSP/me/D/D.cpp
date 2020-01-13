#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
const int P=105;
int n,m,A[2005][2005];
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
LL ans=1,res[2005];
LL dp[2005][2005];
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
int main(){
//	freopen("meal.in","r",stdin);
//	freopen("meal.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&A[i][j]);
	for(int i=1;i<=n;i++){
		res[i]=0;
		for(int j=1;j<=m;j++)
			res[i]=(res[i]+A[i][j])%mod;
		ans=ans*(res[i]+1)%mod;
	}
	for(int j=1;j<=m;j++){//main matarial
		memset(dp,0,sizeof(dp));
		dp[0][P]=1;
		for(int i=1;i<=n;i++){//method
			LL xu=A[i][j];//qu
			LL bx=(res[i]-A[i][j]+mod)%mod;//buqu
			for(int j=-i;j<=i;j++){
				if(j+P-1>=0)Add(dp[i][j+P],dp[i-1][j+P-1]*xu%mod);
				Add(dp[i][j+P],dp[i-1][j+P+1]*bx%mod);
				Add(dp[i][j+P],dp[i-1][j+P]%mod);
			}
		}
		for(int i=1;i<=n;i++)
			Add(ans,-dp[n][i+P]);
	}
	printf("%lld\n",(ans-1+mod)%mod);
	return 0;
} 
