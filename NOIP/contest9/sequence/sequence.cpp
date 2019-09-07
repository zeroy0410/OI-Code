#include<bits/stdc++.h>
#define LL long long
#define M 2005
using namespace std;
const int mod=152076289;
int n,m,K;
LL dp[M][M],S[M][M],fac[M],sum[M];
void Init(){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	S[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			S[i][j]=(S[i-1][j-1]+S[i-1][j]*j)%mod;
}
int main(){
	scanf("%d%d%d",&n,&m,&K);
	Init();
	dp[1][0]=1;LL ans=1;
	for(int i=2;i<=n;i++){
		sum[0]=dp[i-1][0];
		for(int j=1;j<=m;j++)
			sum[j]=(sum[j-1]+dp[i-1][j])%mod;
		for(int j=1;j<=m;j++){
			dp[i][j]=sum[j-1]-(j-K>=1?sum[j-K-1]:0);
			ans=(ans+S[n][i]*fac[i]%mod*dp[i][j])%mod;
		}
	}
	ans=(ans%mod+mod)%mod;
	cout<<ans<<endl;
	return 0;
}
